/*
 * Copyright (C) 2020-2024 ArtInChip Technology Co. Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: <jun.ma@artinchip.com>
 * Desc: aic recorder api
 */

#include <fcntl.h>
#include <malloc.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "aic_muxer.h"
#include "aic_recorder.h"
#include "mm_core.h"
#include "mpp_dec_type.h"
#include "mpp_log.h"
#include "mpp_mem.h"

#define AIC_RECORDER_STATE_IDLE 0
#define AIC_RECORDER_STATE_INITIALIZED 1
#define AIC_RECORDER_STATE_RECORDING 2
#define AIC_RECORDER_STATE_STOPPED 3

#define wait_state(                            \
    h_component,                               \
    des_state)                                 \
    {                                          \
        MM_STATE_TYPE state;                   \
        while (1) {                            \
            mm_get_state(h_component, &state); \
            if (state == des_state) {          \
                break;                         \
            } else {                           \
                usleep(1000);                  \
            }                                  \
        }                                      \
    } /* Macro End */

struct aic_recorder {
    mm_handle muxer_handle;
    mm_handle venc_handle;
    mm_handle vin_handle;
    mm_handle aenc_handle;
    struct aic_recorder_config config;
    event_handler event_handle;
    void *app_data;
    char uri[512];
    int state;
};

static s32 component_event_handler(
    mm_handle h_component,
    void *p_app_data,
    MM_EVENT_TYPE event,
    u32 data1,
    u32 data2,
    void *p_event_data)
{
    s32 error = MM_ERROR_NONE;
    struct aic_recorder *recorder = (struct aic_recorder *)p_app_data;

    switch ((s32)event) {
    case MM_EVENT_MUXER_NEED_NEXT_FILE:
        recorder->event_handle(recorder->app_data,
                               AIC_RECORDER_EVENT_NEED_NEXT_FILE, 0, 0);
        break;


    case MM_EVENT_BUFFER_FLAG:
         recorder->event_handle(recorder->app_data, AIC_RECORDER_EVENT_COMPLETE, 0, 0);
         break;

    default:
        break;
    }
    return error;
}

s32 component_giveback_buffer(
    mm_handle h_component,
    void *p_app_data,
    mm_buffer *p_buffer)
{
    s32 error = MM_ERROR_NONE;

    u64 tmp = (u64)(unsigned long)p_buffer->p_buffer;
    struct aic_recorder *recorder = (struct aic_recorder *)p_app_data;
    if (h_component == recorder->venc_handle) {
        recorder->event_handle(recorder->app_data,
                               AIC_RECORDER_EVENT_RELEASE_VIDEO_BUFFER,
                               (u32)tmp, 0);
    }
    return error;
}

static mm_callback component_event_callbacks = {
    .event_handler = component_event_handler,
    .giveback_buffer = component_giveback_buffer,
};

struct aic_recorder *aic_recorder_create(void)
{
    s32 error;
    struct aic_recorder *recorder = mpp_alloc(sizeof(struct aic_recorder));
    if (recorder == NULL) {
        loge("mpp_alloc aic_recorder error\n");
        return NULL;
    }
    memset(recorder, 0x00, sizeof(struct aic_recorder));
    error = mm_init();
    if (error != MM_ERROR_NONE) {
        loge("mm_init error!!!\n");
        mpp_free(recorder);
        return NULL;
    }
    recorder->state = AIC_RECORDER_STATE_IDLE;
    return recorder;
}

s32 aic_recorder_destroy(struct aic_recorder *recorder)
{
    mm_deinit();
    mpp_free(recorder);
    return 0;
}

s32 aic_recorder_set_event_callback(struct aic_recorder *recorder,
                                    void *app_data, event_handler event_handle)
{
    recorder->event_handle = event_handle;
    recorder->app_data = app_data;
    return 0;
}

s32 aic_recorder_init(struct aic_recorder *recorder,
                      struct aic_recorder_config *recorder_config)
{
    int ret = 0;
    mm_param_port_def port_define;
    mm_param_record_file_info rec_file_info;
    mm_image_param_qfactor qfactor;

    if (!recorder || !recorder_config) {
        return -1;
    }
    recorder->config = *recorder_config;
    if (!recorder->config.has_video && !recorder->config.has_audio) {
        loge("para error\n");
        return -1;
    }

    // create muxer
    if (MM_ERROR_NONE != mm_get_handle(&recorder->muxer_handle,
                                       MM_COMPONENT_MUXER_NAME,
                                       recorder,
                                       &component_event_callbacks)) {
        loge("unable to get muxer_handle handle.\n");
        return -1;
    }
    // set muxer para
    rec_file_info.duration = recorder->config.file_duration;
    rec_file_info.file_num = recorder->config.file_num;
    rec_file_info.muxer_type = 0; // only support  mp4
    if (MM_ERROR_NONE != mm_set_parameter(recorder->muxer_handle,
                                          MM_INDEX_VENDOR_MUXER_RECORD_FILE_INFO,
                                          &rec_file_info)) {
        loge("mm_set_parameter error.\n");
        ret = -1;
        goto _EXIT;
    }
    // video
    if (recorder->config.has_video) {
        // create vin
        if (MM_ERROR_NONE != mm_get_handle(&recorder->vin_handle,
                                           MM_COMPONENT_VIN_NAME,
                                           recorder,
                                           &component_event_callbacks)) {
            loge("unable to get vin_handle handle.\n");
            ret = -1;
            goto _EXIT;
        }

        // create venc
        if (MM_ERROR_NONE != mm_get_handle(&recorder->venc_handle,
                                           MM_COMPONENT_VENC_NAME,
                                           recorder,
                                           &component_event_callbacks)) {
            loge("unable to get venc_handle handle.\n");
            ret = -1;
            goto _EXIT;
        }

        // set muxer in_video_port para
        port_define.port_index = MUX_PORT_VIDEO_INDEX;
        if (MM_ERROR_NONE != mm_get_parameter(recorder->muxer_handle,
                                              MM_INDEX_PARAM_PORT_DEFINITION,
                                              &port_define)) {
            loge("mm_get_parameter error.\n");
            ret = -1;
            goto _EXIT;
        }

        port_define.format.video.frame_width = recorder->config.video_config.out_width;
        port_define.format.video.frame_height = recorder->config.video_config.out_height;
        port_define.format.video.framerate = recorder->config.video_config.out_frame_rate;
        port_define.format.video.bitrate = recorder->config.video_config.out_bit_rate;
        if (recorder->config.video_config.codec_type != MPP_CODEC_VIDEO_DECODER_MJPEG) {
            loge("only support MPP_CODEC_VIDEO_DECODER_MJPEG.\n");
            ret = -1;
            goto _EXIT;
        }
        port_define.format.video.compression_format = MM_VIDEO_CODING_MJPEG;
        if (MM_ERROR_NONE != mm_set_parameter(recorder->muxer_handle,
                                              MM_INDEX_PARAM_PORT_DEFINITION,
                                              &port_define)) {
            loge("mm_set_parameter error.\n");
            ret = -1;
            goto _EXIT;
        }

        // set venc in_port para
        if (MM_ERROR_NONE != mm_get_parameter(recorder->venc_handle,
                                              MM_INDEX_PARAM_PORT_DEFINITION,
                                              &port_define)) {
            loge("mm_set_parameter error.\n");
            ret = -1;
            goto _EXIT;
        }
        port_define.format.video.frame_width = recorder->config.video_config.out_width;
        port_define.format.video.frame_height = recorder->config.video_config.out_height;
        port_define.format.video.framerate = recorder->config.video_config.out_frame_rate;
        port_define.format.video.bitrate = recorder->config.video_config.out_bit_rate;
        port_define.format.video.compression_format = MM_VIDEO_CODING_MJPEG;
        if (MM_ERROR_NONE != mm_set_parameter(recorder->venc_handle,
                                              MM_INDEX_PARAM_PORT_DEFINITION,
                                              &port_define)) {
            loge("mm_set_parameter error.\n");
            ret = -1;
            goto _EXIT;
        }
        qfactor.q_factor = recorder->config.qfactor;
        if (MM_ERROR_NONE != mm_set_parameter(recorder->venc_handle,
                                              MM_INDEX_PARAM_QFACTOR,
                                              &qfactor)) {
            loge("mm_set_parameter error.\n");
            ret = -1;
            goto _EXIT;
        }

        port_define.format.video.frame_width = recorder->config.video_config.out_width;
        port_define.format.video.frame_height = recorder->config.video_config.out_height;
        port_define.format.video.framerate = recorder->config.video_config.out_frame_rate;
        port_define.format.video.color_format = MM_COLOR_FORMAT_YUV420P;
        if (MM_ERROR_NONE != mm_set_parameter(recorder->vin_handle,
                                              MM_INDEX_PARAM_PORT_DEFINITION,
                                              &port_define)) {
            loge("mm_set_parameter error.\n");
            ret = -1;
            goto _EXIT;
        }

        // setup bind VENC_PORT_OUT_INDEX--->MUX_PORT_VIDEO_INDEX
        if (MM_ERROR_NONE != mm_set_bind(recorder->venc_handle,
                                         VENC_PORT_OUT_INDEX,
                                         recorder->muxer_handle,
                                         MUX_PORT_VIDEO_INDEX)) {
            loge("mm_set_bind venc and muxer error.\n");
            ret = -1;
            goto _EXIT;
        }

        // setup bind VIN_PORT_OUT_INDEX--->VENC_PORT_VIDEO_INDEX
        if (MM_ERROR_NONE != mm_set_bind(recorder->vin_handle,
                                         VIN_PORT_OUT_INDEX,
                                         recorder->venc_handle,
                                         VENC_PORT_IN_INDEX)) {
            loge("mm_set_bind vin and venc error.\n");
            ret = -1;
            goto _EXIT;
        }
    }

    // audio
    if (recorder->config.has_audio) {
    }

    if (recorder->muxer_handle) {
        mm_send_command(recorder->muxer_handle, MM_COMMAND_STATE_SET, MM_STATE_IDLE, NULL);
    }
    if (recorder->venc_handle) {
        mm_send_command(recorder->venc_handle, MM_COMMAND_STATE_SET, MM_STATE_IDLE, NULL);
    }
    if (recorder->vin_handle) {
        mm_send_command(recorder->vin_handle, MM_COMMAND_STATE_SET, MM_STATE_IDLE, NULL);
    }
    if (recorder->aenc_handle) {
        mm_send_command(recorder->aenc_handle, MM_COMMAND_STATE_SET, MM_STATE_IDLE, NULL);
    }

    recorder->state = AIC_RECORDER_STATE_INITIALIZED;

    return ret;
_EXIT:
    if (recorder->muxer_handle) {
        mm_free_handle(recorder->muxer_handle);
        recorder->muxer_handle = NULL;
    }
    if (recorder->venc_handle) {
        mm_free_handle(recorder->venc_handle);
        recorder->venc_handle = NULL;
    }
    if (recorder->vin_handle) {
        mm_free_handle(recorder->vin_handle);
        recorder->vin_handle = NULL;
    }
    if (recorder->aenc_handle) {
        mm_free_handle(recorder->aenc_handle);
        recorder->aenc_handle = NULL;
    }
    return ret;
}

s32 aic_recorder_start(struct aic_recorder *recorder)
{
    if (recorder->config.has_video && recorder->vin_handle) {
        mm_send_command(recorder->vin_handle, MM_COMMAND_STATE_SET, MM_STATE_EXECUTING, NULL);
    }
    if (recorder->config.has_video && recorder->venc_handle) {
        mm_send_command(recorder->venc_handle, MM_COMMAND_STATE_SET, MM_STATE_EXECUTING, NULL);
    }
    if (recorder->config.has_audio && recorder->aenc_handle) {
        mm_send_command(recorder->aenc_handle, MM_COMMAND_STATE_SET, MM_STATE_EXECUTING, NULL);
    }
    if (recorder->muxer_handle) {
        mm_send_command(recorder->muxer_handle, MM_COMMAND_STATE_SET, MM_STATE_EXECUTING, NULL);
    }
    recorder->state = AIC_RECORDER_STATE_RECORDING;
    return 0;
}

s32 aic_recorder_stop(struct aic_recorder *recorder)
{
    if (recorder->state == AIC_RECORDER_STATE_IDLE) {
        printf("%s:%d\n", __FUNCTION__, __LINE__);
        goto _FREE_HANDLE_;
    }

    if (recorder->muxer_handle) {
        mm_send_command(recorder->muxer_handle, MM_COMMAND_STATE_SET, MM_STATE_IDLE, NULL);
        wait_state(recorder->muxer_handle, MM_STATE_IDLE);
        mm_send_command(recorder->muxer_handle, MM_COMMAND_STATE_SET, MM_STATE_LOADED, NULL);
        wait_state(recorder->muxer_handle, MM_STATE_LOADED);
    }

    if (recorder->config.has_video) {
        if (recorder->venc_handle) {
            mm_send_command(recorder->venc_handle, MM_COMMAND_STATE_SET, MM_STATE_IDLE, NULL);
            wait_state(recorder->venc_handle, MM_STATE_IDLE);
            mm_send_command(recorder->venc_handle, MM_COMMAND_STATE_SET, MM_STATE_LOADED, NULL);
            wait_state(recorder->venc_handle, MM_STATE_LOADED);
        }
        if (recorder->vin_handle) {
            mm_send_command(recorder->vin_handle, MM_COMMAND_STATE_SET, MM_STATE_IDLE, NULL);
            wait_state(recorder->vin_handle, MM_STATE_IDLE);
            mm_send_command(recorder->vin_handle, MM_COMMAND_STATE_SET, MM_STATE_LOADED, NULL);
            wait_state(recorder->vin_handle, MM_STATE_LOADED);
        }
    }

    if (recorder->config.has_video) {
        if (recorder->muxer_handle && recorder->venc_handle) {
            mm_set_bind(recorder->venc_handle, VENC_PORT_OUT_INDEX, NULL, 0);
            mm_set_bind(NULL, 0, recorder->muxer_handle, MUX_PORT_VIDEO_INDEX);
        }
        if (recorder->venc_handle && recorder->vin_handle) {
            mm_set_bind(recorder->vin_handle, VENC_PORT_OUT_INDEX, NULL, 0);
            mm_set_bind(NULL, 0, recorder->venc_handle, MUX_PORT_VIDEO_INDEX);
        }
    }

_FREE_HANDLE_:
    if (recorder->muxer_handle) {
        mm_free_handle(recorder->muxer_handle);
        recorder->muxer_handle = NULL;
    }
    if (recorder->venc_handle) {
        mm_free_handle(recorder->venc_handle);
        recorder->venc_handle = NULL;
    }
     if (recorder->vin_handle) {
        mm_free_handle(recorder->vin_handle);
        recorder->vin_handle = NULL;
    }
    if (recorder->aenc_handle) {
        mm_free_handle(recorder->aenc_handle);
        recorder->aenc_handle = NULL;
    }
    return 0;
}

s32 aic_recorder_set_output_file_path(struct aic_recorder *recorder, char *uri)
{
    int bytes;
    mm_param_content_uri *uri_param;

    if (!recorder || !uri) {
        loge("param  error\n");
        return -1;
    }
    memset(recorder->uri, 0x00, sizeof(recorder->uri));
    strncpy(recorder->uri, uri, sizeof(recorder->uri) - 1);
    bytes = strlen(recorder->uri);
    uri_param = (mm_param_content_uri *)mpp_alloc(sizeof(mm_param_content_uri) + bytes);
    uri_param->size = sizeof(mm_param_content_uri) + bytes;
    strcpy((char *)uri_param->content_uri, recorder->uri);
    mm_set_parameter(recorder->muxer_handle, MM_INDEX_PARAM_CONTENT_URI, uri_param);
    mpp_free(uri_param);
    return 0;
}

s32 aic_recorder_set_input_file_path(struct aic_recorder *recorder, char *video_uri, char *audio_uri)
{
    int bytes;
    mm_param_content_uri *uri_param;

    if (!recorder || !video_uri) {
        loge("param  error\n");
        return -1;
    }
    memset(recorder->uri, 0x00, sizeof(recorder->uri));
    strncpy(recorder->uri, video_uri, sizeof(recorder->uri) - 1);
    bytes = strlen(recorder->uri);
    uri_param = (mm_param_content_uri *)mpp_alloc(sizeof(mm_param_content_uri) + bytes);
    uri_param->size = sizeof(mm_param_content_uri) + bytes;
    strcpy((char *)uri_param->content_uri, recorder->uri);
    mm_set_parameter(recorder->vin_handle, MM_INDEX_PARAM_CONTENT_URI, uri_param);
    mpp_free(uri_param);
    return 0;
}


s32 aic_recorder_set_vin_type(struct aic_recorder *recorder, enum aic_recorder_vin_type type)
{
    if (!recorder || !recorder->vin_handle) {
        loge("recorder or vin_handle is null\n");
        return -1;
    }

    mm_param_u32 param;
    if (type == AIC_RECORDER_VIN_DVP) {
        param.u32 = MM_VIDEO_IN_SOURCE_DVP;
    } else if (type == AIC_RECORDER_VIN_USB) {
        param.u32 = MM_VIDEO_IN_SOURCE_USB;
    } else {
        param.u32 = MM_VIDEO_IN_SOURCE_FILE;
    }

    return mm_set_parameter(recorder->vin_handle, MM_INDEX_PARAM_VIDEO_INPUT_SOURCE, (void *)&param);
}

s32 aic_recorder_set_max_duration(struct aic_recorder *recorder)
{
    return 0;
}

s32 aic_recorder_snapshot(struct aic_recorder *recorder, struct aic_record_snapshot_info *snapshot_info)
{

    if (!recorder || !recorder->venc_handle) {
        loge("recorder or venc_handle is null\n");
        return -1;
    }

    mm_param_video_capture capture;
    capture.p_file_path = (s8 *)snapshot_info->file_path;

    if (MM_ERROR_NONE != mm_set_config(recorder->venc_handle,
                                       MM_INDEX_VENDOR_VIDEO_ENC_CAPTURE, &capture)) {
        loge("no video!!!!\n");
        return -1;
    }
    return 0;
}

s32 aic_recorder_print_debug_info(struct aic_recorder *recorder)
{
    if (!recorder) {
        loge("recorder is null\n");
        return -1;
    }

    if (recorder->vin_handle) {
        mm_set_parameter(recorder->vin_handle, MM_INDEX_PARAM_PRINT_DEBUG_INFO, NULL);
    }

    if (recorder->venc_handle) {
        mm_set_parameter(recorder->venc_handle, MM_INDEX_PARAM_PRINT_DEBUG_INFO, NULL);
    }

    if (recorder->muxer_handle) {
        mm_set_parameter(recorder->muxer_handle, MM_INDEX_PARAM_PRINT_DEBUG_INFO, NULL);
    }

    return 0;
}