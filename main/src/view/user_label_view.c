#include <src/misc/lv_area.h>
#include "global_def.h"
#include "lvgl.h"
#include "stdio.h"
#include "ui_style.h"
#include "common_widget.h"
#include "route.h"

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_26)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_30)
// 添加函数原型声明
static void user_selected_method(const char* head_path, const char* head_text,
                                 int index);

lv_obj_t* user_label_view = 0;
lv_obj_t* user_label_text = 0;
lv_obj_t* user_label_sure_btn = 0;
lv_obj_t* user_label_sure_btn_text = 0;
lv_obj_t* user_sel_sliding_panel = 0;
static int user_count = 2;  // 记录当前用户数量

const char* user_head_list[] = {
    LVGL_IMAGE_PATH("uesr_label_images/img_selected_head_sculpture.png"),
    LVGL_IMAGE_PATH("uesr_label_images/img_add_uesr.png"),  // 添加用户按钮
    LVGL_IMAGE_PATH("uesr_label_images/img_unselected_head_sculpture.png"),

};

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

// 新增点击事件处理函数
static void add_user_handler(lv_event_t* e) {
  lv_obj_t* add_user_btn = lv_event_get_target(e);
  // 在添加按钮前插入新用户
  user_selected_method(user_head_list[2], "用户2", user_count);
  // 先移动添加按钮到新位置
  lv_obj_move_to_index(add_user_btn, -1);  // 移动到最后一个位置
  // 再更新滑动面板布局
  lv_obj_update_layout(user_sel_sliding_panel);

  user_count++;
}
// 新增事件转发函数
// 修改事件转发函数
static void event_forwarder(lv_event_t* e) {
  // 使用官方API获取事件目标对象
  lv_obj_t* target = lv_event_get_target(e);
  // 使用官方API获取父对象
  lv_obj_t* parent = lv_obj_get_parent(target);
  // 使用正确的事件发送API
  lv_obj_send_event(parent, LV_EVENT_CLICKED, NULL);
}
static void user_selected_method(const char* head_path, const char* head_text,
                                 int index) {
  // 创建一个内小面板对象
  lv_obj_t* sliding_inside_panel = lv_obj_create(user_sel_sliding_panel);
  // 禁用 sliding_inside_panel 的滚动
  lv_obj_set_scroll_dir(sliding_inside_panel, LV_DIR_NONE);
  lv_obj_set_size(sliding_inside_panel, 186, 223);
  lv_obj_set_style_bg_color(sliding_inside_panel, lv_color_hex(0x0F0C0A), 0);
  lv_obj_set_style_bg_opa(sliding_inside_panel, LV_OPA_100, 0);
  lv_obj_set_style_radius(sliding_inside_panel, 0, 0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(sliding_inside_panel, 2,
                                0);  // 设置边框的宽度为0像素
  lv_obj_set_style_border_color(sliding_inside_panel, lv_color_hex(0xE9BD86),
                                0);
  lv_obj_set_style_border_opa(sliding_inside_panel, LV_OPA_100, 0);
  lv_obj_add_flag(sliding_inside_panel,
                  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
  // 添加高级点击穿透
  lv_obj_add_flag(sliding_inside_panel, LV_OBJ_FLAG_ADV_HITTEST);

  // 创建一个圆
  lv_obj_t* circle = lv_obj_create(sliding_inside_panel);
  lv_obj_set_size(circle, 120, 120);
  lv_obj_set_style_radius(circle, 60, 0);
  lv_obj_set_style_bg_color(circle, lv_color_hex(0x1F1915), 0);
  lv_obj_set_style_border_width(circle, 0, 0);
  lv_obj_align(circle, LV_ALIGN_CENTER, 0, -30);

  lv_obj_t* img = lv_image_create(sliding_inside_panel);
  lv_image_set_src(img, head_path);
  // 仅保留一次点击标志和事件绑定
  lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_event_cb(img, event_forwarder, LV_EVENT_CLICKED, NULL);
  lv_obj_clear_flag(img, LV_OBJ_FLAG_EVENT_BUBBLE);
  // img居中
  lv_obj_align(img, LV_ALIGN_CENTER, 0, -30);
  // 删除重复的点击标志设置和事件绑定
  // lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
  // lv_obj_add_event_cb(img, event_forwarder, LV_EVENT_CLICKED, NULL);

  lv_obj_t* user_name_text = lv_label_create(sliding_inside_panel);
  lv_label_set_text(user_name_text, head_text);
  lv_obj_set_style_text_color(user_name_text, lv_color_hex(0xE9BD86), 0);
  lv_obj_set_style_text_font(user_name_text, &HarmonyOS_Sans_SC_Regular_26, 0);
  // 居中对齐
  lv_obj_align(user_name_text, LV_ALIGN_CENTER, 0, 75);
  lv_obj_add_flag(user_name_text, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_clear_flag(user_name_text, LV_OBJ_FLAG_EVENT_BUBBLE);
  // 添加按钮（索引1）绑定特殊事件
  if (index == 1) {
    lv_obj_add_event_cb(sliding_inside_panel, add_user_handler,
                        LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_bg_color(sliding_inside_panel, lv_color_hex(0x1A1A1A),
                              0);  // 区别样式
  }
}

static void sliding_panel_scroll_end_event(lv_event_t* e) {
  lv_obj_t* panel = lv_event_get_target(e);
  lv_coord_t scroll_x = lv_obj_get_scroll_x(panel);
  lv_coord_t scroll_left = lv_obj_get_scroll_left(panel);  // 获取左侧滚动区域
  lv_coord_t scroll_right = lv_obj_get_scroll_right(panel);  // 获取右侧滚动区域
  lv_coord_t panel_width = lv_obj_get_width(panel);

  // 计算滚动区域的结束位置
  lv_coord_t scroll_end_x = scroll_left + scroll_right + panel_width;

  // 如果滚动到最右边，调整位置使最后一张图片停在距离右边距 44px 的位置
  if (scroll_x + panel_width >= scroll_end_x) {
    lv_obj_scroll_to_x(panel, scroll_end_x - panel_width + 44, LV_ANIM_ON);
  }
}

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

  user_label_text = lv_label_create(user_label_view);
  lv_label_set_text(user_label_text, "用户");
  lv_obj_set_style_text_color(user_label_text, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_font(user_label_text, &HarmonyOS_Sans_SC_Regular_30, 0);
  lv_obj_set_width(user_label_text, 120);  // 设置标签宽度
  lv_obj_set_style_text_align(user_label_text, LV_TEXT_ALIGN_CENTER,
                              0);  // 添加文字居中对齐
  lv_obj_align(user_label_text, LV_ALIGN_CENTER, 0, -192);

  // 创建一个滑动外面板对象
  user_sel_sliding_panel = lv_obj_create(user_label_view);
  lv_obj_set_size(user_sel_sliding_panel, 1280, 244);
  lv_obj_set_flex_flow(user_sel_sliding_panel, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(user_sel_sliding_panel, LV_FLEX_ALIGN_START,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);
  // 设置子元素之间的间隔为 15px
  lv_obj_set_style_pad_column(user_sel_sliding_panel, 15, 0);
  lv_obj_set_pos(user_sel_sliding_panel, 0, 97);
  lv_obj_set_style_bg_color(user_sel_sliding_panel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_bg_opa(user_sel_sliding_panel, LV_OPA_0, 0);
  lv_obj_set_style_radius(user_sel_sliding_panel, 0,
                          0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(user_sel_sliding_panel, 0,
                                0);  // 设置边框的宽度为0像素
  lv_obj_set_scrollbar_mode(user_sel_sliding_panel,
                            LV_SCROLLBAR_MODE_OFF);  // 取消滑动效果
  // 设置左边距为 44px
  lv_obj_set_style_pad_left(user_sel_sliding_panel, 44, 0);
  // 设置右边距为 44px
  lv_obj_set_style_pad_right(user_sel_sliding_panel, 44, 0);
  // 设置上边距为 0px
  lv_obj_set_style_pad_top(user_sel_sliding_panel, 0, 0);
  // 设置下边距为 0px
  lv_obj_set_style_pad_bottom(user_sel_sliding_panel, 0, 0);
  // 添加滑动结束事件回调
  lv_obj_add_event_cb(user_sel_sliding_panel, sliding_panel_scroll_end_event,
                      LV_EVENT_SCROLL_END, NULL);
  lv_obj_add_flag(user_sel_sliding_panel,
                  LV_OBJ_FLAG_CLICKABLE);  // 确保能点击到，不然点不到文字()

  // 创建一个内小面板对象
  user_selected_method(user_head_list[0], "标准用户", 0);
  user_selected_method(user_head_list[1], "添加用户", 1);  // 添加按钮
  // user_selected_method(user_head_list[2], "用户2", 2);

  // 创建一个“确定”按钮
  user_label_sure_btn = lv_btn_create(user_label_view);
  lv_obj_add_style(user_label_sure_btn, &button_style, 0);
  lv_obj_align(user_label_sure_btn, LV_ALIGN_CENTER, 0, 169);  // 设置按钮位置

  user_label_sure_btn_text = lv_label_create(user_label_sure_btn);
  lv_label_set_text(user_label_sure_btn_text, "确定");
  lv_obj_set_width(user_label_sure_btn_text, 200);
  lv_obj_set_style_text_color(user_label_sure_btn_text, lv_color_hex(0xFFFFFF),
                              0);
  lv_obj_set_style_text_align(user_label_sure_btn_text, LV_TEXT_ALIGN_CENTER,
                              0);
  lv_obj_align(user_label_sure_btn_text, LV_ALIGN_CENTER, 0, 1);

  return user_label_view;
}