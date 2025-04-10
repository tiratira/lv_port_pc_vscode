#include "global_def.h"
#include "drink_type.h"
#include "lvgl.h"

lv_obj_t* cute_coffee_config_view = 0;

extern lv_font_t* lanapixel_sm;
extern lv_font_t* lanapixel_md;
extern lv_font_t* lanapixel_xl;

static drink_item_data_t* drink_item = 0;

static void on_back_clicked(lv_event_t* e) {
  
}

lv_obj_t* cute_coffee_config_view_init(void* args) {
  drink_item = (drink_item_data_t*)args;
  if (drink_item == 0) {
    return 0;
  }
  cute_coffee_config_view = lv_obj_create(NULL);
  lv_obj_set_size(cute_coffee_config_view, SCREEN_WIDTH, SCREEN_HEIGHT);
  lv_obj_set_style_bg_color(cute_coffee_config_view, lv_color_hex(0xF3EADB), 0);

  lv_obj_t* dec_rect = lv_obj_create(cute_coffee_config_view);
  lv_obj_set_size(dec_rect, 798, 289);
  lv_obj_set_style_bg_color(dec_rect, lv_color_hex(0xB5B5D1), 0);
  lv_obj_set_style_radius(dec_rect, 40, 0);
  lv_obj_set_style_border_width(dec_rect, 0, 0);
  lv_obj_set_pos(dec_rect, 143, 182);

  lv_obj_t* side_cat = lv_image_create(cute_coffee_config_view);
  lv_image_set_src(side_cat,
                   LVGL_IMAGE_PATH("cute_coffee_config/side_cat.png"));
  lv_obj_set_pos(side_cat, 695, 90);

  lv_obj_t* title1 = lv_label_create(cute_coffee_config_view);
  lv_label_set_text(title1, "早上好！来杯咖啡开启活力满满的一天！");
  lv_obj_set_style_text_font(title1, lanapixel_md, 0);
  lv_obj_set_style_text_color(title1, lv_color_black(), 0);
  lv_obj_set_pos(title1, 52, 45);

  lv_obj_t* title2 = lv_label_create(cute_coffee_config_view);
  lv_label_set_text(title2, "请选择您的偏好设置");
  lv_obj_set_style_text_font(title2, lanapixel_sm, 0);
  lv_obj_set_style_text_color(title2, lv_color_hex(0x9F73B3), 0);
  lv_obj_set_pos(title2, 52, 80);

  lv_obj_t* coffee_preview = lv_image_create(cute_coffee_config_view);
  lv_image_set_src(coffee_preview, drink_item->icon_xl_path);
  lv_obj_set_pos(coffee_preview, 34, 192);

  lv_obj_t* coffee_title_1 = lv_label_create(cute_coffee_config_view);
  lv_label_set_text(coffee_title_1, drink_item->title_cn);
  lv_obj_set_style_text_font(coffee_title_1, lanapixel_xl, 0);
  lv_obj_set_style_text_color(coffee_title_1, lv_color_black(), 0);
  lv_obj_set_pos(coffee_title_1, 267, 201);

  lv_obj_t* coffee_title_2 = lv_label_create(cute_coffee_config_view);
  lv_label_set_text(coffee_title_2, drink_item->title_en);
  lv_obj_set_style_text_font(coffee_title_2, lanapixel_md, 0);
  lv_obj_set_style_text_color(coffee_title_2, lv_color_hex(0x6E6E6E), 0);
  lv_obj_set_pos(coffee_title_2, 267, 242);

  lv_obj_t* back_btn = lv_btn_create(cute_coffee_config_view);
  lv_obj_set_size(back_btn, 51, 51);
  lv_obj_set_style_bg_color(back_btn, lv_color_hex(0xB5B5D1), 0);
  lv_obj_set_style_radius(back_btn, 26, 0);
  lv_obj_set_style_border_width(back_btn, 0, 0);
  lv_obj_set_pos(back_btn, 42, 119);
  lv_obj_set_style_shadow_opa(back_btn, LV_OPA_TRANSP, 0);

  lv_obj_t* back_icon_img = lv_image_create(back_btn);
  lv_image_set_src(back_icon_img, LVGL_IMAGE_PATH("common/icon_back.png"));
  lv_obj_align(back_icon_img, LV_ALIGN_CENTER, 0, 0);

  return cute_coffee_config_view;
}