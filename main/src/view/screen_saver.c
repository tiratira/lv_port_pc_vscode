#include "global_def.h"
#include "lvgl.h"

lv_obj_t* screen_saver = 0;

void screen_saver_init(void) {
  screen_saver = lv_obj_create(NULL);
  lv_obj_set_size(screen_saver, 1280, 480);
  lv_obj_set_style_bg_color(screen_saver, lv_color_hex(0x000000), 0);
  lv_obj_t* bg = lv_image_create(screen_saver);
  lv_image_set_src(bg, LVGL_IMAGE_PATH(img_scr_saver_1.png));
  lv_obj_center(bg);
}