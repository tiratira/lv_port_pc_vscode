#include <src/misc/lv_style.h>
#include <src/misc/lv_style_gen.h>
#include "lvgl.h"

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_26)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_30)

lv_style_t button_style;
lv_style_t slider_style;
lv_style_t icon_style;

void ui_style_init(void) { 
  lv_style_init(&button_style);
  // 创建一个217, 54大小的矩形
  lv_style_set_size(&button_style, 217, 54);
  // 设置背景颜色
  lv_style_set_bg_color(&button_style, lv_color_hex(0x221C17));
  // 设置边框颜色
  lv_style_set_border_color(&button_style, lv_color_hex(0x45392F));
  // 设置边框宽度
  lv_style_set_border_width(&button_style, 1);
  // 设置边框圆角
  lv_style_set_radius(&button_style, 4);
  // 设置阴影颜色
  lv_style_set_shadow_color(&button_style, lv_color_hex(0x000000));
  
  lv_style_set_text_font(&button_style, &HarmonyOS_Sans_SC_Regular_30);
}