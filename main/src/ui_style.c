#include <src/misc/lv_color.h>
#include <src/misc/lv_style.h>
#include "lvgl.h"
#include "global_def.h"

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_26)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_30)

lv_style_t button_style;
lv_style_t slider_style;
lv_style_t icon_style;

lv_style_t btn_style_normal;
lv_style_t btn_style_primary;

lv_font_t *lanapixel_sm;
lv_font_t *lanapixel_md;
lv_font_t *lanapixel_xl;

void ui_style_init(void) {
  lanapixel_sm =
      lv_tiny_ttf_create_file("A:" LVGL_FONT_PATH("LanaPixel.ttf"), 16);
  lanapixel_md =
      lv_tiny_ttf_create_file("A:" LVGL_FONT_PATH("LanaPixel.ttf"), 20);
  lanapixel_xl =
      lv_tiny_ttf_create_file("A:" LVGL_FONT_PATH("LanaPixel.ttf"), 32);

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

  lv_style_init(&btn_style_normal);
  lv_style_set_bg_color(&btn_style_normal, lv_color_hex(0xB5B5D1));
  lv_style_set_bg_opa(&btn_style_normal, LV_OPA_100);
  lv_style_set_radius(&btn_style_normal, LV_RADIUS_CIRCLE);
  lv_style_set_text_color(&btn_style_normal, lv_color_hex(0xA27AB6));
  lv_style_set_text_font(&btn_style_normal, lanapixel_md);

  lv_style_init(&btn_style_primary);
  lv_style_set_bg_color(&btn_style_primary, lv_color_hex(0xA27AB6));
  lv_style_set_bg_opa(&btn_style_primary, LV_OPA_100);
  lv_style_set_radius(&btn_style_primary, LV_RADIUS_CIRCLE);
  lv_style_set_text_color(&btn_style_primary, lv_color_white());
  lv_style_set_text_font(&btn_style_primary, lanapixel_md);
}