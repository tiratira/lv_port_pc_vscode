#include <stdio.h>
#include "global_def.h"
#include "drink_type.h"
#include "ui_style.h"
#include "route.h"

lv_obj_t* cute_bean_mode_view = 0;

static lv_obj_t* left_image;
static lv_obj_t* right_image;
static lv_obj_t* left_btn;
static lv_obj_t* right_btn;
static lv_obj_t* sel_flash;

static int mode = 0;
static const int flash_x[] = {139, 522};

static void on_back_clicked(lv_event_t* e) {
  navigate_to_view("cute_settings_view", 0);
}

static void on_mode_change_clicked(lv_event_t* e) {
  mode = (size_t)lv_event_get_user_data(e);
  lv_obj_set_style_bg_color(
      left_btn, mode == 0 ? lv_color_hex(0xAB86BA) : lv_color_hex(0xE1E1E3), 0);
  lv_obj_set_style_bg_color(
      right_btn, mode == 1 ? lv_color_hex(0xAB86BA) : lv_color_hex(0xE1E1E3),
      0);
  lv_obj_set_pos(sel_flash, flash_x[mode], 228);
}

static void on_next_clicked(lv_event_t* e) {
  navigate_to_view("cute_powder_detail_view", 0);
}

lv_obj_t* cute_bean_mode_view_init(void* args) {
  cute_bean_mode_view = lv_obj_create(NULL);
  lv_obj_t* this = cute_bean_mode_view;

  lv_obj_set_size(cute_bean_mode_view, SCREEN_WIDTH, SCREEN_HEIGHT);
  lv_obj_set_style_bg_color(cute_bean_mode_view, lv_color_hex(0xF3EADB), 0);

  UI_TEXT_XL(cute_bean_mode_view, "咖啡豆/粉 模式切换", 51, 43, UI_BLACK);

  lv_obj_t* back_btn = lv_btn_create(cute_bean_mode_view);
  lv_obj_remove_style_all(back_btn);
  lv_obj_add_style(back_btn, &btn_style_normal, 0);
  lv_obj_set_size(back_btn, 51, 51);
  lv_obj_set_pos(back_btn, 42, 119);

  lv_obj_t* back_icon_img = lv_image_create(back_btn);
  lv_image_set_src(back_icon_img, LVGL_IMAGE_PATH("common/icon_back.png"));
  lv_obj_align(back_icon_img, LV_ALIGN_CENTER, 0, 0);

  lv_obj_add_event_cb(back_btn, on_back_clicked, LV_EVENT_CLICKED, NULL);

  left_image =
      ui_image(cute_bean_mode_view,
               LVGL_IMAGE_PATH("cute_bean_mode/mode_bean.png"), 217, 215);

  lv_obj_add_flag(left_image, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_event_cb(left_image, on_mode_change_clicked, LV_EVENT_CLICKED, 0);

  right_image =
      ui_image(cute_bean_mode_view,
               LVGL_IMAGE_PATH("cute_bean_mode/mode_powder.png"), 583, 218);

  lv_obj_add_flag(right_image, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_event_cb(right_image, on_mode_change_clicked, LV_EVENT_CLICKED,
                      (void*)1);

  left_btn = lv_obj_create(cute_bean_mode_view);
  lv_obj_set_size(left_btn, 50, 50);
  lv_obj_set_pos(left_btn, 289, 455);
  lv_obj_set_style_border_width(left_btn, 0, 0);
  lv_obj_set_style_bg_color(
      left_btn, mode == 0 ? lv_color_hex(0xAB86BA) : lv_color_hex(0xE1E1E3), 0);
  lv_obj_set_style_radius(left_btn, 25, 0);

  lv_obj_add_flag(left_btn, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_event_cb(left_btn, on_mode_change_clicked, LV_EVENT_CLICKED, 0);

  right_btn = lv_obj_create(cute_bean_mode_view);
  lv_obj_set_size(right_btn, 50, 50);
  lv_obj_set_pos(right_btn, 666, 455);
  lv_obj_set_style_border_width(right_btn, 0, 0);
  lv_obj_set_style_bg_color(
      right_btn, mode == 1 ? lv_color_hex(0xAB86BA) : lv_color_hex(0xE1E1E3),
      0);
  lv_obj_set_style_radius(right_btn, 25, 0);

  lv_obj_add_flag(right_btn, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_event_cb(right_btn, on_mode_change_clicked, LV_EVENT_CLICKED,
                      (void*)1);

  sel_flash = lv_image_create(cute_bean_mode_view);
  lv_image_set_src(sel_flash,
                   LVGL_IMAGE_PATH("cute_bean_mode/select_flash.png"));
  lv_obj_set_pos(sel_flash, flash_x[mode], 228);

  lv_obj_t* next_btn = lv_btn_create(cute_bean_mode_view);
  lv_obj_remove_style_all(next_btn);
  lv_obj_add_style(next_btn, &btn_style_normal, 0);
  lv_obj_set_size(next_btn, 123, 59);
  lv_obj_set_pos(next_btn, 818, 500);
  lv_obj_t* btn_img = lv_image_create(next_btn);
  lv_image_set_src(btn_img, LVGL_IMAGE_PATH("cute_main_menu/icon_next.png"));
  lv_obj_center(btn_img);

  lv_obj_add_event_cb(next_btn, on_next_clicked, LV_EVENT_CLICKED, NULL);

  return cute_bean_mode_view;
}