#include <src/misc/lv_area.h>
#include "global_def.h"
#include "lvgl.h"
#include "ui_style.h"
#include "stdio.h"
#include "common_widget.h"
#include "route.h"

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_24)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_26)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_28)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_30)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_34)

lv_obj_t* coffee_making_view = 0;
lv_obj_t* img_coffee_making_bg = 0;
lv_obj_t* coffee_making_sure_btn = 0;
lv_obj_t* coffee_making_cancel_btn = 0;
lv_obj_t* coffee_making_sure_btn_text = 0;
lv_obj_t* coffee_making_cancel_btn_text = 0;
lv_obj_t* coffee_making_outside_panel = 0;
lv_obj_t* coffee_making_inside_panel = 0;

// lv_obj_t* coffee_making_img = 0;

const char* coffee_making_img_list[] = {
    LVGL_IMAGE_PATH("coffee_making_images/making_americano_icon.png"),
    LVGL_IMAGE_PATH("coffee_making_images/making_latte_icon.png"),
};

// 定义一个函数，用于设置当前咖啡的图片和文字
// static void set_current_coffee(const char* coffee_name) {
//   // 根据咖啡名称获取对应的图片路径
//   const char* img_path = NULL;
//   if (strcmp(coffee_name, "Americano") == 0) {
//     img_path =
//         LVGL_IMAGE_PATH("coffee_making_images/making_americano_icon.png");
//   }
// }

// 定义一个函数，用于设置当前咖啡的开始制作按钮的点击事件
static void coffee_making_sure_btn_event(lv_event_t* e) {
  // 根据咖啡名称获取对应的开始制作按钮的点击事件
  const char* coffee_name = NULL;
}
// 定义一个函数，用于设置当前咖啡的取消按钮的点击事件
void coffee_making_cancel_btn_event(lv_event_t* e) {
  // 点击取消后跳转到main_menu_view
  navigate_to_view("main_menu_view");
}
// 定义返回按钮的点击事件回调函数
static void back_btn_click_event(lv_event_t* e) {
  // 加载主菜单视图
  navigate_to_view("main_menu_view");
}

// 制作内部面板的函数
static lv_obj_t* parameter_settings_panel_method(const char* icon_path,
                                                 const char* icon_text,
                                                 int index) {
  // 创建内部参数调整面板
  lv_obj_t* coffee_making_inside_panel =
      lv_obj_create(coffee_making_outside_panel);
  // 禁用 coffee_making_inside_panel 的滚动
  lv_obj_set_scroll_dir(coffee_making_inside_panel, LV_DIR_NONE);
  lv_obj_set_size(coffee_making_inside_panel, 230, 304);
  lv_obj_set_style_bg_color(coffee_making_inside_panel, lv_color_hex(0xE9BD86),
                            0);
  lv_obj_set_style_bg_opa(coffee_making_inside_panel, LV_OPA_0, 0);
  lv_obj_set_style_radius(coffee_making_inside_panel, 0,
                          0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(coffee_making_inside_panel, 0,
                                0);  // 设置边框的宽度为0像素
  lv_obj_add_flag(coffee_making_inside_panel,
                  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  //   lv_obj_t* img = lv_image_create(coffee_making_inside_panel);
  //   lv_image_set_src(img, icon_path);
  //   lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
  //   // img居中
  //   lv_obj_align(img, LV_ALIGN_CENTER, 0, -22);

  //   lv_obj_t* sliding_inside_text =
  //   lv_label_create(coffee_making_inside_panel);
  //   lv_label_set_text(sliding_inside_text, icon_text);
  //   lv_obj_set_style_text_color(sliding_inside_text, lv_color_hex(0xFFFFFF),
  //   0); lv_obj_set_style_text_font(sliding_inside_text,
  //   &HarmonyOS_Sans_SC_Regular_26,
  //                              0);
  //   // 居中对齐
  //   lv_obj_align(sliding_inside_text, LV_ALIGN_CENTER, 0, 135);
  //   lv_obj_add_flag(sliding_inside_text,
  //                   LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  return coffee_making_inside_panel;
}

// 制作内部图片函数
static lv_obj_t* coffee_making_img_name_panel_method(const char* icon_path,
                                                     const char* icon_text) {
  // 创建内部参数调整面板
  lv_obj_t* coffee_making_img_panel =
      lv_obj_create(coffee_making_outside_panel);
  // 禁用 coffee_making_img_panel 的滚动
  lv_obj_set_scroll_dir(coffee_making_img_panel, LV_DIR_NONE);
  lv_obj_set_size(coffee_making_img_panel, 230, 304);
  lv_obj_set_style_bg_color(coffee_making_img_panel, lv_color_hex(0xE9BD86), 0);
  lv_obj_set_style_bg_opa(coffee_making_img_panel, LV_OPA_0, 0);
  lv_obj_set_style_radius(coffee_making_img_panel, 0,
                          0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(coffee_making_img_panel, 0,
                                0);  // 设置边框的宽度为0像素
  lv_obj_add_flag(coffee_making_img_panel,
                  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t* coffee_making_name_text =
      lv_label_create(coffee_making_outside_panel);
  lv_label_set_text(coffee_making_name_text, icon_text);
  lv_obj_set_style_text_color(coffee_making_name_text, lv_color_hex(0xFFFFFF),
                              0);
  lv_obj_set_style_text_font(coffee_making_name_text,
                             &HarmonyOS_Sans_SC_Regular_30, 0);
  lv_obj_set_width(coffee_making_name_text, 200);  // 设置标签宽度
  lv_obj_set_style_text_align(coffee_making_name_text, LV_TEXT_ALIGN_CENTER,
                              0);  // 添加文字居中对齐
  lv_obj_align(coffee_making_name_text, LV_ALIGN_TOP_MID, 0, 0);

  return coffee_making_inside_panel;
}

lv_obj_t* coffee_making_view_init(void) {
  coffee_making_view = lv_obj_create(NULL);
  lv_obj_set_size(coffee_making_view, 1280, 480);
  lv_obj_set_style_bg_color(coffee_making_view, lv_color_hex(0x000000), 0);

  img_coffee_making_bg = lv_image_create(coffee_making_view);
  lv_image_set_src(img_coffee_making_bg,
                   LVGL_IMAGE_PATH("coffee_making_images/img_coffee_making_bg.png"));
  lv_obj_center(img_coffee_making_bg);

  // 创建制作页面外面板对象
  coffee_making_outside_panel = lv_obj_create(coffee_making_view);
  // 禁用 coffee_making_outside_panel 的滚动
  lv_obj_set_scroll_dir(coffee_making_outside_panel, LV_DIR_NONE);
  lv_obj_set_size(coffee_making_outside_panel, 1280, 334);
  lv_obj_set_style_bg_color(coffee_making_outside_panel, lv_color_hex(0xFFFFFF),
                            0);
  lv_obj_set_style_bg_opa(coffee_making_outside_panel, LV_OPA_10, 0);
  lv_obj_set_style_radius(coffee_making_outside_panel, 0,
                          0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(coffee_making_outside_panel, 0,
                                0);  // 设置边框的宽度为0像素
  lv_obj_set_scrollbar_mode(coffee_making_outside_panel,
                            LV_SCROLLBAR_MODE_OFF);  // 取消滑动效果
  // 设置左边距为 0px
  lv_obj_set_style_pad_left(coffee_making_outside_panel, 0, 0);
  // 设置右边距为 0px
  lv_obj_set_style_pad_right(coffee_making_outside_panel, 0, 0);
  // 设置上边距为 0px
  lv_obj_set_style_pad_top(coffee_making_outside_panel, 0, 0);
  // 设置下边距为 0px
  lv_obj_set_style_pad_bottom(coffee_making_outside_panel, 0, 0);
  lv_obj_align(coffee_making_outside_panel, LV_ALIGN_TOP_MID, 0, 29);
  lv_obj_add_flag(coffee_making_outside_panel, LV_OBJ_FLAG_CLICKABLE);

  //   lv_obj_t* img = lv_image_create(sliding_inside_panel);
  //   lv_image_set_src(img, icon_path);
  //   lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
  //   // img居中
  //   lv_obj_align(img, LV_ALIGN_CENTER, 0, -22);

  //   lv_obj_t* sliding_inside_text = lv_label_create(sliding_inside_panel);
  //   lv_label_set_text(sliding_inside_text, “icon_text);
  //   lv_obj_set_style_text_color(sliding_inside_text, lv_color_hex(0xFFFFFF),
  //   0); lv_obj_set_style_text_font(sliding_inside_text,
  //   &HarmonyOS_Sans_SC_Regular_26,
  //                              0);
  //   // 居中对齐
  //   lv_obj_align(sliding_inside_text, LV_ALIGN_CENTER, 0, 135);
  //   lv_obj_add_flag(sliding_inside_text,
  //                   LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  // 创建返回按钮并绑定点击事件
  lv_obj_t* back_btn =
      create_back_btn(coffee_making_view, back_btn_click_event, 0);

  // 创建一个“确定”按钮
  coffee_making_sure_btn = lv_btn_create(coffee_making_view);
  lv_obj_add_style(coffee_making_sure_btn, &button_style, 0);
  lv_obj_align(coffee_making_sure_btn, LV_ALIGN_CENTER, 337,
               169);  // 设置按钮位置
  // 添加按钮点击事件回调函数
  lv_obj_add_event_cb(coffee_making_sure_btn, coffee_making_sure_btn_event,
                      LV_EVENT_CLICKED, NULL);

  coffee_making_sure_btn_text = lv_label_create(coffee_making_sure_btn);
  lv_label_set_text(coffee_making_sure_btn_text, "确定");
  lv_obj_set_width(coffee_making_sure_btn_text, 200);
  lv_obj_set_style_text_color(coffee_making_sure_btn_text,
                              lv_color_hex(0xE9BD86), 0);
  lv_obj_set_style_text_align(coffee_making_sure_btn_text, LV_TEXT_ALIGN_CENTER,
                              0);
  lv_obj_align(coffee_making_sure_btn_text, LV_ALIGN_CENTER, 0, 1);

  // 创建一个“取消”按钮
  coffee_making_cancel_btn = lv_btn_create(coffee_making_view);
  lv_obj_add_style(coffee_making_cancel_btn, &button_style, 0);
  lv_obj_align(coffee_making_cancel_btn, LV_ALIGN_CENTER, 0,
               169);  // 设置按钮位置
  // 添加按钮点击事件回调函数
  lv_obj_add_event_cb(coffee_making_cancel_btn, coffee_making_cancel_btn_event,
                      LV_EVENT_CLICKED, NULL);

  coffee_making_cancel_btn_text = lv_label_create(coffee_making_cancel_btn);
  lv_label_set_text(coffee_making_cancel_btn_text, "取消");
  lv_obj_set_width(coffee_making_cancel_btn_text, 200);
  lv_obj_set_style_text_color(coffee_making_cancel_btn_text,
                              lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_align(coffee_making_cancel_btn_text,
                              LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(coffee_making_cancel_btn_text, LV_ALIGN_CENTER, 0, 1);

  return coffee_making_view;
}