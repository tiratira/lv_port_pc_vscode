#include <stdio.h>
#include "global_def.h"
#include "drink_type.h"
#include "ui_style.h"
#include "route.h"

lv_obj_t* cute_settings_view = 0;

static void on_back_clicked(lv_event_t* e) {
  navigate_to_view("cute_main_menu_view", 0);
}

static void on_bean_change_clicked(lv_event_t* e) {
  navigate_to_view("cute_bean_mode_view", 0);
}

lv_obj_t* cute_settings_view_init(void* args) {
  cute_settings_view = lv_obj_create(NULL);
  lv_obj_t* this = cute_settings_view;

  lv_obj_set_size(cute_settings_view, SCREEN_WIDTH, SCREEN_HEIGHT);
  lv_obj_set_style_bg_color(cute_settings_view, lv_color_hex(0xF3EADB), 0);

  UI_TEXT_XL(cute_settings_view, "设置", 51, 43, UI_BLACK);
  lv_obj_t* cat = lv_image_create(cute_settings_view);
  lv_image_set_src(cat, LVGL_IMAGE_PATH("cute_settings_view/corner_cat.png"));
  lv_obj_set_pos(cat, 783, 34);

  lv_obj_t* menu = lv_image_create(cute_settings_view);
  lv_image_set_src(menu, LVGL_IMAGE_PATH("cute_settings_view/menu_big.png"));
  lv_obj_set_pos(menu, 63, 193);

  lv_obj_t* back_btn = lv_btn_create(cute_settings_view);
  lv_obj_remove_style_all(back_btn);
  lv_obj_add_style(back_btn, &btn_style_normal, 0);
  lv_obj_set_size(back_btn, 51, 51);
  lv_obj_set_pos(back_btn, 42, 119);

  lv_obj_t* back_icon_img = lv_image_create(back_btn);
  lv_image_set_src(back_icon_img, LVGL_IMAGE_PATH("common/icon_back.png"));
  lv_obj_align(back_icon_img, LV_ALIGN_CENTER, 0, 0);

  lv_obj_add_event_cb(back_btn, on_back_clicked, LV_EVENT_CLICKED, NULL);

  lv_obj_t* bean_change_btn = lv_button_create(cute_settings_view);
  lv_obj_remove_style_all(bean_change_btn);
  lv_obj_set_size(bean_change_btn, 204, 213);
  lv_obj_set_pos(bean_change_btn, 63, 193);

  lv_obj_add_event_cb(bean_change_btn, on_bean_change_clicked, LV_EVENT_CLICKED,
                      0);

  return cute_settings_view;
}