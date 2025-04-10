#pragma once
#include "lvgl.h"

extern lv_style_t button_style;
extern lv_style_t slider_style;
extern lv_style_t icon_style;

extern lv_style_t btn_style_normal;
extern lv_style_t btn_style_primary;

// 初始化所有的样式
void ui_style_init(void);