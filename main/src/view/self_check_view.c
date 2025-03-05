#include <src/font/lv_font.h>
#include <src/misc/lv_anim.h>
#include <src/misc/lv_area.h>
#include <stdint.h>
#include "global_def.h"
#include "lvgl.h"
#include "stdio.h"

#define SCALE_ANIM_MAX_WIDTH 195
#define SCALE_ANIM_TIME 1500
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_26)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_30)

lv_obj_t* self_check_view = 0;
lv_obj_t* img_starting = 0;
lv_obj_t* arc_11 = 0;  // 新增圆环对象指针
lv_obj_t* arc_12 = 0;
lv_obj_t* arc_13 = 0;
lv_obj_t* arc_21 = 0;
lv_obj_t* arc_22 = 0;
lv_obj_t* arc_23 = 0;
lv_obj_t* arc_31 = 0;
lv_obj_t* arc_32 = 0;
lv_obj_t* arc_33 = 0;
lv_obj_t* arc_41 = 0;
lv_obj_t* arc_42 = 0;
lv_obj_t* arc_43 = 0;
lv_obj_t* img_three_dot_1 = 0;
lv_obj_t* img_three_dot_2 = 0;
lv_obj_t* img_three_dot_3 = 0;
lv_obj_t* img_complete_hook_1 = 0;
lv_obj_t* img_complete_hook_2 = 0;
lv_obj_t* img_complete_hook_3 = 0;
lv_obj_t* img_complete_hook_4 = 0;
lv_obj_t* label_text_1 = 0;  // 新增标签对象指针
lv_obj_t* label_text_2 = 0;  // 新增标签对象指针
lv_obj_t* label_text_3 = 0;  // 新增标签对象指针
lv_obj_t* label_text_4 = 0;  // 新增标签对象指针

lv_anim_t scale_anim;
// 存储需要进行动画操作的目标对象指针
lv_obj_t* anim_targets[4] = {0};

const char* three_dot_low =
    LVGL_IMAGE_PATH("boot_view_images/img_three_dot_low.png");
const char* three_dot_active =
    LVGL_IMAGE_PATH("boot_view_images/img_three_dot_active.png");
const char* three_dot_finish =
    LVGL_IMAGE_PATH("boot_view_images/img_three_dot_finish.png");

typedef void (*command_exec_cb)();
static void self_check_view_set_stage(uint8_t stage_num);
command_exec_cb my_command[16] = {0};
int command_count = 0;

void add_command_cb(command_exec_cb cb) {
  if (command_count < 16) {
    my_command[command_count] = cb;
    command_count++;
  }
}

// 当动画执行时每次设置对象的属性方法回调
void anim_set_value_cb(void* target, int32_t value) {
  lv_obj_t* obj = (lv_obj_t*)target;
  lv_obj_set_size(obj, value, value);
  lv_obj_set_style_radius(obj, value / 2, 0);
  lv_obj_set_style_border_opa(
      obj, (SCALE_ANIM_MAX_WIDTH - value) * 255 / (SCALE_ANIM_MAX_WIDTH - 162),
      0);
}

void anim_ended_cb(lv_anim_t* a) {
  static bool is_expanding = false;
  if (is_expanding) {
    lv_anim_set_values(&scale_anim, SCALE_ANIM_MAX_WIDTH, 162);
    is_expanding = false;
    for (int i = 0; i < 16; i++) {
      if (my_command[i] != 0) {
        my_command[i]();
      }
    }
  } else {
    lv_anim_set_values(&scale_anim, 162, SCALE_ANIM_MAX_WIDTH);
    is_expanding = true;
  }
  lv_anim_start(&scale_anim);
}

void change_scale_anim_index(int index) {
  lv_anim_set_var(&scale_anim, anim_targets[index]);
  lv_anim_set_values(&scale_anim, SCALE_ANIM_MAX_WIDTH, 162);
  lv_anim_start(&scale_anim);
}
void change_target_timer_cb(lv_timer_t* timer) {
  static int index = 0;
  self_check_view_set_stage(index);
  index++;
  if (index >= 6) {
    index = 0;
  }
}
void build_anim_arc(lv_obj_t* arc, int32_t x, int32_t y) {
  lv_obj_set_size(arc, 162, 162);            // 设置圆环的大小
  lv_obj_set_style_radius(arc, 81, 0);       // 设置圆环的半径为81像素
  lv_obj_set_style_border_width(arc, 2, 0);  // 设置圆环的宽度为2像素
  lv_obj_set_style_bg_color(arc, lv_color_hex(0x000000),
                            0);  // 设置圆环的背景颜色为黑色
  lv_obj_set_style_bg_opa(arc, 0,
                          0);  // 设置圆环的背景颜色的透明度为0，即完全透明
  lv_obj_set_style_border_color(arc, lv_color_hex(0xE9BD86), 0);
  lv_obj_set_style_border_opa(arc, LV_OPA_COVER, 0);
  lv_obj_align(arc, LV_ALIGN_CENTER, x, y);  // 将圆环居中对齐
}

lv_obj_t* self_check_view_init(void) {
  self_check_view = lv_obj_create(NULL);
  lv_obj_set_size(self_check_view, 1280, 480);
  lv_obj_set_style_bg_color(self_check_view, lv_color_hex(0x000000), 0);

  img_starting = lv_label_create(self_check_view);
  lv_label_set_text(img_starting, "咖啡机启动中…");
  lv_obj_set_style_text_color(img_starting, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_font(img_starting, &HarmonyOS_Sans_SC_Regular_30, 0);
  lv_obj_align(img_starting, LV_ALIGN_CENTER, 15, -157);

  arc_11 = lv_obj_create(self_check_view);
  lv_obj_set_size(arc_11, 158, 158);       // 设置圆环的大小
  lv_obj_set_style_radius(arc_11, 79, 0);  // 设置圆环的半径为50像素
  lv_obj_set_style_border_width(arc_11, 6, 0);  // 设置圆环的宽度为10像素
  lv_obj_set_style_bg_color(arc_11, lv_color_hex(0x000000),
                            0);  // 设置圆环的背景颜色为黑色
  lv_obj_set_style_bg_opa(arc_11, 0,
                          0);  // 设置圆环的背景颜色的透明度为0，即完全透明
  lv_obj_set_style_border_color(arc_11, lv_color_hex(0xE9BD85), 0);
  lv_obj_set_style_border_opa(arc_11, LV_OPA_30, 0);
  lv_obj_align(arc_11, LV_ALIGN_TOP_LEFT, 189, 161);  // 将圆环居中对齐
  // 动画外圈
  arc_12 = lv_obj_create(self_check_view);
  build_anim_arc(arc_12, -372, 0);
  lv_obj_add_flag(arc_12, LV_OBJ_FLAG_HIDDEN);

  arc_22 = lv_obj_create(self_check_view);
  build_anim_arc(arc_22, -124, 0);
  lv_obj_add_flag(arc_22, LV_OBJ_FLAG_HIDDEN);

  arc_32 = lv_obj_create(self_check_view);
  build_anim_arc(arc_32, 124, 0);
  lv_obj_add_flag(arc_32, LV_OBJ_FLAG_HIDDEN);

  arc_42 = lv_obj_create(self_check_view);
  build_anim_arc(arc_42, 372, 0);
  lv_obj_add_flag(arc_42, LV_OBJ_FLAG_HIDDEN);
  // 最终显示外圈
  arc_13 = lv_obj_create(self_check_view);
  build_anim_arc(arc_13, -372, 0);
  lv_obj_add_flag(arc_13, LV_OBJ_FLAG_HIDDEN);

  arc_23 = lv_obj_create(self_check_view);
  build_anim_arc(arc_23, -124, 0);
  lv_obj_add_flag(arc_23, LV_OBJ_FLAG_HIDDEN);

  arc_33 = lv_obj_create(self_check_view);
  build_anim_arc(arc_33, 124, 0);
  lv_obj_add_flag(arc_33, LV_OBJ_FLAG_HIDDEN);

  arc_43 = lv_obj_create(self_check_view);
  build_anim_arc(arc_43, 372, 0);
  lv_obj_add_flag(arc_43, LV_OBJ_FLAG_HIDDEN);

  lv_anim_init(&scale_anim);
  lv_anim_set_var(&scale_anim, arc_12);
  lv_anim_set_values(&scale_anim, SCALE_ANIM_MAX_WIDTH, 162);
  lv_anim_set_time(&scale_anim, SCALE_ANIM_TIME);
  lv_anim_set_repeat_count(&scale_anim, 0);
  lv_anim_set_path_cb(&scale_anim, lv_anim_path_linear);
  lv_anim_set_exec_cb(&scale_anim, (lv_anim_exec_xcb_t)anim_set_value_cb);
  lv_anim_set_completed_cb(&scale_anim, anim_ended_cb);

  label_text_1 = lv_label_create(self_check_view);
  lv_label_set_text(label_text_1, "系统补水");
  lv_obj_set_style_text_color(label_text_1, lv_color_hex(0xE9BD85), 0);
  lv_obj_set_style_text_font(label_text_1, &HarmonyOS_Sans_SC_Regular_26, 0);
  lv_obj_align(label_text_1, LV_ALIGN_CENTER, -372, 0);

  img_complete_hook_1 = lv_image_create(self_check_view);
  lv_image_set_src(img_complete_hook_1,
                   LVGL_IMAGE_PATH("boot_view_images/img_complete_hook.png"));
  lv_obj_align(img_complete_hook_1, LV_ALIGN_CENTER, -372, -40);
  lv_obj_add_flag(img_complete_hook_1, LV_OBJ_FLAG_HIDDEN);

  img_three_dot_1 = lv_image_create(self_check_view);
  lv_image_set_src(img_three_dot_1, three_dot_low);
  lv_obj_align(img_three_dot_1, LV_ALIGN_TOP_LEFT, 376, 240);

  arc_21 = lv_obj_create(self_check_view);
  lv_obj_set_size(arc_21, 158, 158);       // 设置圆环的大小
  lv_obj_set_style_radius(arc_21, 79, 0);  // 设置圆环的半径为50像素
  lv_obj_set_style_border_width(arc_21, 6, 0);  // 设置圆环的宽度为10像素
  lv_obj_set_style_bg_color(arc_21, lv_color_hex(0x000000),
                            0);  // 设置圆环的背景颜色为黑色
  lv_obj_set_style_bg_opa(arc_21, 0,
                          0);  // 设置圆环的背景颜色的透明度为0，即完全透明
  lv_obj_set_style_border_color(arc_21, lv_color_hex(0xE9BD85), 0);
  lv_obj_set_style_border_opa(arc_21, LV_OPA_30, 0);
  lv_obj_align(arc_21, LV_ALIGN_TOP_LEFT, 437, 161);  // 将圆环居中对齐

  label_text_2 = lv_label_create(self_check_view);
  lv_label_set_text(label_text_2, "系统自检");
  lv_obj_set_style_text_color(label_text_2, lv_color_hex(0xE9BD85), 0);
  lv_obj_set_style_text_font(label_text_2, &HarmonyOS_Sans_SC_Regular_26, 0);
  lv_obj_align(label_text_2, LV_ALIGN_CENTER, -124, 0);

  img_complete_hook_2 = lv_image_create(self_check_view);
  lv_image_set_src(img_complete_hook_2,
                   LVGL_IMAGE_PATH("boot_view_images/img_complete_hook.png"));
  lv_obj_align(img_complete_hook_2, LV_ALIGN_CENTER, -124, -40);
  lv_obj_add_flag(img_complete_hook_2, LV_OBJ_FLAG_HIDDEN);

  img_three_dot_2 = lv_image_create(self_check_view);
  lv_image_set_src(img_three_dot_2, three_dot_low);
  lv_obj_align(img_three_dot_2, LV_ALIGN_TOP_LEFT, 624, 240);

  arc_31 = lv_obj_create(self_check_view);
  lv_obj_set_size(arc_31, 158, 158);       // 设置圆环的大小
  lv_obj_set_style_radius(arc_31, 79, 0);  // 设置圆环的半径为50像素
  lv_obj_set_style_border_width(arc_31, 6, 0);  // 设置圆环的宽度为10像素
  lv_obj_set_style_bg_color(arc_31, lv_color_hex(0x000000),
                            0);  // 设置圆环的背景颜色为黑色
  lv_obj_set_style_bg_opa(arc_31, 0,
                          0);  // 设置圆环的背景颜色的透明度为0，即完全透明
  lv_obj_set_style_border_color(arc_31, lv_color_hex(0xE9BD85), 0);
  lv_obj_set_style_border_opa(arc_31, LV_OPA_30, 0);
  lv_obj_align(arc_31, LV_ALIGN_TOP_RIGHT, -437, 161);  // 将圆环居中对齐

  label_text_3 = lv_label_create(self_check_view);
  lv_label_set_text(label_text_3, "系统加热");
  lv_obj_set_style_text_color(label_text_3, lv_color_hex(0xE9BD85), 0);
  lv_obj_set_style_text_font(label_text_3, &HarmonyOS_Sans_SC_Regular_26, 0);
  lv_obj_align(label_text_3, LV_ALIGN_CENTER, 124, 0);

  img_complete_hook_3 = lv_image_create(self_check_view);
  lv_image_set_src(img_complete_hook_3,
                   LVGL_IMAGE_PATH("boot_view_images/img_complete_hook.png"));
  lv_obj_align(img_complete_hook_3, LV_ALIGN_CENTER, 124, -40);
  lv_obj_add_flag(img_complete_hook_3, LV_OBJ_FLAG_HIDDEN);

  img_three_dot_3 = lv_image_create(self_check_view);
  lv_image_set_src(img_three_dot_3, three_dot_low);
  lv_obj_align(img_three_dot_3, LV_ALIGN_TOP_RIGHT, -376, 240);

  arc_41 = lv_obj_create(self_check_view);
  lv_obj_set_size(arc_41, 158, 158);       // 设置圆环的大小
  lv_obj_set_style_radius(arc_41, 79, 0);  // 设置圆环的半径为50像素
  lv_obj_set_style_border_width(arc_41, 6, 0);  // 设置圆环的宽度为10像素
  lv_obj_set_style_bg_color(arc_41, lv_color_hex(0x000000),
                            0);  // 设置圆环的背景颜色为黑色
  lv_obj_set_style_bg_opa(arc_41, 0,
                          0);  // 设置圆环的背景颜色的透明度为0，即完全透明
  lv_obj_set_style_border_color(arc_41, lv_color_hex(0xE9BD85), 0);
  lv_obj_set_style_border_opa(arc_41, LV_OPA_30, 0);
  lv_obj_align(arc_41, LV_ALIGN_TOP_RIGHT, -189, 161);  // 将圆环居中对齐

  label_text_4 = lv_label_create(self_check_view);
  lv_label_set_text(label_text_4, "系统冲洗");
  lv_obj_set_style_text_color(label_text_4, lv_color_hex(0xE9BD85), 0);
  lv_obj_set_style_text_font(label_text_4, &HarmonyOS_Sans_SC_Regular_26, 0);
  lv_obj_align(label_text_4, LV_ALIGN_CENTER, 372, 0);

  img_complete_hook_4 = lv_image_create(self_check_view);
  lv_image_set_src(img_complete_hook_4,
                   LVGL_IMAGE_PATH("boot_view_images/img_complete_hook.png"));
  lv_obj_align(img_complete_hook_4, LV_ALIGN_CENTER, 372, -40);
  lv_obj_add_flag(img_complete_hook_4, LV_OBJ_FLAG_HIDDEN);

  anim_targets[0] = arc_12;
  anim_targets[1] = arc_22;
  anim_targets[2] = arc_32;
  anim_targets[3] = arc_42;

  lv_timer_t* timer = lv_timer_create(change_target_timer_cb, 6000, 0);

  return self_check_view;
}

// 不同状态时更新view
void self_check_view_set_stage(uint8_t stage_num) {
  switch (stage_num) {
    case 0:
      lv_image_set_src(img_three_dot_1, three_dot_active);
      lv_image_set_src(img_three_dot_2, three_dot_low);
      lv_image_set_src(img_three_dot_3, three_dot_low);
      lv_obj_remove_flag(arc_12, LV_OBJ_FLAG_HIDDEN);
      change_scale_anim_index(0);
      lv_anim_start(&scale_anim);
      break;
    case 1:
      lv_image_set_src(img_three_dot_1, three_dot_finish);
      lv_image_set_src(img_three_dot_2, three_dot_active);
      lv_image_set_src(img_three_dot_3, three_dot_low);
      lv_obj_remove_flag(arc_22, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(arc_13, LV_OBJ_FLAG_HIDDEN);
      change_scale_anim_index(1);
      anim_set_value_cb(arc_12, 162);
      lv_obj_remove_flag(img_complete_hook_1, LV_OBJ_FLAG_HIDDEN);
      break;
    case 2:
      lv_image_set_src(img_three_dot_1, three_dot_finish);
      lv_image_set_src(img_three_dot_2, three_dot_finish);
      lv_image_set_src(img_three_dot_3, three_dot_active);
      lv_obj_remove_flag(arc_32, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(arc_23, LV_OBJ_FLAG_HIDDEN);
      change_scale_anim_index(2);
      anim_set_value_cb(arc_22, 162);
      lv_obj_remove_flag(img_complete_hook_2, LV_OBJ_FLAG_HIDDEN);
      break;
    case 3:
      lv_image_set_src(img_three_dot_1, three_dot_finish);
      lv_image_set_src(img_three_dot_2, three_dot_finish);
      lv_image_set_src(img_three_dot_3, three_dot_finish);
      lv_obj_remove_flag(arc_42, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(arc_33, LV_OBJ_FLAG_HIDDEN);
      change_scale_anim_index(3);
      anim_set_value_cb(arc_32, 162);
      lv_obj_remove_flag(img_complete_hook_3, LV_OBJ_FLAG_HIDDEN);
      break;
    case 4:
      lv_anim_del(&scale_anim, NULL);  // 停止动画
      lv_anim_init(&scale_anim);  // 重新初始化动画，确保状态重置
      lv_obj_remove_flag(arc_43, LV_OBJ_FLAG_HIDDEN);
      anim_set_value_cb(arc_42, 162);
      lv_obj_remove_flag(img_complete_hook_4, LV_OBJ_FLAG_HIDDEN);
      break;
    default:
      break;
  }
}

static void timer_cb_remove_flag_1(lv_timer_t* timer) {
  lv_obj_remove_flag(img_complete_hook_1, LV_OBJ_FLAG_HIDDEN);
  lv_timer_del(timer);  // 执行完后删除定时器
}

void updat_check_view() {
  // 读取model
  // 按model值更新view
}