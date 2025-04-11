#pragma once
#include <src/misc/lv_area.h>
#include "lvgl.h"

extern lv_style_t button_style;
extern lv_style_t slider_style;
extern lv_style_t icon_style;

extern lv_style_t btn_style_normal;
extern lv_style_t btn_style_primary;

extern lv_font_t *lanapixel_sm;
extern lv_font_t *lanapixel_md;
extern lv_font_t *lanapixel_xl;
extern lv_font_t *lanapixel_xxl;

#define UI_BLACK lv_color_black()
#define UI_WHITE lv_color_white()
#define UI_PRIMARY lv_color_hex(0xAB86BA)
#define UI_SECONDARY lv_color_hex(0xB5B5D1)
#define UI_BG lv_color_hex(0xE1E1E3)
#define COLOR(x) lv_color_hex(0x##x)

#define UI_TEXT_XL(_parent, _text, _x, _y, _color)        \
  {                                                       \
    lv_obj_t *__title = lv_label_create(_parent);         \
    lv_obj_set_pos(__title, _x, _y);                      \
    lv_label_set_text(__title, _text);                    \
    lv_obj_set_style_text_font(__title, lanapixel_xl, 0); \
    lv_obj_set_style_text_color(__title, _color, 0);      \
  }

#define UI_TEXT_MD(_parent, _text, _x, _y, _color)        \
  {                                                       \
    lv_obj_t *__title = lv_label_create(_parent);         \
    lv_obj_set_pos(__title, _x, _y);                      \
    lv_label_set_text(__title, _text);                    \
    lv_obj_set_style_text_font(__title, lanapixel_md, 0); \
    lv_obj_set_style_text_color(__title, _color, 0);      \
  }

#define UI_TEXT_SM(_parent, _text, _x, _y, _color)        \
  {                                                       \
    lv_obj_t *__title = lv_label_create(_parent);         \
    lv_obj_set_pos(__title, _x, _y);                      \
    lv_label_set_text(__title, _text);                    \
    lv_obj_set_style_text_font(__title, lanapixel_sm, 0); \
    lv_obj_set_style_text_color(__title, _color, 0);      \
  }

lv_obj_t *ui_text(lv_obj_t *parent, const char *text, lv_font_t *font,
                  lv_align_t align, lv_coord_t x, lv_coord_t y,
                  lv_color_t color);

// 初始化所有的样式
void ui_style_init(void);