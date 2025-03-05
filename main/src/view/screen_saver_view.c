#include "global_def.h"
#include "lvgl.h"
#include "stdio.h"

#define CHANGE_IMG_TIME 5000

lv_obj_t* screen_saver_view = 0;
lv_obj_t* bg = 0;
lv_obj_t* energy_saving_img = 0;
lv_obj_t* bg_mask_img = 0;
lv_obj_t* touch_img = 0;

const char* img_list[] = {
    LVGL_IMAGE_PATH("scr_saver_images/img_scr_saver_1.png"),
    LVGL_IMAGE_PATH("scr_saver_images/img_scr_saver_3.png"),
    LVGL_IMAGE_PATH("scr_saver_images/img_scr_saver_2.png"),
    LVGL_IMAGE_PATH("scr_saver_images/img_scr_saver_4.png"),
    LVGL_IMAGE_PATH("scr_saver_images/img_scr_saver_5.png"),
};

void timer_callback(lv_timer_t* timer) {
  static int index = 1;
  printf("%d\n", index);
  // 在这里编写定时器到期时要执行的代码
  lv_image_set_src(bg, img_list[index]);
  index++;
  if (index >= 5) {
    index = 0;
  }
}

lv_obj_t* screen_saver_view_init(void) {
  screen_saver_view = lv_obj_create(NULL);
  lv_obj_set_size(screen_saver_view, 1280, 480);
  lv_obj_set_style_bg_color(screen_saver_view, lv_color_hex(0x000000), 0);

  bg = lv_image_create(screen_saver_view);
  lv_image_set_src(bg, LVGL_IMAGE_PATH("scr_saver_images/img_scr_saver_1.png"));
  lv_obj_center(bg);

  bg_mask_img = lv_obj_create(screen_saver_view);
  lv_obj_set_size(bg_mask_img, 1280, 480);
  lv_obj_set_style_bg_color(bg_mask_img, lv_color_hex(0x000000),
                            0);                  // 设置背景颜色为黑色
  lv_obj_set_style_bg_opa(bg_mask_img, 225, 0);  // 设置背景透明度为不透明
  lv_obj_center(bg_mask_img);

  energy_saving_img = lv_image_create(screen_saver_view);
  lv_image_set_src(
      energy_saving_img,
      LVGL_IMAGE_PATH("scr_saver_images/img_scr_energysaving.png"));
  lv_obj_center(energy_saving_img);

  touch_img = lv_image_create(screen_saver_view);
  lv_image_set_src(touch_img,
                   LVGL_IMAGE_PATH("scr_saver_images/img_scr_touch.png"));
  lv_obj_align(touch_img, LV_ALIGN_TOP_RIGHT, -38, 37);

  lv_timer_t* timer = lv_timer_create(timer_callback, CHANGE_IMG_TIME, NULL);
  return screen_saver_view;
}