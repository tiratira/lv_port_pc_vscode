#include <stdio.h>
#include "global_def.h"
#include "drink_type.h"
#include "ui_style.h"
#include "route.h"

lv_obj_t* cute_make_coffee_view = 0;

extern lv_font_t* lanapixel_sm;
extern lv_font_t* lanapixel_md;
extern lv_font_t* lanapixel_xl;
extern lv_font_t* lanapixel_xxl;

static drink_item_data_t* drink_item = 0;

static lv_obj_t* bg_flower_1 = 0;
static lv_obj_t* bg_flower_2 = 0;
static lv_obj_t* bg_flower_3 = 0;

static lv_obj_t* bean_imgs[4] = {0};
static lv_obj_t* sweetness_objs[5] = {0};
static lv_timer_t* timer;

static const char* coffee_making_anim_path[] = {
    LVGL_IMAGE_PATH("cute_make_coffee/machine_anim_1.png"),
    LVGL_IMAGE_PATH("cute_make_coffee/machine_anim_2.png"),
    LVGL_IMAGE_PATH("cute_make_coffee/machine_anim_3.png"),
    LVGL_IMAGE_PATH("cute_make_coffee/machine_anim_4.png"),
    LVGL_IMAGE_PATH("cute_make_coffee/machine_anim_5.png"),
    LVGL_IMAGE_PATH("cute_make_coffee/machine_anim_6.png"),
    LVGL_IMAGE_PATH("cute_make_coffee/machine_anim_7.png"),
};

static const char* cat_walk_anim_path[] = {
    LVGL_IMAGE_PATH("cute_make_coffee/cat_walk_0.png"),
    LVGL_IMAGE_PATH("cute_make_coffee/cat_walk_1.png"),
    LVGL_IMAGE_PATH("cute_make_coffee/cat_walk_2.png"),
    LVGL_IMAGE_PATH("cute_make_coffee/cat_walk_3.png"),
};

static lv_obj_t* coffee_img;
static lv_obj_t* bean_vol_value = 0;
static lv_obj_t* water_vol_value = 0;
static lv_obj_t* cat;
static lv_obj_t* progress_bar;
static lv_obj_t* progress_text;

// data model
typedef struct {
  int bean_density;
  int coffee_volume;
  int water_volume;
  int sweetness;
  int progress;
} coffee_making_data_t;

coffee_making_data_t data_model = {
    .bean_density = 2,
    .coffee_volume = 20,
    .water_volume = 200,
    .sweetness = 3,
    .progress = 0,
};

static void page_timer_cb(lv_timer_t* timer) {
  static int cat_frame = 0;
  cat_frame++;
  if (cat_frame >= 4) {
    cat_frame = 0;
  }
  lv_img_set_src(cat, cat_walk_anim_path[cat_frame]);
  lv_image_set_rotation(bg_flower_1, cat_frame * 450);
  lv_image_set_rotation(bg_flower_2, cat_frame * 450);
  lv_image_set_rotation(bg_flower_3, cat_frame * 450);

  if (data_model.progress < 100) {
    data_model.progress += 5;
    lv_obj_set_pos(cat, (217 * data_model.progress / 100) + 516, 504);
    lv_bar_set_value(progress_bar, data_model.progress, LV_ANIM_OFF);
    lv_label_set_text_fmt(progress_text, "%d%%", data_model.progress);
    lv_image_set_src(coffee_img,
                     coffee_making_anim_path[data_model.progress / 16]);
  } else {
    static char delay = 0;
    delay++;
    if (delay > 2) {
      lv_timer_delete(timer);
      navigate_to_view("cute_make_finish_view", drink_item);
    }
  }
}

static void on_back_clicked(lv_event_t* e) {
  lv_timer_del(timer);
  navigate_to_view("cute_coffee_config_view", drink_item);
}

static void on_dec_clicked(lv_event_t* e) {
  int* value = (int*)e->user_data;
  if (value == &data_model.coffee_volume) {
    if (*value > 10) {
      *value -= 10;
    }
    lv_label_set_text_fmt(bean_vol_value, "%d", *value);
  } else if (value == &data_model.water_volume) {
    if (*value > 0) {
      *value -= 10;
    }
    lv_label_set_text_fmt(water_vol_value, "%d", *value);
  }
}
static void on_inc_clicked(lv_event_t* e) {
  int* value = (int*)e->user_data;
  if (value == &data_model.coffee_volume) {
    if (*value < 240) {
      *value += 10;
    }
    lv_label_set_text_fmt(bean_vol_value, "%d", *value);
  } else if (value == &data_model.water_volume) {
    if (*value < 300) {
      *value += 10;
    }
    lv_label_set_text_fmt(water_vol_value, "%d", *value);
  }
}

static void on_sweetness_changed(lv_event_t* e) {
  int idx = (int)e->user_data;
  data_model.sweetness = idx + 1;
  for (int i = 0; i < 5; i++) {
    lv_obj_set_style_bg_color(sweetness_objs[i],
                              i < data_model.sweetness ? UI_PRIMARY : UI_BG, 0);
  }
}

static void on_bean_density_changed(lv_event_t* e) {
  int idx = (int)e->user_data;
  data_model.bean_density = idx + 1;
  for (int i = 0; i < 4; i++) {
    lv_img_set_src(bean_imgs[i],
                   i < data_model.bean_density
                       ? LVGL_IMAGE_PATH("cute_make_coffee/bean_1.png")
                       : LVGL_IMAGE_PATH("cute_make_coffee/bean_0.png"));
  }
}

static void build_control_widget(const char* title, const char* title2,
                                 lv_obj_t** value_obj_ptr, int x, int y,
                                 int value) {
  lv_obj_t* container = lv_obj_create(cute_make_coffee_view);
  lv_obj_remove_style_all(container);
  lv_obj_set_size(container, 137, 233);
  lv_obj_set_pos(container, x, y);
  lv_obj_set_style_radius(container, 40, 0);
  lv_obj_set_style_bg_color(container, lv_color_hex(0xB5B5D1), 0);
  lv_obj_set_style_bg_opa(container, LV_OPA_100, 0);
  lv_obj_set_style_border_width(container, 0, 0);

  UI_TEXT_MD(container, title, 38, 30, UI_BLACK);
  UI_TEXT_MD(container, title2, 21, 60, COLOR(414141));
  UI_TEXT_SM(container, "ml", 116, 138, COLOR(414141));

  char value_str[4] = {0};
  sprintf(value_str, "%d", value);

  *value_obj_ptr = lv_label_create(container);
  lv_label_set_text(*value_obj_ptr, value_str);
  lv_obj_align(*value_obj_ptr, LV_ALIGN_BOTTOM_MID, -5, -55);
  lv_obj_set_style_text_font(*value_obj_ptr, lanapixel_xxl, 0);
  lv_obj_set_style_text_color(*value_obj_ptr, UI_BLACK, 0);

  lv_obj_t* control_container = lv_obj_create(container);
  lv_obj_remove_style_all(control_container);
  lv_obj_set_size(control_container, 96, 39);
  lv_obj_set_pos(control_container, 21, 177);
  lv_obj_set_style_radius(control_container, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_bg_color(control_container, lv_color_hex(0xE5E5E5), 0);
  lv_obj_set_style_bg_opa(control_container, LV_OPA_100, 0);

  lv_obj_t* add_circle = lv_obj_create(container);
  lv_obj_remove_style_all(add_circle);
  lv_obj_set_size(add_circle, 39, 39);
  lv_obj_set_pos(add_circle, 79, 177);
  lv_obj_set_style_radius(add_circle, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_bg_color(add_circle, lv_color_hex(0xAB86BA), 0);
  lv_obj_set_style_bg_opa(add_circle, LV_OPA_100, 0);

  lv_obj_t* icon = lv_image_create(container);
  lv_image_set_src(icon, LVGL_IMAGE_PATH("cute_make_coffee/add_minus.png"));
  lv_obj_set_pos(icon, 33, 188);
}

lv_obj_t* cute_make_coffee_view_init(void* args) {
  drink_item = (drink_item_data_t*)args;
  if (drink_item == 0) {
    return 0;
  }
  data_model.progress = 0;
  cute_make_coffee_view = lv_obj_create(NULL);
  lv_obj_t* this = cute_make_coffee_view;

  lv_obj_set_size(cute_make_coffee_view, SCREEN_WIDTH, SCREEN_HEIGHT);
  lv_obj_set_style_bg_color(cute_make_coffee_view, lv_color_hex(0xF3EADB), 0);

  UI_TEXT_MD(this, "早上好！来杯咖啡开启活力满满的一天！", 52, 45, UI_BLACK);
  UI_TEXT_SM(this, "请选择您的偏好设置", 52, 80, COLOR(9F73B3));

  lv_obj_t* back_btn = lv_btn_create(cute_make_coffee_view);
  lv_obj_remove_style_all(back_btn);
  lv_obj_add_style(back_btn, &btn_style_normal, 0);
  lv_obj_set_size(back_btn, 51, 51);
  lv_obj_set_pos(back_btn, 42, 119);

  lv_obj_t* back_icon_img = lv_image_create(back_btn);
  lv_image_set_src(back_icon_img, LVGL_IMAGE_PATH("common/icon_back.png"));
  lv_obj_align(back_icon_img, LV_ALIGN_CENTER, 0, 0);

  lv_obj_add_event_cb(back_btn, on_back_clicked, LV_EVENT_CLICKED, NULL);

  // 大文字
  UI_TEXT_XL(this, drink_item->title_cn, 66, 184, UI_BLACK);
  UI_TEXT_MD(this, drink_item->title_en, 66, 225, COLOR(BBBBBB));

  // 小文字
  UI_TEXT_MD(this, "制作中……", 66, 264, UI_BLACK);

  // 咖啡机背景花朵
  bg_flower_1 = lv_img_create(cute_make_coffee_view);
  lv_img_set_src(bg_flower_1, LVGL_IMAGE_PATH("cute_make_coffee/flower_1.png"));
  lv_obj_set_pos(bg_flower_1, 124, 365);

  bg_flower_2 = lv_img_create(cute_make_coffee_view);
  lv_img_set_src(bg_flower_2, LVGL_IMAGE_PATH("cute_make_coffee/flower_2.png"));
  lv_obj_set_pos(bg_flower_2, 298, 251);

  bg_flower_3 = lv_img_create(cute_make_coffee_view);
  lv_img_set_src(bg_flower_3, LVGL_IMAGE_PATH("cute_make_coffee/flower_3.png"));
  lv_obj_set_pos(bg_flower_3, 371, 430);

  // 咖啡机动画
  coffee_img = lv_img_create(cute_make_coffee_view);
  lv_img_set_src(coffee_img, coffee_making_anim_path[0]);
  lv_obj_set_pos(coffee_img, 148, 297);

  // 浓度框
  lv_obj_t* strength_bg = lv_obj_create(cute_make_coffee_view);
  lv_obj_set_size(strength_bg, 119, 284);
  lv_obj_set_pos(strength_bg, 462, 184);
  lv_obj_set_style_bg_opa(strength_bg, LV_OPA_TRANSP, 0);
  lv_obj_set_style_radius(strength_bg, 40, 0);
  lv_obj_set_style_border_color(strength_bg, lv_color_hex(0xBCBBD2), 0);
  lv_obj_set_style_border_width(strength_bg, 6, 0);

  // 浓度文字
  UI_TEXT_MD(this, "咖啡浓度", 482, 214, UI_BLACK);
  UI_TEXT_SM(this, "(1-4shot)", 490, 249, COLOR(414141));

  const int bean_y[] = {272, 313, 355, 396};

  // bean
  for (int i = 0; i < 4; i++) {
    bean_imgs[i] = lv_img_create(cute_make_coffee_view);
    lv_img_set_src(bean_imgs[i],
                   i < data_model.bean_density
                       ? LVGL_IMAGE_PATH("cute_make_coffee/bean_1.png")
                       : LVGL_IMAGE_PATH("cute_make_coffee/bean_0.png"));
    lv_obj_set_pos(bean_imgs[i], 502, bean_y[i]);
    lv_obj_add_flag(bean_imgs[i], LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(bean_imgs[i], on_bean_density_changed, LV_EVENT_CLICKED,
                        (void*)i);
  }

  build_control_widget("咖啡量", "(10-240mL)", &bean_vol_value, 627, 184,
                       data_model.coffee_volume);
  build_control_widget("热水量", "(0-300mL)", &water_vol_value, 809, 184,
                       data_model.water_volume);

  UI_TEXT_MD(this, "甜度", 635, 439, UI_BLACK);

  const int sweet_x[] = {696, 745, 794, 843, 892};

  for (int i = 0; i < 5; i++) {
    sweetness_objs[i] = lv_button_create(this);
    lv_obj_remove_style_all(sweetness_objs[i]);
    lv_obj_set_size(sweetness_objs[i], 30, 30);
    lv_obj_set_pos(sweetness_objs[i], sweet_x[i], 439);
    lv_obj_set_style_bg_color(sweetness_objs[i],
                              i < data_model.sweetness ? UI_PRIMARY : UI_BG, 0);
    lv_obj_set_style_bg_opa(sweetness_objs[i], LV_OPA_100, 0);
    lv_obj_set_style_radius(sweetness_objs[i], LV_RADIUS_CIRCLE, 0);
    lv_obj_add_event_cb(sweetness_objs[i], on_sweetness_changed,
                        LV_EVENT_CLICKED, (void*)i);
  }

  UI_TEXT_MD(this, "进度", 462, 521, UI_BLACK);

  progress_bar = lv_bar_create(cute_make_coffee_view);
  lv_obj_set_size(progress_bar, 271, 30);
  lv_obj_set_pos(progress_bar, 523, 518);
  lv_bar_set_value(progress_bar, 20, LV_ANIM_ON);
  lv_obj_set_style_bg_color(progress_bar, lv_color_hex(0xD9D9D9), 0);
  lv_obj_set_style_bg_opa(progress_bar, LV_OPA_100, 0);
  lv_obj_set_style_bg_color(progress_bar, lv_color_hex(0xA27AB6),
                            LV_PART_INDICATOR);

  progress_text = lv_label_create(this);
  lv_label_set_text_fmt(progress_text, "%d%%", data_model.progress);
  lv_obj_set_style_text_font(progress_text, lanapixel_md, 0);
  lv_obj_set_style_text_color(progress_text, lv_color_black(), 0);
  lv_obj_set_pos(progress_text, 539, 522);

  cat = lv_image_create(this);
  lv_image_set_src(cat, cat_walk_anim_path[0]);
  lv_obj_set_pos(cat, 516, 504);

  lv_obj_t* close_btn = lv_btn_create(this);
  lv_obj_remove_style_all(close_btn);
  lv_obj_add_style(close_btn, &btn_style_primary, 0);
  lv_obj_set_size(close_btn, 113, 59);
  lv_obj_set_pos(close_btn, 838, 502);
  lv_obj_t* btn_img = lv_image_create(close_btn);
  lv_image_set_src(btn_img, LVGL_IMAGE_PATH("common/icon_close.png"));
  lv_obj_center(btn_img);
  lv_obj_add_event_cb(close_btn, on_back_clicked, LV_EVENT_CLICKED, NULL);

  lv_obj_t* bean_vol_dec_btn = lv_btn_create(this);
  lv_obj_remove_style_all(bean_vol_dec_btn);
  lv_obj_set_pos(bean_vol_dec_btn, 648, 361);
  lv_obj_set_size(bean_vol_dec_btn, 39, 39);

  lv_obj_add_event_cb(bean_vol_dec_btn, on_dec_clicked, LV_EVENT_CLICKED,
                      &data_model.coffee_volume);

  lv_obj_t* bean_vol_inc_btn = lv_btn_create(this);
  lv_obj_remove_style_all(bean_vol_inc_btn);
  lv_obj_set_pos(bean_vol_inc_btn, 706, 361);
  lv_obj_set_size(bean_vol_inc_btn, 39, 39);

  lv_obj_add_event_cb(bean_vol_inc_btn, on_inc_clicked, LV_EVENT_CLICKED,
                      &data_model.coffee_volume);

  lv_obj_t* water_vol_dec_btn = lv_btn_create(this);
  lv_obj_remove_style_all(water_vol_dec_btn);
  lv_obj_set_pos(water_vol_dec_btn, 830, 361);
  lv_obj_set_size(water_vol_dec_btn, 39, 39);

  lv_obj_add_event_cb(water_vol_dec_btn, on_dec_clicked, LV_EVENT_CLICKED,
                      &data_model.water_volume);

  lv_obj_t* water_vol_inc_btn = lv_btn_create(this);
  lv_obj_remove_style_all(water_vol_inc_btn);
  lv_obj_set_pos(water_vol_inc_btn, 888, 361);
  lv_obj_set_size(water_vol_inc_btn, 39, 39);

  lv_obj_add_event_cb(water_vol_inc_btn, on_inc_clicked, LV_EVENT_CLICKED,
                      &data_model.water_volume);

  timer = lv_timer_create(page_timer_cb, 1000, 0);

  return this;
}
