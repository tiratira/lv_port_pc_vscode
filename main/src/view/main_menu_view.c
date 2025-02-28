#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_style.h>
#include <src/display/lv_display.h>
#include <src/layouts/flex/lv_flex.h>
#include <src/misc/lv_event.h>
#include "global_def.h"
#include "lvgl.h"
#include "ui_style.h"
#include "stdio.h"

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_26)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_30)

lv_obj_t* main_menu_view = 0;
lv_obj_t* img_main_menu_bg = 0;
lv_obj_t* img_warning_icon = 0;
lv_obj_t* img_wifi_icon = 0;
lv_obj_t* main_menu_hot_water_text = 0;
lv_obj_t* main_menu_cold_water_text = 0;

const char* main_menu_img_list[] = {
    LVGL_IMAGE_PATH("main_menu_images/img_lock_screen_label_icon.png"),
    LVGL_IMAGE_PATH("main_menu_images/img_user_label_icon.png"),
    LVGL_IMAGE_PATH("main_menu_images/img_settings_label_icon.png"),
    LVGL_IMAGE_PATH("main_menu_images/img_collect_label_icon.png"),
    LVGL_IMAGE_PATH("main_menu_images/img_quick_cooked_rinse_label_icon.png"),
};

extern lv_obj_t* screen_saver_view;
extern void screen_saver_view_init(void);

static void h_or_c_text_click_event(lv_event_t* e) {
  lv_obj_t* obj = lv_event_get_target(e);
  // 重置文本颜色
  lv_obj_set_style_text_color(main_menu_hot_water_text, lv_color_hex(0xFFFFFF),
                              0);
  lv_obj_set_style_text_color(main_menu_cold_water_text, lv_color_hex(0xFFFFFF),
                              0);
  // 根据点击的方形设置对应的文字颜色
  if (obj == main_menu_hot_water_text) {
    lv_obj_set_style_text_color(main_menu_hot_water_text,
                                lv_color_hex(0xE9BD85), 0);
  } else if (obj == main_menu_cold_water_text) {
    lv_obj_set_style_text_color(main_menu_cold_water_text,
                                lv_color_hex(0xE9BD85), 0);
  }
}

static void func_label_click_event(lv_event_t* e) {
  lv_obj_t* label_obj = lv_event_get_target(e);
  // 获取用户数据
  int index = (int)lv_event_get_user_data(e);
  printf("index = %d\n", index);
  // 根据点击的方形设置对应的文字颜色
  // if (label_obj == main_menu_hot_water_text) {
  //   lv_obj_set_style_text_color(main_menu_hot_water_text,
  //                               lv_color_hex(0xE9BD85), 0);
  // } else if (label_obj == main_menu_cold_water_text) {
  //   lv_obj_set_style_text_color(main_menu_cold_water_text,
  //                               lv_color_hex(0xE9BD85), 0);
  // }
}

// 制作通用的图片加文字这种表达形式的方法
static void build_label_method(const char* img_path, const char* text,
                               int32_t x, int32_t y, int index) {
  // 创建一个外面板对象
  lv_obj_t* outside_panel = lv_obj_create(main_menu_view);
  lv_obj_set_size(outside_panel, 210, 64);
  lv_obj_set_pos(outside_panel, x, y);
  lv_obj_set_style_bg_color(outside_panel, lv_color_hex(0x000000), 0);
  lv_obj_set_style_bg_opa(outside_panel, LV_OPA_0, 0);
  lv_obj_set_style_radius(outside_panel, 0, 0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(outside_panel, 0, 0);  // 设置边框的宽度为0像素
  lv_obj_set_scrollbar_mode(outside_panel,
                            LV_SCROLLBAR_MODE_OFF);  // 取消滑动效果
  lv_obj_add_flag(outside_panel,
                  LV_OBJ_FLAG_CLICKABLE);  // 确保能点击到，不然点不到文字()
  lv_obj_add_event_cb(outside_panel, func_label_click_event, LV_EVENT_CLICKED,
                      (void*)index);  // 注册点击事件回调函数
  // 创建一个内小面板对象
  lv_obj_t* inside_panel = lv_obj_create(outside_panel);
  lv_obj_set_flex_flow(inside_panel, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(inside_panel, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_size(inside_panel, 180, 64);
  lv_obj_set_align(inside_panel, LV_ALIGN_CENTER);  // 居中对齐()
  lv_obj_set_style_bg_color(inside_panel, lv_color_hex(0x000000), 0);
  lv_obj_set_style_bg_opa(inside_panel, LV_OPA_0, 0);
  lv_obj_set_style_radius(inside_panel, 0, 0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(inside_panel, 0, 0);  // 设置边框的宽度为0像素
  lv_obj_set_scrollbar_mode(inside_panel,
                            LV_SCROLLBAR_MODE_OFF);  // 取消滑动效果
  lv_obj_add_flag(inside_panel,
                  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  // 隔开icon和文字的空隙
  lv_obj_t* img = lv_image_create(inside_panel);
  lv_image_set_src(img, img_path);
  lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t* mini_panel = lv_obj_create(inside_panel);
  lv_obj_set_size(mini_panel, 10, 64);
  lv_obj_set_style_bg_color(mini_panel, lv_color_hex(0x000000), 0);
  lv_obj_set_style_bg_opa(mini_panel, LV_OPA_0, 0);
  lv_obj_set_style_radius(mini_panel, 0, 0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(mini_panel, 0, 0);  // 设置边框的宽度为0像素
  lv_obj_set_scrollbar_mode(mini_panel, LV_SCROLLBAR_MODE_OFF);  // 取消滑动效果
  lv_obj_add_flag(mini_panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t* label = lv_label_create(inside_panel);
  lv_label_set_text(label, text);
  lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_font(label, &HarmonyOS_Sans_SC_Regular_26, 0);
  lv_obj_add_flag(mini_panel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
}

void main_menu_view_init(void) {
  main_menu_view = lv_obj_create(NULL);
  lv_obj_set_size(main_menu_view, 1280, 480);
  lv_obj_set_style_bg_color(main_menu_view, lv_color_hex(0x000000), 0);

  img_main_menu_bg = lv_image_create(main_menu_view);
  lv_image_set_src(img_main_menu_bg,
                   LVGL_IMAGE_PATH("main_menu_images/img_main_menu_bg.png"));
  lv_obj_center(img_main_menu_bg);

  main_menu_hot_water_text = lv_label_create(main_menu_view);
  lv_label_set_text(main_menu_hot_water_text, "热饮");
  lv_obj_add_flag(main_menu_hot_water_text,
                  LV_OBJ_FLAG_CLICKABLE);  // 确保能点击到，不然点不到文字
  lv_obj_set_style_text_color(main_menu_hot_water_text, lv_color_hex(0xE9BD85),
                              0);  // 设置标签宽度
  lv_obj_set_style_text_font(main_menu_hot_water_text,
                             &HarmonyOS_Sans_SC_Regular_26, 0);  // 设置标签宽度
  lv_obj_set_width(main_menu_hot_water_text, 200);  // 设置标签宽度
  lv_obj_set_height(main_menu_hot_water_text, 78);  // 设置标签高度
  lv_obj_set_style_text_align(main_menu_hot_water_text, LV_TEXT_ALIGN_CENTER,
                              0);  // 添加文字居中对齐
  lv_obj_set_style_pad_top(
      main_menu_hot_water_text,
      (78 - lv_font_get_line_height(&HarmonyOS_Sans_SC_Regular_26)) / 2,
      0);  // 添加顶部内边距实现垂直居中
  lv_obj_align(main_menu_hot_water_text, LV_ALIGN_CENTER, -98, -188);
  lv_obj_add_event_cb(main_menu_hot_water_text, h_or_c_text_click_event,
                      LV_EVENT_CLICKED, NULL);

  main_menu_cold_water_text = lv_label_create(main_menu_view);
  lv_label_set_text(main_menu_cold_water_text, "冷饮");
  lv_obj_add_flag(main_menu_cold_water_text,
                  LV_OBJ_FLAG_CLICKABLE);  // 确保能点击到，不然点不到文字
  lv_obj_set_style_text_color(main_menu_cold_water_text, lv_color_hex(0xFFFFFF),
                              0);
  lv_obj_set_style_text_font(main_menu_cold_water_text,
                             &HarmonyOS_Sans_SC_Regular_26, 0);
  lv_obj_set_width(main_menu_cold_water_text, 200);  // 设置标签宽度
  lv_obj_set_height(main_menu_cold_water_text, 78);  // 设置标签高度
  lv_obj_set_style_text_align(main_menu_cold_water_text, LV_TEXT_ALIGN_CENTER,
                              0);  // 添加文字居中对齐
  lv_obj_set_style_pad_top(
      main_menu_cold_water_text,
      (78 - lv_font_get_line_height(&HarmonyOS_Sans_SC_Regular_26)) / 2,
      0);  // 添加顶部内边距实现垂直居中
  lv_obj_align(main_menu_cold_water_text, LV_ALIGN_CENTER, 98, -188);
  lv_obj_add_event_cb(main_menu_cold_water_text, h_or_c_text_click_event,
                      LV_EVENT_CLICKED, NULL);

  img_warning_icon = lv_image_create(main_menu_view);
  lv_image_set_src(img_warning_icon,
                   LVGL_IMAGE_PATH("main_menu_images/img_warning_icon.png"));
  // build_label_method(const char *img_path, const char *text, int x, int y)
  lv_obj_align(img_warning_icon, LV_ALIGN_CENTER, 502, -201);
  img_wifi_icon = lv_image_create(main_menu_view);
  lv_image_set_src(img_wifi_icon,
                   LVGL_IMAGE_PATH("main_menu_images/img_wifi_icon.png"));
  lv_obj_align(img_wifi_icon, LV_ALIGN_CENTER, 571, -201);

  build_label_method(main_menu_img_list[0], "锁屏", 25, 406, 0);
  build_label_method(main_menu_img_list[1], "用户", 280, 406, 1);
  build_label_method(main_menu_img_list[2], "设置", 535, 406, 2);
  build_label_method(main_menu_img_list[3], "收藏", 790, 406, 3);
  build_label_method(main_menu_img_list[4], "快速冲洗", 1045, 406, 4);
}