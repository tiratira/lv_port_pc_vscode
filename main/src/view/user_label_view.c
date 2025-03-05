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

// 在全局变量区域添加状态跟踪变量
static lv_obj_t* selected_panel = NULL;
static lv_obj_t* selected_label = NULL;

lv_obj_t* user_label_view = 0;
lv_obj_t* user_label_text = 0;
lv_obj_t* user_label_sure_btn = 0;
lv_obj_t* user_label_sure_btn_text = 0;
lv_obj_t* user_sel_sliding_panel = 0;
static int user_count = 2;  // 记录当前用户数量

const char* user_head_list[] = {
    LVGL_IMAGE_PATH("user_label_images/img_selected_head_sculpture.png"),
    LVGL_IMAGE_PATH("user_label_images/img_add_user.png"),  // 添加用户按钮
    LVGL_IMAGE_PATH("user_label_images/img_unselected_head_sculpture.png"),

};

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

// 新增面板点击处理函数
static void panel_click_handler(lv_event_t* e) {
  lv_obj_t* panel = lv_event_get_target(e);
  lv_obj_t* label = (lv_obj_t*)lv_event_get_user_data(e);

  // 修正遍历逻辑：使用整型索引
  // 添加空指针检查
  if (selected_panel) {
    int32_t index = 0;
    lv_obj_t* child = lv_obj_get_child(selected_panel, index);
    while (child != NULL) {
      if (lv_obj_check_type(child, &lv_image_class)) {
        lv_image_set_src(child, user_head_list[2]);
        break;
      }
      index++;
      child = lv_obj_get_child(selected_panel, index);
    }
  }

  // 重置所有面板样式
  if (selected_panel && lv_obj_is_valid(selected_panel)) {
    lv_obj_set_style_border_opa(selected_panel, LV_OPA_0, 0);
    if (selected_label) {
      lv_obj_set_style_text_color(selected_label, lv_color_hex(0xFFFFFF), 0);
    }
  }
  // 设置当前选中样式
  if (panel && lv_obj_is_valid(panel)) {
    lv_obj_set_style_border_opa(panel, LV_OPA_100, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xE9BD86), 0);
  }

  // 修正第二个遍历逻辑
  int32_t new_index = 0;
  lv_obj_t* new_child = lv_obj_get_child(panel, new_index);
  while (new_child) {
    if (lv_obj_check_type(new_child, &lv_image_class)) {
      lv_image_set_src(new_child, user_head_list[0]);
      break;
    }
    new_index++;
    new_child = lv_obj_get_child(panel, new_index);
  }

  // 更新选中状态
  selected_panel = panel;
  selected_label = label;
}

static void user_selected_method(const char* head_path, const char* head_text,
                                 int index) {
  // 添加参数校验
  if (!head_path || !head_text || index < 0) return;

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
  lv_obj_set_style_border_opa(sliding_inside_panel, LV_OPA_0, 0);
  lv_obj_add_flag(sliding_inside_panel,
                  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
  // 添加高级点击穿透
  lv_obj_add_flag(sliding_inside_panel, LV_OBJ_FLAG_ADV_HITTEST);

  // 在创建对象后立即设置用户数据
  lv_obj_set_user_data(sliding_inside_panel, (void*)(intptr_t)index);

  // 创建一个圆
  lv_obj_t* circle = lv_obj_create(sliding_inside_panel);
  lv_obj_set_size(circle, 120, 120);
  lv_obj_set_style_radius(circle, 60, 0);
  lv_obj_set_style_bg_color(circle, lv_color_hex(0x1F1915), 0);
  lv_obj_set_style_border_width(circle, 0, 0);
  lv_obj_align(circle, LV_ALIGN_CENTER, 0, -30);
  lv_obj_add_flag(circle, LV_OBJ_FLAG_CLICKABLE);
  // 添加事件转发到父面板
  lv_obj_add_event_cb(circle, event_forwarder, LV_EVENT_CLICKED, NULL);
  lv_obj_clear_flag(circle, LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t* img = lv_image_create(sliding_inside_panel);
  lv_image_set_src(img, head_path);
  // 仅保留一次点击标志和事件绑定
  lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_event_cb(img, event_forwarder, LV_EVENT_CLICKED, NULL);
  lv_obj_clear_flag(img, LV_OBJ_FLAG_EVENT_BUBBLE);
  // img居中
  lv_obj_align(img, LV_ALIGN_CENTER, 0, -30);

  lv_obj_t* user_name_text = lv_label_create(sliding_inside_panel);
  lv_label_set_text(user_name_text, head_text);
  lv_obj_set_style_text_color(user_name_text, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_font(user_name_text, &HarmonyOS_Sans_SC_Regular_26, 0);
  // 居中对齐
  lv_obj_align(user_name_text, LV_ALIGN_CENTER, 0, 75);
  lv_obj_add_flag(user_name_text, LV_OBJ_FLAG_CLICKABLE);
  // 添加事件转发到父面板
  lv_obj_add_event_cb(user_name_text, event_forwarder, LV_EVENT_CLICKED, NULL);
  lv_obj_clear_flag(user_name_text, LV_OBJ_FLAG_EVENT_BUBBLE);

  // 修改面板事件绑定方式（确保事件参数正确传递）
  if (index != 1) {
    lv_obj_add_event_cb(sliding_inside_panel, panel_click_handler,
                        LV_EVENT_CLICKED, user_name_text);
    // 设置面板层级
    lv_obj_move_foreground(sliding_inside_panel);
  }

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

  // 创建默认用户面板
  user_selected_method(user_head_list[0], "标准用户", 0);
  user_selected_method(user_head_list[1], "添加用户", 1);  // 添加按钮

  // 新增：设置初始选中状态
  selected_panel =
      lv_obj_get_child(user_sel_sliding_panel, 0);  // 获取第一个面板
  if (selected_panel) {
    lv_obj_set_style_border_opa(selected_panel, LV_OPA_100, 0);
    // 修正后的遍历逻辑
    int32_t child_idx = 0;  // 使用整型索引
    lv_obj_t* label = lv_obj_get_child(selected_panel, child_idx);
    while (label) {
      if (lv_obj_check_type(label, &lv_label_class)) break;
      child_idx++;
      label = lv_obj_get_child(selected_panel, child_idx);
    }
    if (label) {
      lv_obj_set_style_text_color(label, lv_color_hex(0xE9BD86), 0);
      selected_label = label;
    }
  }

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