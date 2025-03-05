#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_scroll.h>
#include <src/core/lv_obj_style.h>
#include <src/display/lv_display.h>
#include <src/layouts/flex/lv_flex.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_event.h>
#include "global_def.h"
#include "lvgl.h"
#include "ui_style.h"
#include "stdio.h"
#include "route.h"

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_26)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_30)

lv_obj_t* main_menu_view = 0;
lv_obj_t* img_main_menu_bg = 0;
lv_obj_t* img_warning_icon = 0;
lv_obj_t* img_wifi_icon = 0;
lv_obj_t* main_menu_hot_water_text = 0;
lv_obj_t* main_menu_cold_water_text = 0;
lv_obj_t* sliding_panel = 0;

// 声明外部变量
extern lv_obj_t* screen_saver_view;
extern void screen_saver_view_init(void);
extern lv_obj_t* user_label_view;
extern lv_obj_t* child_lock_view;

const char* main_menu_img_list[] = {
    LVGL_IMAGE_PATH("main_menu_images/img_lock_screen_label_icon.png"),
    LVGL_IMAGE_PATH("main_menu_images/img_user_label_icon.png"),
    LVGL_IMAGE_PATH("main_menu_images/img_settings_label_icon.png"),
    LVGL_IMAGE_PATH("main_menu_images/img_collect_label_icon.png"),
    LVGL_IMAGE_PATH("main_menu_images/img_quick_cooked_rinse_label_icon.png"),
};

const char* coffee_icon_list[] = {
    LVGL_IMAGE_PATH("main_menu_images/expresso_icon_1.png"),
    LVGL_IMAGE_PATH("main_menu_images/americano_icon_2.png"),
    LVGL_IMAGE_PATH("main_menu_images/latte_icon_3.png"),
    LVGL_IMAGE_PATH("main_menu_images/cappuccino_icon_4.png"),
    LVGL_IMAGE_PATH("main_menu_images/macchiato_icon_5.png"),
    LVGL_IMAGE_PATH("main_menu_images/ristretto_icon_6.png"),
    LVGL_IMAGE_PATH("main_menu_images/fresh_ground_coffee_icon_7.png"),
    LVGL_IMAGE_PATH("main_menu_images/latte_macchiato_icon_8.png"),

};

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

// 定义返回按钮的点击事件回调函数
static void func_label_click_event(lv_event_t* e) {
  lv_obj_t* label_obj = lv_event_get_target(e);
  // 获取用户数据
  int index = (int)lv_event_get_user_data(e);
  switch (index) {
    case 0:
      navigate_to_view("child_lock_view");
      break;
    case 1:
      navigate_to_view("user_label_view");
      break;
    default:
      break;
  }
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

  lv_obj_t* img = lv_image_create(inside_panel);
  lv_image_set_src(img, img_path);
  lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  // 隔开icon和文字的空隙
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
  lv_obj_add_flag(label, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
}

static void coffee_options_method(const char* icon_path, const char* icon_text,
                                  int index) {
  // 创建一个内小面板对象
  lv_obj_t* sliding_inside_panel = lv_obj_create(sliding_panel);
  // 禁用 sliding_inside_panel 的滚动
  lv_obj_set_scroll_dir(sliding_inside_panel, LV_DIR_NONE);
  lv_obj_set_size(sliding_inside_panel, 230, 304);
  lv_obj_set_style_bg_color(sliding_inside_panel, lv_color_hex(0x000000), 0);
  lv_obj_set_style_bg_opa(sliding_inside_panel, LV_OPA_0, 0);
  lv_obj_set_style_radius(sliding_inside_panel, 0, 0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(sliding_inside_panel, 0,
                                0);  // 设置边框的宽度为0像素
  lv_obj_add_flag(sliding_inside_panel,
                  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t* img = lv_image_create(sliding_inside_panel);
  lv_image_set_src(img, icon_path);
  lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
  // img居中
  lv_obj_align(img, LV_ALIGN_CENTER, 0, -22);

  lv_obj_t* sliding_inside_text = lv_label_create(sliding_inside_panel);
  lv_label_set_text(sliding_inside_text, icon_text);
  lv_obj_set_style_text_color(sliding_inside_text, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_font(sliding_inside_text, &HarmonyOS_Sans_SC_Regular_26,
                             0);
  // 居中对齐
  lv_obj_align(sliding_inside_text, LV_ALIGN_CENTER, 0, 135);
  lv_obj_add_flag(sliding_inside_text,
                  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
}

// 添加滑动结束事件处理函数
static void sliding_panel_scroll_end_event(lv_event_t* e) {
  lv_obj_t* panel = lv_event_get_target(e);
  lv_coord_t scroll_x = lv_obj_get_scroll_x(panel);
  lv_coord_t scroll_left = lv_obj_get_scroll_left(panel);  // 获取左侧滚动区域
  lv_coord_t scroll_right = lv_obj_get_scroll_right(panel);  // 获取右侧滚动区域
  lv_coord_t panel_width = lv_obj_get_width(panel);

  // 计算滚动区域的结束位置
  lv_coord_t scroll_end_x = scroll_left + scroll_right + panel_width;

  // 如果滚动到最右边，调整位置使最后一张图片停在距离右边距 25px 的位置
  if (scroll_x + panel_width >= scroll_end_x) {
    lv_obj_scroll_to_x(panel, scroll_end_x - panel_width + 25, LV_ANIM_ON);
  }
}

lv_obj_t* main_menu_view_init(void) {
  main_menu_view = lv_obj_create(NULL);
  lv_obj_set_size(main_menu_view, 1280, 480);
  lv_obj_set_style_bg_color(main_menu_view, lv_color_hex(0x000000), 0);
  // 取消内边距
  lv_obj_set_style_pad_all(main_menu_view, 0, 0);
  // 禁用 main_menu_view 的滚动
  lv_obj_set_scroll_dir(main_menu_view, LV_DIR_NONE);

  img_main_menu_bg = lv_image_create(main_menu_view);
  lv_image_set_src(img_main_menu_bg,
                   LVGL_IMAGE_PATH("main_menu_images/img_main_menu_bg.png"));
  lv_obj_center(img_main_menu_bg);

  // 创建一个滑动外面板对象
  sliding_panel = lv_obj_create(main_menu_view);
  lv_obj_set_size(sliding_panel, 1280, 304);
  lv_obj_set_flex_flow(sliding_panel, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(sliding_panel, LV_FLEX_ALIGN_START,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  // 设置子元素之间的间隔为 20px
  lv_obj_set_style_pad_column(sliding_panel, 20, 0);
  lv_obj_set_pos(sliding_panel, 0, 54);
  lv_obj_set_style_bg_color(sliding_panel, lv_color_hex(0x000000), 0);
  lv_obj_set_style_bg_opa(sliding_panel, LV_OPA_0, 0);
  lv_obj_set_style_radius(sliding_panel, 0, 0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(sliding_panel, 0, 0);  // 设置边框的宽度为0像素
  lv_obj_set_scrollbar_mode(sliding_panel,
                            LV_SCROLLBAR_MODE_OFF);  // 取消滑动效果
  // 设置左边距为 25px
  lv_obj_set_style_pad_left(sliding_panel, 25, 0);
  // 设置右边距为 25px
  lv_obj_set_style_pad_right(sliding_panel, 25, 0);
  // 设置上边距为 0px
  lv_obj_set_style_pad_top(sliding_panel, 0, 0);
  // 设置下边距为 0px
  lv_obj_set_style_pad_bottom(sliding_panel, 0, 0);
  // 启用水平滚动对齐
  // lv_obj_set_scroll_snap_x(sliding_panel, LV_SCROLL_SNAP_START);
  // lv_obj_scroll_to_x(sliding_panel, -25, LV_ANIM_OFF);
  // 添加滑动结束事件回调
  lv_obj_add_event_cb(sliding_panel, sliding_panel_scroll_end_event,
                      LV_EVENT_SCROLL_END, NULL);
  lv_obj_add_flag(sliding_panel,
                  LV_OBJ_FLAG_CLICKABLE);  // 确保能点击到，不然点不到文字()

  coffee_options_method(coffee_icon_list[0], "意式浓缩", 0);
  coffee_options_method(coffee_icon_list[1], "美式咖啡", 1);
  coffee_options_method(coffee_icon_list[2], "拿铁咖啡", 2);
  coffee_options_method(coffee_icon_list[3], "卡布奇诺", 3);
  coffee_options_method(coffee_icon_list[4], "玛奇雅朵", 4);
  coffee_options_method(coffee_icon_list[5], "芮斯崔朵", 5);
  coffee_options_method(coffee_icon_list[6], "现磨咖啡", 6);
  coffee_options_method(coffee_icon_list[7], "拿铁玛奇朵", 7);

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

  return main_menu_view;
}