/*
 * Copyright (C) 2024 ArtInChip Technology Co., Ltd.
 *
 * This file was generated by AiUIBuilder
 * AiUIBuilder version: v1.0.0
 */

#ifndef _UI_OBJECTS
#define _UI_OBJECTS

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct {
    lv_obj_t *obj;
    lv_obj_t *button_1;
} screen_t;


typedef struct {
    bool auto_del;
    screen_t screen;

} ui_manager_t;

static inline void ui_manager_init(ui_manager_t *ui, bool auto_del)
{
    memset(ui, 0 , sizeof(ui_manager_t));
    ui->auto_del = auto_del;
}

static inline screen_t *screen_get(ui_manager_t *ui)
{
    return &ui->screen;
}


void screen_create(ui_manager_t *ui);

extern lv_font_t *montserratmedium_16;


extern ui_manager_t ui_manager;

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif // _UI_OBJECTS