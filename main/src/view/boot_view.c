#include "global_def.h"
#include "lvgl.h"
#include "stdio.h"

lv_obj_t* boot_view = 0;
lv_obj_t* img_boot = 0;

void boot_view_init(void) {
  boot_view = lv_obj_create(NULL);
  lv_obj_set_size(boot_view, 1280, 480);
  lv_obj_set_style_bg_color(boot_view, lv_color_hex(0x000000), 0);

  img_boot = lv_image_create(boot_view);
  lv_image_set_src(img_boot,
                   LVGL_IMAGE_PATH("boot_view_images/img_boot_view.png"));
  lv_obj_center(img_boot);
}