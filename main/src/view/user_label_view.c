#include <src/core/lv_obj_pos.h>
#include <src/misc/lv_area.h>
#include <src/core/lv_obj_style.h>
#include <src/misc/lv_style.h>
#include <src/misc/lv_style_gen.h>
#include <src/misc/lv_color.h>
#include "global_def.h"
#include "lvgl.h"
#include "stdio.h"
#include "ui_style.h"
#include "common_widget.h"
#include "route.h"

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_26)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_30)

lv_obj_t* user_label_view = 0;
lv_obj_t* uesr_label_text = 0;
lv_obj_t* uesr_label_sure_btn = 0;
lv_obj_t* uesr_label_sure_btn_text = 0;

// 声明 main_menu_view 为外部变量
extern lv_obj_t* main_menu_view;

// static void user_selected_event(lv_event_t* e) {
//   lv_obj_t* obj = lv_event_get_target(e);
//   // 重置所有方形的边框透明度
//   lv_obj_set_style_border_opa(simplified_chinese_square, LV_OPA_0, 0);
//   lv_obj_set_style_border_opa(traditional_chinese_square, LV_OPA_0, 0);
//   lv_obj_set_style_border_opa(english_square, LV_OPA_0, 0);
//   lv_obj_set_style_bg_opa(simplified_chinese_square, LV_OPA_100, 0);
//   lv_obj_set_style_bg_opa(traditional_chinese_square, LV_OPA_100, 0);
//   lv_obj_set_style_bg_opa(english_square, LV_OPA_100, 0);
//   lv_obj_set_style_text_color(simplified_chinese_selection_text,
//                               lv_color_hex(0xFFFFFF), 0);
//   lv_obj_set_style_text_color(traditional_chinese_selection_text,
//                               lv_color_hex(0xFFFFFF), 0);
//   lv_obj_set_style_text_color(english_selection_text, lv_color_hex(0xFFFFFF),
//                               0);
//   // 设置被点击方形的边框透明度为0
//   lv_obj_set_style_border_opa(obj, LV_OPA_100, 0);
//   lv_obj_set_style_bg_opa(obj, LV_OPA_0, 0);
//   // 根据点击的方形设置对应的文字颜色
//   if (obj == simplified_chinese_square) {
//     lv_obj_set_style_text_color(simplified_chinese_selection_text,
//                                 lv_color_hex(0xE9BD86), 0);
//   } else if (obj == traditional_chinese_square) {
//     lv_obj_set_style_text_color(traditional_chinese_selection_text,
//                                 lv_color_hex(0xE9BD86), 0);
//   } else if (obj == english_square) {
//     lv_obj_set_style_text_color(english_selection_text,
//     lv_color_hex(0xE9BD86),
//                                 0);
//   }
// }

// 定义返回按钮的点击事件回调函数
static void back_btn_click_event(lv_event_t* e) {
  // 加载主菜单视图
  navigate_to_view("main_menu_view");
}

lv_obj_t* user_label_view_init(void) {
  user_label_view = lv_obj_create(NULL);
  lv_obj_set_size(user_label_view, 1280, 480);
  lv_obj_set_style_bg_color(user_label_view, lv_color_hex(0x000000), 0);

  // 创建返回按钮并绑定点击事件
  lv_obj_t* back_btn =
      create_back_btn(user_label_view, back_btn_click_event, 0);

  uesr_label_text = lv_label_create(user_label_view);
  lv_label_set_text(uesr_label_text, "用户");
  lv_obj_set_style_text_color(uesr_label_text, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_font(uesr_label_text, &HarmonyOS_Sans_SC_Regular_30, 0);
  lv_obj_set_width(uesr_label_text, 120);  // 设置标签宽度
  lv_obj_set_style_text_align(uesr_label_text, LV_TEXT_ALIGN_CENTER,
                              0);  // 添加文字居中对齐
  lv_obj_align(uesr_label_text, LV_ALIGN_CENTER, 0, -192);

  // 创建一个“确定”按钮
  uesr_label_sure_btn = lv_btn_create(user_label_view);
  lv_obj_add_style(uesr_label_sure_btn, &button_style, 0);
  lv_obj_align(uesr_label_sure_btn, LV_ALIGN_CENTER, 0, 169);  // 设置按钮位置

  uesr_label_sure_btn_text = lv_label_create(uesr_label_sure_btn);
  lv_label_set_text(uesr_label_sure_btn_text, "确定");
  lv_obj_set_width(uesr_label_sure_btn_text, 200);
  lv_obj_set_style_text_color(uesr_label_sure_btn_text, lv_color_hex(0xFFFFFF),
                              0);
  lv_obj_set_style_text_align(uesr_label_sure_btn_text, LV_TEXT_ALIGN_CENTER,
                              0);
  lv_obj_align(uesr_label_sure_btn_text, LV_ALIGN_CENTER, 0, 1);

  return user_label_view;
}