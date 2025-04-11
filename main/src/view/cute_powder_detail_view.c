#include <stdio.h>
#include "global_def.h"
#include "drink_type.h"
#include "ui_style.h"
#include "route.h"

lv_obj_t* cute_powder_detail_view = 0;

static void on_back_clicked(lv_event_t* e) {
  navigate_to_view("cute_bean_mode_view", 0);
}

lv_obj_t* cute_powder_detail_view_init(void* args) {
  cute_powder_detail_view = lv_obj_create(NULL);
  lv_obj_t* this = cute_powder_detail_view;

  lv_obj_set_size(cute_powder_detail_view, SCREEN_WIDTH, SCREEN_HEIGHT);
  lv_obj_set_style_bg_color(cute_powder_detail_view, lv_color_hex(0xF3EADB), 0);

  UI_TEXT_XL(cute_powder_detail_view, "咖啡粉模式", 51, 43, UI_BLACK);

  lv_obj_t* back_btn = lv_btn_create(cute_powder_detail_view);
  lv_obj_remove_style_all(back_btn);
  lv_obj_add_style(back_btn, &btn_style_normal, 0);
  lv_obj_set_size(back_btn, 51, 51);
  lv_obj_set_pos(back_btn, 42, 119);

  lv_obj_t* back_icon_img = lv_image_create(back_btn);
  lv_image_set_src(back_icon_img, LVGL_IMAGE_PATH("common/icon_back.png"));
  lv_obj_align(back_icon_img, LV_ALIGN_CENTER, 0, 0);

  lv_obj_add_event_cb(back_btn, on_back_clicked, LV_EVENT_CLICKED, NULL);

  ui_image(this, LVGL_IMAGE_PATH("cute_make_coffee/machine_anim_1.png"), 146,
           212);

  UI_TEXT_MD(this, "请打开咖啡粉盖，加入咖啡粉", 584, 287, UI_BLACK);
  UI_TEXT_MD(this, "(最多加入16克咖啡粉)", 584, 307, UI_BLACK);
  UI_TEXT_MD(this, "完成后，点击“确定”按钮", 584, 347, UI_BLACK);

  return cute_powder_detail_view;
}