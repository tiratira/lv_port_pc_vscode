#include <src/core/lv_obj_pos.h>
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
lv_font_t *lanapixel_xxl;

lv_obj_t *ui_text(lv_obj_t *parent, const char *text, lv_font_t *font,
                  lv_align_t align, lv_coord_t x, lv_coord_t y,
                  lv_color_t color) {
  lv_obj_t *title = lv_label_create(parent);
  lv_obj_align(title, align, x, y);
  lv_label_set_text(title, text);
  lv_obj_set_style_text_font(title, lanapixel_sm, 0);
  lv_obj_set_style_text_color(title, color, 0);
  return title;
}

lv_obj_t *ui_image(lv_obj_t *parent, const char *path, int x, int y) {
  lv_obj_t *img = lv_img_create(parent);
  lv_img_set_src(img, path);
  lv_obj_set_pos(img, x, y);
  return img;
}

void ui_style_init(void) {
  // lanapixel_sm =
  //     lv_tiny_ttf_create_file("A:" LVGL_FONT_PATH("LanaPixel.ttf"), 16);
  // lanapixel_md =
  //     lv_tiny_ttf_create_file("A:" LVGL_FONT_PATH("LanaPixel.ttf"), 20);
  // lanapixel_xl =
  //     lv_tiny_ttf_create_file("A:" LVGL_FONT_PATH("LanaPixel.ttf"), 32);
  // lanapixel_xxl =
  //     lv_tiny_ttf_create_file("A:" LVGL_FONT_PATH("LanaPixel.ttf"), 64);

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