#include <src/core/lv_obj_event.h>
#include <src/core/lv_obj_style.h>
#include <src/misc/lv_event.h>
#include <src/widgets/image/lv_image.h>
#include "global_def.h"
#include "drink_type.h"
#include "lvgl.h"
#include "ui_style.h"
#include "route.h"

lv_obj_t* cute_coffee_config_view = 0;

extern lv_font_t* lanapixel_sm;
extern lv_font_t* lanapixel_md;
extern lv_font_t* lanapixel_xl;

static drink_item_data_t* drink_item = 0;

static lv_style_t style_mode_selected;
static lv_style_t style_mode_normal;

static lv_obj_t* drop_mode_btns[3] = {0};
static lv_obj_t* temp_lvl_btns[3] = {0};
// static const int mode_btn_x_pos[3] = {471, 594, 716};

static int pre_cook_value = 2;
static int drop_mode_value = 0;
static int temp_lvl_value = 1;

static void on_drop_mode_clicked(lv_event_t* e) {
  lv_obj_remove_style(drop_mode_btns[drop_mode_value], &style_mode_selected, 0);
  lv_obj_add_style(drop_mode_btns[drop_mode_value], &style_mode_normal, 0);
  drop_mode_value = (size_t)lv_event_get_user_data(e);
  lv_obj_remove_style(drop_mode_btns[drop_mode_value], &style_mode_normal, 0);
  lv_obj_add_style(drop_mode_btns[drop_mode_value], &style_mode_selected, 0);
}

static void on_temp_lvl_clicked(lv_event_t* e) {
  lv_obj_remove_style(temp_lvl_btns[temp_lvl_value], &style_mode_selected, 0);
  lv_obj_add_style(temp_lvl_btns[temp_lvl_value], &style_mode_normal, 0);
  temp_lvl_value = (size_t)lv_event_get_user_data(e);
  lv_obj_remove_style(temp_lvl_btns[temp_lvl_value], &style_mode_normal, 0);
  lv_obj_add_style(temp_lvl_btns[temp_lvl_value], &style_mode_selected, 0);
}

static void on_back_clicked(lv_event_t* e) {
  navigate_to_view("cute_main_menu_view", 0);
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
  lv_image_set_scale(coffee_preview, 200);
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

  lv_obj_add_event_cb(back_btn, on_back_clicked, LV_EVENT_CLICKED, NULL);

  lv_obj_t* cui_text = lv_image_create(cute_coffee_config_view);
  lv_image_set_src(cui_text, LVGL_IMAGE_PATH("cute_coffee_config/萃.png"));
  lv_obj_set_pos(cui_text, 267, 355);

  lv_obj_t* ycz_text = lv_label_create(cute_coffee_config_view);
  lv_label_set_text(ycz_text, "预冲煮");
  lv_obj_set_style_text_font(ycz_text, lanapixel_md, 0);
  lv_obj_set_style_text_color(ycz_text, lv_color_black(), 0);
  lv_obj_set_pos(ycz_text, 267, 297);

  lv_obj_t* cuiqu_text = lv_label_create(cute_coffee_config_view);
  lv_label_set_text(cuiqu_text, "取方式");
  lv_obj_set_style_text_font(cuiqu_text, lanapixel_md, 0);
  lv_obj_set_style_text_color(cuiqu_text, lv_color_black(), 0);
  lv_obj_set_pos(cuiqu_text, 288, 354);

  lv_obj_t* temp_text = lv_label_create(cute_coffee_config_view);
  lv_label_set_text(temp_text, "温度等级");
  lv_obj_set_style_text_font(temp_text, lanapixel_md, 0);
  lv_obj_set_style_text_color(temp_text, lv_color_black(), 0);
  lv_obj_set_pos(temp_text, 267, 408);

  lv_obj_t* pre_cook_indicator = lv_image_create(cute_coffee_config_view);
  lv_image_set_src(pre_cook_indicator,
                   LVGL_IMAGE_PATH("cute_coffee_config/dimension.png"));
  lv_obj_set_pos(pre_cook_indicator, 408, 290);

  lv_obj_t* pre_cook_slider = lv_slider_create(cute_coffee_config_view);
  lv_obj_set_size(pre_cook_slider, 368, 31);
  lv_obj_set_pos(pre_cook_slider, 471, 293);
  lv_obj_set_style_bg_color(pre_cook_slider, lv_color_hex(0xD9D9D9),
                            LV_PART_MAIN);
  lv_obj_set_style_bg_color(pre_cook_slider, lv_color_hex(0xAB86BA),
                            LV_PART_INDICATOR);
  lv_obj_set_style_bg_opa(pre_cook_slider, LV_OPA_100, LV_PART_MAIN);
  lv_obj_set_style_bg_opa(pre_cook_slider, LV_OPA_TRANSP, LV_PART_KNOB);

  lv_slider_set_range(pre_cook_slider, 0, 5);
  lv_slider_set_value(pre_cook_slider, pre_cook_value, LV_ANIM_OFF);

  static lv_style_t style_indicator;
  lv_style_init(&style_indicator);
  lv_style_set_bg_color(&style_indicator, lv_color_hex(0xD9D9D9));
  lv_style_set_bg_opa(&style_indicator, LV_OPA_100);
  lv_style_set_radius(&style_indicator, LV_RADIUS_CIRCLE);
  lv_style_set_size(&style_indicator, 368, 31);

  lv_obj_t* drop_method_bg = lv_obj_create(cute_coffee_config_view);
  lv_obj_remove_style_all(drop_method_bg);
  lv_obj_add_style(drop_method_bg, &style_indicator, 0);
  lv_obj_set_pos(drop_method_bg, 471, 354);

  lv_obj_t* temp_level_bg = lv_obj_create(cute_coffee_config_view);
  lv_obj_remove_style_all(temp_level_bg);
  lv_obj_add_style(temp_level_bg, &style_indicator, 0);
  lv_obj_set_pos(temp_level_bg, 471, 405);

  lv_style_init(&style_mode_selected);
  lv_style_set_bg_color(&style_mode_selected, lv_color_hex(0xAB86BA));
  lv_style_set_bg_opa(&style_mode_selected, LV_OPA_100);
  lv_style_set_radius(&style_mode_selected, LV_RADIUS_CIRCLE);
  lv_style_set_size(&style_mode_selected, 122, 31);
  lv_style_set_text_color(&style_mode_selected, lv_color_white());
  lv_style_set_text_font(&style_mode_selected, lanapixel_md);

  lv_style_init(&style_mode_normal);
  lv_style_set_bg_color(&style_mode_normal, lv_color_hex(0xD9D9D9));
  lv_style_set_bg_opa(&style_mode_normal, LV_OPA_100);
  lv_style_set_radius(&style_mode_normal, LV_RADIUS_CIRCLE);
  lv_style_set_size(&style_mode_normal, 122, 31);
  lv_style_set_text_color(&style_mode_normal, lv_color_hex(0xA5A5A5));
  lv_style_set_text_font(&style_mode_normal, lanapixel_md);

  drop_mode_btns[0] = lv_btn_create(cute_coffee_config_view);
  lv_obj_remove_style_all(drop_mode_btns[0]);
  lv_obj_add_style(drop_mode_btns[0], &style_mode_selected, 0);
  lv_obj_set_pos(drop_mode_btns[0], 471, 354);
  lv_obj_t* btn_text = lv_label_create(drop_mode_btns[0]);
  lv_label_set_text(btn_text, "低温");
  lv_obj_center(btn_text);
  lv_obj_add_event_cb(drop_mode_btns[0], on_drop_mode_clicked, LV_EVENT_CLICKED,
                      (void*)0);

  drop_mode_btns[1] = lv_btn_create(cute_coffee_config_view);
  lv_obj_remove_style_all(drop_mode_btns[1]);
  lv_obj_add_style(drop_mode_btns[1], &style_mode_normal, 0);
  lv_obj_set_pos(drop_mode_btns[1], 594, 354);
  btn_text = lv_label_create(drop_mode_btns[1]);
  lv_label_set_text(btn_text, "中温");
  lv_obj_center(btn_text);
  lv_obj_add_event_cb(drop_mode_btns[1], on_drop_mode_clicked, LV_EVENT_CLICKED,
                      (void*)1);

  drop_mode_btns[2] = lv_btn_create(cute_coffee_config_view);
  lv_obj_remove_style_all(drop_mode_btns[2]);
  lv_obj_add_style(drop_mode_btns[2], &style_mode_normal, 0);
  lv_obj_set_pos(drop_mode_btns[2], 716, 354);
  btn_text = lv_label_create(drop_mode_btns[2]);
  lv_label_set_text(btn_text, "高温");
  lv_obj_center(btn_text);
  lv_obj_add_event_cb(drop_mode_btns[2], on_drop_mode_clicked, LV_EVENT_CLICKED,
                      (void*)2);

  temp_lvl_btns[0] = lv_btn_create(cute_coffee_config_view);
  lv_obj_remove_style_all(temp_lvl_btns[0]);
  lv_obj_add_style(temp_lvl_btns[0], &style_mode_normal, 0);
  lv_obj_set_pos(temp_lvl_btns[0], 471, 405);
  btn_text = lv_label_create(temp_lvl_btns[0]);
  lv_label_set_text(btn_text, "常规");
  lv_obj_center(btn_text);
  lv_obj_add_event_cb(temp_lvl_btns[0], on_temp_lvl_clicked, LV_EVENT_CLICKED,
                      (void*)0);

  temp_lvl_btns[1] = lv_btn_create(cute_coffee_config_view);
  lv_obj_remove_style_all(temp_lvl_btns[1]);
  lv_obj_add_style(temp_lvl_btns[1], &style_mode_selected, 0);
  lv_obj_set_pos(temp_lvl_btns[1], 594, 405);
  btn_text = lv_label_create(temp_lvl_btns[1]);
  lv_label_set_text(btn_text, "加浓");
  lv_obj_center(btn_text);
  lv_obj_add_event_cb(temp_lvl_btns[1], on_temp_lvl_clicked, LV_EVENT_CLICKED,
                      (void*)1);

  temp_lvl_btns[2] = lv_btn_create(cute_coffee_config_view);
  lv_obj_remove_style_all(temp_lvl_btns[2]);
  lv_obj_add_style(temp_lvl_btns[2], &style_mode_normal, 0);
  lv_obj_set_pos(temp_lvl_btns[2], 716, 405);
  btn_text = lv_label_create(temp_lvl_btns[2]);
  lv_label_set_text(btn_text, "特浓");
  lv_obj_center(btn_text);
  lv_obj_add_event_cb(temp_lvl_btns[2], on_temp_lvl_clicked, LV_EVENT_CLICKED,
                      (void*)2);

  lv_obj_t* close_btn = lv_btn_create(cute_coffee_config_view);
  lv_obj_remove_style_all(close_btn);
  lv_obj_add_style(close_btn, &btn_style_primary, 0);
  lv_obj_set_size(close_btn, 113, 59);
  lv_obj_set_pos(close_btn, 144, 500);
  lv_obj_t* btn_img = lv_image_create(close_btn);
  lv_image_set_src(btn_img, LVGL_IMAGE_PATH("common/icon_close.png"));
  lv_obj_center(btn_img);

  lv_obj_t* like_btn = lv_btn_create(cute_coffee_config_view);
  lv_obj_remove_style_all(like_btn);
  lv_obj_add_style(like_btn, &btn_style_normal, 0);
  lv_obj_set_size(like_btn, 123, 59);
  lv_obj_set_pos(like_btn, 655, 500);
  btn_img = lv_image_create(like_btn);
  lv_image_set_src(btn_img, LVGL_IMAGE_PATH("common/icon_like.png"));
  lv_obj_center(btn_img);

  lv_obj_t* next_btn = lv_btn_create(cute_coffee_config_view);
  lv_obj_remove_style_all(next_btn);
  lv_obj_add_style(next_btn, &btn_style_normal, 0);
  lv_obj_set_size(next_btn, 123, 59);
  lv_obj_set_pos(next_btn, 818, 500);
  btn_img = lv_image_create(next_btn);
  lv_image_set_src(btn_img, LVGL_IMAGE_PATH("cute_main_menu/icon_next.png"));
  lv_obj_center(btn_img);

  return cute_coffee_config_view;
}