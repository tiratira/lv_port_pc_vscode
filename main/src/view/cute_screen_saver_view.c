#include <stdint.h>
#include "lvgl.h"
#include "global_def.h"

extern lv_font_t* lanapixel_sm;
extern lv_font_t* lanapixel_md;
extern lv_font_t* lanapixel_xl;

lv_obj_t* cute_screen_saver_view = 0;

lv_obj_t* flower_1 = 0;
lv_obj_t* flower_2 = 0;
lv_obj_t* flower_3 = 0;
lv_obj_t* flower_4 = 0;
lv_obj_t* flower_5 = 0;
lv_obj_t* cat = 0;

static const char** cat_frames = (const char*[]){
    LVGL_IMAGE_PATH("cute_screen_saver/cat1.png"),
    LVGL_IMAGE_PATH("cute_screen_saver/cat2.png"),
    LVGL_IMAGE_PATH("cute_screen_saver/cat3.png"),
    LVGL_IMAGE_PATH("cute_screen_saver/cat4.png"),
};

static void animate_timer_cb(lv_timer_t* timer) {
  static int32_t frame = 0;
  frame += 1;

  if (frame >= 4) {
    frame = 0;
  }

  lv_img_set_src(cat, cat_frames[frame]);

  int32_t rotation = frame * 450;

  lv_image_set_rotation(flower_1, rotation);
  lv_image_set_rotation(flower_2, rotation);
  lv_image_set_rotation(flower_3, rotation);
  lv_image_set_rotation(flower_4, rotation);
  lv_image_set_rotation(flower_5, rotation);
}

lv_obj_t* cute_screen_saver_view_init(void) {
  cute_screen_saver_view = lv_obj_create(NULL);
  lv_obj_set_size(cute_screen_saver_view, SCREEN_WIDTH, SCREEN_HEIGHT);

  lv_obj_t* img = lv_img_create(cute_screen_saver_view);
  lv_img_set_src(img, LVGL_IMAGE_PATH("cute_screen_saver/bg.png"));
  lv_obj_set_size(img, SCREEN_WIDTH, SCREEN_HEIGHT);

  flower_1 = lv_img_create(cute_screen_saver_view);
  lv_img_set_src(flower_1, LVGL_IMAGE_PATH("cute_screen_saver/flower1.png"));
  lv_obj_set_pos(flower_1, 82, 47);

  flower_2 = lv_img_create(cute_screen_saver_view);
  lv_img_set_src(flower_2, LVGL_IMAGE_PATH("cute_screen_saver/flower2.png"));
  lv_obj_set_pos(flower_2, 785, 67);

  flower_3 = lv_img_create(cute_screen_saver_view);
  lv_img_set_src(flower_3, LVGL_IMAGE_PATH("cute_screen_saver/flower3.png"));
  lv_obj_set_pos(flower_3, 160, 374);

  flower_4 = lv_img_create(cute_screen_saver_view);
  lv_img_set_src(flower_4, LVGL_IMAGE_PATH("cute_screen_saver/flower4.png"));
  lv_obj_set_pos(flower_4, 707, 472);

  flower_5 = lv_img_create(cute_screen_saver_view);
  lv_img_set_src(flower_5, LVGL_IMAGE_PATH("cute_screen_saver/flower5.png"));
  lv_obj_set_pos(flower_5, 928, 514);

  cat = lv_image_create(cute_screen_saver_view);
  lv_img_set_src(cat, LVGL_IMAGE_PATH("cute_screen_saver/cat1.png"));
  lv_obj_set_pos(cat, 462, 262);

  lv_obj_t* label = lv_label_create(cute_screen_saver_view);
  lv_label_set_text(label, "点击屏幕任意位置");
  lv_obj_set_pos(label, 383, 505);
  lv_obj_set_style_text_font(label, lanapixel_xl, 0);
  lv_obj_set_style_text_color(label, lv_color_hex(0x733490), 0);

  lv_timer_t* timer = lv_timer_create(animate_timer_cb, 1000, NULL);

  return cute_screen_saver_view;
}