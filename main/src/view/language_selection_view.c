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

typedef struct {
    lv_obj_t* square;
    lv_obj_t* label;
    const char* text;
    int32_t x_pos;
} LangOption;

static LangOption lang_options[3];
lv_obj_t* lan_sel_view = 0;
lv_obj_t* lan_sel_text = 0;
lv_obj_t* lan_sel_sure_btn = 0;
lv_obj_t* sure_btn_label = 0;

static void square_click_event(lv_event_t* e) {
  lv_obj_t* obj = lv_event_get_target(e);
  
  for (int i = 0; i < 3; i++) {
    lv_obj_set_style_border_opa(lang_options[i].square, LV_OPA_0, 0);
    lv_obj_set_style_bg_opa(lang_options[i].square, LV_OPA_100, 0);
    lv_obj_set_style_text_color(lang_options[i].label, lv_color_hex(0xFFFFFF), 0);
    
    if (obj == lang_options[i].square) {
      lv_obj_set_style_border_opa(obj, LV_OPA_100, 0);
      lv_obj_set_style_bg_opa(obj, LV_OPA_0, 0);
      lv_obj_set_style_text_color(lang_options[i].label, lv_color_hex(0xE9BD86), 0);
    }
  }
}

lv_obj_t* lan_sel_view_init(void) {
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

  // 初始化样式
  static lv_style_t base_style;
  static lv_style_t label_style;
  lv_style_init(&base_style);
  lv_style_set_radius(&base_style, 0);
  lv_style_set_border_width(&base_style, 1);
  lv_style_set_bg_color(&base_style, lv_color_hex(0x121212));
  lv_style_set_bg_opa(&base_style, LV_OPA_0);
  lv_style_set_border_color(&base_style, lv_color_hex(0xE9BD86));

  lv_style_init(&label_style);
  lv_style_set_text_font(&label_style, &HarmonyOS_Sans_SC_Regular_26);
  lv_style_set_width(&label_style, 120);
  lv_style_set_text_align(&label_style, LV_TEXT_ALIGN_CENTER);
  // 语言选项配置
  const struct {
    const char* text;
    int32_t x_pos;
  } lang_config[3] = {
    {"简体中文", -215},
    {"繁體中文", 0},
    {"English", 215}
  };
  // 创建语言选项
  for (int i = 0; i < 3; i++) {
    // 创建方形
    lang_options[i].square = lv_obj_create(lan_sel_view);
    lv_obj_add_style(lang_options[i].square, &base_style, 0);
    lv_obj_set_size(lang_options[i].square, 130, 130);
    lv_obj_align(lang_options[i].square, LV_ALIGN_CENTER, lang_config[i].x_pos, 0);
    lv_obj_add_event_cb(lang_options[i].square, square_click_event, LV_EVENT_CLICKED, NULL);
  // 创建标签
  lang_options[i].label = lv_label_create(lan_sel_view);
  lv_label_set_text(lang_options[i].label, lang_config[i].text);
  lv_obj_add_style(lang_options[i].label, &label_style, 0);
  lv_obj_align(lang_options[i].label, LV_ALIGN_CENTER, lang_config[i].x_pos, 0);
  
  // 设置默认选中状态
  if(i == 0) {
      lv_obj_set_style_border_opa(lang_options[i].square, LV_OPA_100, 0);
      lv_obj_set_style_text_color(lang_options[i].label, lv_color_hex(0xE9BD86), 0);
  } else {
      lv_obj_set_style_bg_opa(lang_options[i].square, LV_OPA_100, 0);
      lv_obj_set_style_border_opa(lang_options[i].square, LV_OPA_0, 0);
      lv_obj_set_style_text_color(lang_options[i].label, lv_color_hex(0xFFFFFF), 0);
  }
  }
  // 创建确定按钮
  lan_sel_sure_btn = lv_btn_create(lan_sel_view);
  lv_obj_add_style(lan_sel_sure_btn, &button_style, 0);
  lv_obj_align(lan_sel_sure_btn, LV_ALIGN_CENTER, 0, 182);  // 设置按钮位置

  sure_btn_label = lv_label_create(lan_sel_sure_btn);
  lv_label_set_text(sure_btn_label, "确定");
  lv_obj_set_width(sure_btn_label, 200);
  lv_obj_set_style_text_color(sure_btn_label, lv_color_hex(0xE9BD86), 0);
  lv_obj_set_style_text_align(sure_btn_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(sure_btn_label, LV_ALIGN_CENTER, 0, 1);
  return lan_sel_view;
}