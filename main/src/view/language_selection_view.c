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

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_26)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_30)

lv_obj_t* lan_sel_view = 0;
lv_obj_t* lan_sel_text = 0;
lv_obj_t* simplified_chinese_square = 0;
lv_obj_t* traditional_chinese_square = 0;
lv_obj_t* english_square = 0;
lv_obj_t* simplified_chinese_selection_text = 0;
lv_obj_t* traditional_chinese_selection_text = 0;
lv_obj_t* english_selection_text = 0;
lv_obj_t* lan_sel_sure_btn = 0;
lv_obj_t* sure_btn_label = 0;

static void square_click_event(lv_event_t* e) {
  lv_obj_t* obj = lv_event_get_target(e);
  // 重置所有方形的边框透明度
  lv_obj_set_style_border_opa(simplified_chinese_square, LV_OPA_0, 0);
  lv_obj_set_style_border_opa(traditional_chinese_square, LV_OPA_0, 0);
  lv_obj_set_style_border_opa(english_square, LV_OPA_0, 0);
  lv_obj_set_style_bg_opa(simplified_chinese_square, LV_OPA_100, 0);
  lv_obj_set_style_bg_opa(traditional_chinese_square, LV_OPA_100, 0);
  lv_obj_set_style_bg_opa(english_square, LV_OPA_100, 0);
  lv_obj_set_style_text_color(simplified_chinese_selection_text,
                              lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_color(traditional_chinese_selection_text,
                              lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_color(english_selection_text, lv_color_hex(0xFFFFFF),
                              0);
  // 设置被点击方形的边框透明度为0
  lv_obj_set_style_border_opa(obj, LV_OPA_100, 0);
  lv_obj_set_style_bg_opa(obj, LV_OPA_0, 0);
  // 根据点击的方形设置对应的文字颜色
  if (obj == simplified_chinese_square) {
    lv_obj_set_style_text_color(simplified_chinese_selection_text,
                                lv_color_hex(0xE9BD86), 0);
  } else if (obj == traditional_chinese_square) {
    lv_obj_set_style_text_color(traditional_chinese_selection_text,
                                lv_color_hex(0xE9BD86), 0);
  } else if (obj == english_square) {
    lv_obj_set_style_text_color(english_selection_text, lv_color_hex(0xE9BD86),
                                0);
  }
}

void lan_sel_view_init(void) {
  lan_sel_view = lv_obj_create(NULL);
  lv_obj_set_size(lan_sel_view, 1280, 480);
  lv_obj_set_style_bg_color(lan_sel_view, lv_color_hex(0x000000), 0);

  lan_sel_text = lv_label_create(lan_sel_view);
  lv_label_set_text(lan_sel_text, "语言选择");
  lv_obj_set_style_text_color(lan_sel_text, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_font(lan_sel_text, &HarmonyOS_Sans_SC_Regular_26, 0);
  lv_obj_set_width(lan_sel_text, 120);  // 设置标签宽度
  lv_obj_set_style_text_align(lan_sel_text, LV_TEXT_ALIGN_CENTER,
                              0);  // 添加文字居中对齐
  lv_obj_align(lan_sel_text, LV_ALIGN_CENTER, 0, -191);

  simplified_chinese_square = lv_obj_create(lan_sel_view);
  lv_obj_set_size(simplified_chinese_square, 130, 130);  // 设置方形大小
  lv_obj_set_style_radius(simplified_chinese_square, 0,
                          0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(simplified_chinese_square, 1,
                                0);  // 设置边框的宽度为1像素
  lv_obj_set_style_bg_color(simplified_chinese_square, lv_color_hex(0x121212),
                            0);  // 设置方形的背景颜色为深灰色
  lv_obj_set_style_bg_opa(simplified_chinese_square, LV_OPA_0, 0);
  lv_obj_set_style_border_color(simplified_chinese_square,
                                lv_color_hex(0xE9BD86), 0);
  // lv_obj_set_style_border_opa(simplified_chinese_square, LV_OPA_0, 0);
  lv_obj_align(simplified_chinese_square, LV_ALIGN_CENTER, -215,
               0);  // 方形位置
  // 为每个方形添加点击事件
  lv_obj_add_event_cb(simplified_chinese_square, square_click_event,
                      LV_EVENT_CLICKED, NULL);

  simplified_chinese_selection_text = lv_label_create(lan_sel_view);
  lv_label_set_text(simplified_chinese_selection_text, "简体中文");
  lv_obj_set_style_text_color(simplified_chinese_selection_text,
                              lv_color_hex(0xE9BD86), 0);
  lv_obj_set_style_text_font(simplified_chinese_selection_text,
                             &HarmonyOS_Sans_SC_Regular_26, 0);
  lv_obj_set_width(simplified_chinese_selection_text, 120);  // 设置标签宽度
  lv_obj_set_style_text_align(simplified_chinese_selection_text,
                              LV_TEXT_ALIGN_CENTER,
                              0);  // 添加文字居中对齐
  lv_obj_align(simplified_chinese_selection_text, LV_ALIGN_CENTER, -215, 0);

  traditional_chinese_square = lv_obj_create(lan_sel_view);
  lv_obj_set_size(traditional_chinese_square, 130, 130);  // 设置方形大小
  lv_obj_set_style_radius(traditional_chinese_square, 0,
                          0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(traditional_chinese_square, 1,
                                0);  // 设置边框的宽度为1像素
  lv_obj_set_style_bg_color(traditional_chinese_square, lv_color_hex(0x121212),
                            0);  // 设置方形的背景颜色为深灰色
  lv_obj_set_style_border_color(traditional_chinese_square,
                                lv_color_hex(0xE9BD86), 0);
  lv_obj_set_style_border_opa(traditional_chinese_square, LV_OPA_0, 0);
  lv_obj_align(traditional_chinese_square, LV_ALIGN_CENTER, 0, 0);  // 方形位置
  // 为每个方形添加点击事件
  lv_obj_add_event_cb(traditional_chinese_square, square_click_event,
                      LV_EVENT_CLICKED, NULL);

  traditional_chinese_selection_text = lv_label_create(lan_sel_view);
  lv_label_set_text(traditional_chinese_selection_text, "繁體中文");
  lv_obj_set_style_text_color(traditional_chinese_selection_text,
                              lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_font(traditional_chinese_selection_text,
                             &HarmonyOS_Sans_SC_Regular_26, 0);
  lv_obj_set_width(traditional_chinese_selection_text, 120);  // 设置标签宽度
  lv_obj_set_style_text_align(traditional_chinese_selection_text,
                              LV_TEXT_ALIGN_CENTER,
                              0);  // 添加文字居中对齐
  lv_obj_align(traditional_chinese_selection_text, LV_ALIGN_CENTER, 0, 0);

  english_square = lv_obj_create(lan_sel_view);
  lv_obj_set_size(english_square, 130, 130);      // 设置方形大小
  lv_obj_set_style_radius(english_square, 0, 0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(english_square, 1, 0);  // 设置边框的宽度为1像素
  lv_obj_set_style_bg_color(english_square, lv_color_hex(0x121212),
                            0);  // 设置方形的背景颜色为深灰色
  lv_obj_set_style_border_color(english_square, lv_color_hex(0xE9BD86), 0);
  lv_obj_set_style_border_opa(english_square, LV_OPA_0, 0);
  lv_obj_align(english_square, LV_ALIGN_CENTER, 215, 0);  // 方形位置
  // 为每个方形添加点击事件
  lv_obj_add_event_cb(english_square, square_click_event, LV_EVENT_CLICKED,
                      NULL);

  english_selection_text = lv_label_create(lan_sel_view);
  lv_label_set_text(english_selection_text, "English");
  lv_obj_set_style_text_color(english_selection_text, lv_color_hex(0xFFFFFF),
                              0);
  lv_obj_set_style_text_font(english_selection_text,
                             &HarmonyOS_Sans_SC_Regular_26, 0);
  lv_obj_set_width(english_selection_text, 120);  // 设置标签宽度
  lv_obj_set_style_text_align(english_selection_text, LV_TEXT_ALIGN_CENTER,
                              0);  // 添加文字居中对齐
  lv_obj_align(english_selection_text, LV_ALIGN_CENTER, 215, 0);
  // 创建一个“确定”按钮
  lan_sel_sure_btn = lv_btn_create(lan_sel_view);
  lv_obj_add_style(lan_sel_sure_btn, &button_style, 0);
  lv_obj_align(lan_sel_sure_btn, LV_ALIGN_CENTER, 0, 182);  // 设置按钮位置

  sure_btn_label = lv_label_create(lan_sel_sure_btn);
  lv_label_set_text(sure_btn_label, "确定");
  lv_obj_set_width(sure_btn_label, 200);
  lv_obj_set_style_text_color(sure_btn_label, lv_color_hex(0xE9BD86), 0);
  lv_obj_set_style_text_align(sure_btn_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(sure_btn_label, LV_ALIGN_CENTER, 0, 1);
}