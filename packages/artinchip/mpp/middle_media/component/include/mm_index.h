/*
 * Copyright (C) 2020-2024 ArtInChip Technology Co. Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Author: <jun.ma@artinchip.com>
 * Desc: middle media index desc
 */

#ifndef MM_INDEX_H
#define MM_INDEX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum MM_BOOL {
    MM_FALSE = 0,
    MM_TRUE = !MM_FALSE,
} MM_BOOL;

typedef enum MM_DIR_TYPE {
    MM_DIR_INPUT,  /* Port is an input port */
    MM_DIR_OUTPUT, /* Port is an output port */
    MM_DIR_MAX = 0x7FFFFFFF
} MM_DIR_TYPE;

typedef enum MM_INDEX_TYPE {

    MM_INDEX_COMP_START_UNUSED,

    MM_INDEX_CONFIG_TIME_POSITION = 0x100,
    MM_INDEX_CONFIG_TIME_SEEK_MODE,
    MM_INDEX_CONFIG_TIME_CLOCK_STATE,
    MM_INDEX_CONFIG_TIME_CUR_MEDIA_TIME,
    MM_INDEX_CONFIG_TIME_CUR_AUDIO_REFERENCE,
    MM_INDEX_CONFIG_TIME_CUR_VIDEO_REFERENCE,
    MM_INDEX_CONFIG_TIME_CLIENT_START_TIME,
    MM_INDEX_CONFIG_COMMON_ROTATE,
    MM_INDEX_CONFIG_COMMON_OUTPUT_CROP,
    MM_INDEX_CONFIG_VIDEO_DECODER_EXT_FRAME_ALLOCATOR,
    MM_INDEX_CONFIG_VIDEO_DECODER_CROP_INFO,

    MM_INDEX_PARAM_PORT_DEFINITION = 0x200,
    MM_INDEX_PARAM_ACTIVE_STREAM,
    MM_INDEX_PARAM_NUM_AVAILABLE_STREAM,
    MM_INDEX_PARAM_CONTENT_URI,
    MM_INDEX_PARAM_VIDEO_PORT_FORMAT,
    MM_INDEX_PARAM_AUDIO_PORT_FORMAT,
    MM_INDEX_PARAM_VIDEO_DECODER_HANDLE,
    MM_INDEX_PARAM_AUDIO_DECODER_HANDLE,
    MM_INDEX_PARAM_VIDEO_STREAM_END_FLAG,
    MM_INDEX_PARAM_QFACTOR,
    MM_INDEX_PARAM_AUDIO_MP3,
    MM_INDEX_PARAM_VIDEO_INPUT_SOURCE,
    MM_INDEX_PARAM_PRINT_DEBUG_INFO,

    MM_INDEX_VENDOR_STREAM_FRAME_END = 0x300,
    MM_INDEX_VENDOR_VIDEO_RENDER_INIT,
    MM_INDEX_VENDOR_AUDIO_RENDER_INIT,
    MM_INDEX_VENDOR_CLEAR_BUFFER,
    MM_INDEX_VENDOR_VIDEO_RENDER_SCREEN_SIZE,
    MM_INDEX_VENDOR_AUDIO_RENDER_VOLUME,
    MM_INDEX_VENDOR_DEMUXER_SKIP_TRACK,
    MM_INDEX_VENDOR_VIDEO_RENDER_CAPTURE,
    MM_INDEX_VENDOR_MUXER_RECORD_FILE_INFO,
    MM_INDEX_VENDOR_VIDEO_ENC_CAPTURE,
} MM_INDEX_TYPE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
/* File EOF */