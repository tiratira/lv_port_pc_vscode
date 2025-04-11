#include <src/misc/lv_timer.h>
#include "route.h"
#include "ui_style.h"
#include "global_def.h"

lv_obj_t* cute_make_finish_view = 0;

static lv_obj_t* flower_1 = 0;
static lv_obj_t* flower_2 = 0;
static lv_obj_t* flower_3 = 0;
static lv_obj_t* flower_4 = 0;
static lv_obj_t* flower_5 = 0;
static lv_timer_t* timer = 0;
static lv_obj_t* count_text = 0;

static void animate_timer_cb(lv_timer_t* timer) {
  static int32_t frame = 0;
  static int32_t count = 5;
  frame += 1;

  if (frame >= 4) {
    frame = 0;
  }

  if (count > 0) {
    count--;
  } else {
    lv_timer_delete(timer);
    navigate_to_view("cute_main_menu_view", 0);
  }

  int32_t rotation = frame * 450;

  lv_label_set_text_fmt(count_text, "%ds自动返回主界面", count);
  lv_image_set_rotation(flower_1, rotation);
  lv_image_set_rotation(flower_2, rotation);
  lv_image_set_rotation(flower_3, rotation);
  lv_image_set_rotation(flower_4, rotation);
  lv_image_set_rotation(flower_5, rotation);
}

lv_obj_t* cute_make_finish_view_init(void* args) {
  cute_make_finish_view = lv_obj_create(NULL);
  lv_obj_t* this = cute_make_finish_view;

  lv_obj_set_size(cute_make_finish_view, SCREEN_WIDTH, SCREEN_HEIGHT);
  lv_obj_set_style_bg_color(cute_make_finish_view, lv_color_hex(0xF3EADB), 0);

  lv_obj_t* img = lv_img_create(this);
  lv_img_set_src(img, LVGL_IMAGE_PATH("cute_make_finish/coffee_finish.png"));
  lv_obj_center(img);

  flower_1 = lv_img_create(this);
  lv_img_set_src(flower_1, LVGL_IMAGE_PATH("cute_screen_saver/flower1.png"));
  lv_obj_set_pos(flower_1, 82, 47);

  flower_2 = lv_img_create(this);
  lv_img_set_src(flower_2, LVGL_IMAGE_PATH("cute_screen_saver/flower2.png"));
  lv_obj_set_pos(flower_2, 785, 67);

  flower_3 = lv_img_create(this);
  lv_img_set_src(flower_3, LVGL_IMAGE_PATH("cute_screen_saver/flower3.png"));
  lv_obj_set_pos(flower_3, 160, 374);

  flower_4 = lv_img_create(this);
  lv_img_set_src(flower_4, LVGL_IMAGE_PATH("cute_screen_saver/flower4.png"));
  lv_obj_set_pos(flower_4, 707, 472);

  flower_5 = lv_img_create(this);
  lv_img_set_src(flower_5, LVGL_IMAGE_PATH("cute_screen_saver/flower5.png"));
  lv_obj_set_pos(flower_5, 928, 514);

  lv_obj_t* flower_sm_1 = lv_image_create(this);
  lv_image_set_src(flower_sm_1,
                   LVGL_IMAGE_PATH("cute_make_finish/flower_sm_1.png"));
  lv_obj_set_pos(flower_sm_1, 73, 517);

  lv_obj_t* flower_sm_1_2 = lv_image_create(this);
  lv_image_set_src(flower_sm_1_2,
                   LVGL_IMAGE_PATH("cute_make_finish/flower_sm_1.png"));
  lv_obj_set_pos(flower_sm_1_2, 729, 223);

  lv_obj_t* flower_sm_2 = lv_image_create(this);
  lv_image_set_src(flower_sm_2,
                   LVGL_IMAGE_PATH("cute_make_finish/flower_sm_2.png"));
  lv_obj_set_pos(flower_sm_2, 949, 166);

  lv_obj_t* flower_sm_3 = lv_image_create(this);
  lv_image_set_src(flower_sm_3,
                   LVGL_IMAGE_PATH("cute_make_finish/flower_sm_3.png"));
  lv_obj_set_pos(flower_sm_3, 338, 67);

  UI_TEXT_XL(this, "制作完成", 455, 460, COLOR(733490));
  count_text = ui_text(this, "5s自动返回主界面", lanapixel_md,
                       LV_ALIGN_BOTTOM_MID, 0, -68, COLOR(7A7A7A));

  timer = lv_timer_create(animate_timer_cb, 1000, NULL);

  return cute_make_finish_view;
}