#include "global_def.h"
#include "lvgl.h"
#include "ui_style.h"
#include "stdio.h"
#include "route.h"
#include "drink_type.h"

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_26)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_30)

extern lv_font_t* lanapixel_sm;
extern lv_font_t* lanapixel_md;
extern lv_font_t* lanapixel_xl;

lv_obj_t* cute_main_menu_view = 0;
static lv_obj_t* img_main_menu_bg = 0;
static lv_obj_t* img_warning_icon = 0;
static lv_obj_t* img_wifi_icon = 0;
static lv_obj_t* main_menu_hot_water_text = 0;
static lv_obj_t* main_menu_cold_water_text = 0;
static lv_obj_t* sliding_panel = 0;
static bool current_is_hot = true;  // 当前显示状态是否为热饮

static lv_style_t hot_cold_btn_style;
static lv_style_t hot_cold_btn_style_selected;
static lv_obj_t* hot_btn = 0;
static lv_obj_t* cold_btn = 0;

static lv_timer_t* timer = 0;
static int32_t count = 5;

// 声明外部变量
extern lv_obj_t* screen_saver_view;
extern void screen_saver_view_init(void);
extern lv_obj_t* user_label_view;
extern lv_obj_t* child_lock_view;

static lv_obj_t* hot_drink_options_method(const char* icon_path,
                                          const char* icon_text,
                                          const char* icon_text2, int index);
static lv_obj_t* cold_drink_options_method(const char* icon_path,
                                           const char* icon_text, int index);

extern drink_item_data_t drink_item_data[];

static const char* main_menu_img_list[] = {
    LVGL_IMAGE_PATH("cute_main_menu/icon_lock.png"),
    LVGL_IMAGE_PATH("cute_main_menu/icon_fav.png"),
    LVGL_IMAGE_PATH("cute_main_menu/icon_user.png"),
    LVGL_IMAGE_PATH("cute_main_menu/icon_more.png"),
    LVGL_IMAGE_PATH("cute_main_menu/icon_next.png"),
};

static void animate_timer_cb(lv_timer_t* timer) {
  count -= 1;
  if (count <= 0) {
    lv_timer_delete(timer);
    navigate_to_view("cute_screen_saver_view", 0);
  }
}

static void global_click_cb(lv_event_t* e) { count = 5; }

// 新增创建函数（放在原有函数下方）
static void create_hot_drinks() {
  for (int i = 0; i < drink_count(); i++) {
    if (drink_item_data[i].type == HOT_DRINK) {
      hot_drink_options_method(drink_item_data[i].icon_path,
                               drink_item_data[i].title_cn,
                               drink_item_data[i].title_en, i);
    }
  }
}

static void create_cold_drinks() {
  for (int i = 0; i < drink_count(); i++) {
    if (drink_item_data[i].type == COLD_DRINK) {
      cold_drink_options_method(drink_item_data[i].icon_path,
                                drink_item_data[i].title_cn, i);
    }
  }
}

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
  if (obj == main_menu_hot_water_text) {
    // 删除冷饮项并创建热饮项
    if (!current_is_hot) {
      // 删除所有子对象
      lv_obj_clean(sliding_panel);
      create_hot_drinks();
      current_is_hot = true;
    }
  } else if (obj == main_menu_cold_water_text) {
    // 删除热饮项并创建冷饮项
    if (current_is_hot) {
      // 删除所有子对象
      lv_obj_clean(sliding_panel);
      create_cold_drinks();
      current_is_hot = false;
    }
  }

  // 重置滚动位置
  lv_obj_scroll_to_x(sliding_panel, 0, LV_ANIM_OFF);
}

// 定义返回按钮的点击事件回调函数
static void func_label_click_event(lv_event_t* e) {
  lv_obj_t* label_obj = lv_event_get_target(e);
  // 获取用户数据
  int index = (int)lv_event_get_user_data(e);
  switch (index) {
    case 0:
      navigate_to_view("child_lock_view", NULL);
      break;
    case 1:
      navigate_to_view("user_label_view", NULL);
      break;
    case 2:
      navigate_to_view("coffee_making_view", NULL);
      break;
    default:
      break;
  }
}

static void coffee_select_event(lv_event_t* e) {
  navigate_to_view("cute_coffee_config_view", lv_event_get_user_data(e));
}

static void settings_click_event(lv_event_t* e) {
  navigate_to_view("cute_settings_view", NULL);
}

// 制作通用的图片加文字这种表达形式的方法
static void build_label_method(const char* img_path, const char* text,
                               int32_t x, int32_t y, int index) {
  // 创建一个外面板对象
  // lv_obj_t* outside_panel = lv_obj_create(cute_main_menu_view);
  // lv_obj_set_size(outside_panel, 210, 64);
  // lv_obj_set_pos(outside_panel, x, y);
  // lv_obj_set_style_bg_color(outside_panel, lv_color_hex(0x000000), 0);
  // lv_obj_set_style_bg_opa(outside_panel, LV_OPA_0, 0);
  // lv_obj_set_style_radius(outside_panel, 0, 0);        //
  // 设置倒角的半径为0像素 lv_obj_set_style_border_width(outside_panel, 0, 0);
  // // 设置边框的宽度为0像素 lv_obj_set_scrollbar_mode(outside_panel,
  //                           LV_SCROLLBAR_MODE_OFF);  // 取消滑动效果
  // lv_obj_add_flag(outside_panel,
  //                 LV_OBJ_FLAG_CLICKABLE);  // 确保能点击到，不然点不到文字()
  // lv_obj_add_event_cb(outside_panel, func_label_click_event,
  // LV_EVENT_CLICKED,
  //                     (void*)index);  // 注册点击事件回调函数
  // // 创建一个内小面板对象
  // lv_obj_t* inside_panel = lv_obj_create(outside_panel);
  // lv_obj_set_flex_flow(inside_panel, LV_FLEX_FLOW_ROW);
  // lv_obj_set_flex_align(inside_panel, LV_FLEX_ALIGN_CENTER,
  //                       LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  // lv_obj_set_size(inside_panel, 180, 64);
  // lv_obj_set_align(inside_panel, LV_ALIGN_CENTER);  // 居中对齐()
  // lv_obj_set_style_bg_color(inside_panel, lv_color_hex(0x000000), 0);
  // lv_obj_set_style_bg_opa(inside_panel, LV_OPA_0, 0);
  // lv_obj_set_style_radius(inside_panel, 0, 0);        //
  // 设置倒角的半径为0像素 lv_obj_set_style_border_width(inside_panel, 0, 0); //
  // 设置边框的宽度为0像素 lv_obj_set_scrollbar_mode(inside_panel,
  //                           LV_SCROLLBAR_MODE_OFF);  // 取消滑动效果
  // lv_obj_add_flag(inside_panel,
  //                 LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t* img = lv_image_create(cute_main_menu_view);
  lv_image_set_src(img, img_path);
  lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
  lv_obj_set_pos(img, x, y);
  if (index == 3) {
    lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(img, settings_click_event, LV_EVENT_CLICKED, 0);
  }

  // // 隔开icon和文字的空隙
  // lv_obj_t* mini_panel = lv_obj_create(inside_panel);
  // lv_obj_set_size(mini_panel, 10, 64);
  // lv_obj_set_style_bg_color(mini_panel, lv_color_hex(0x000000), 0);
  // lv_obj_set_style_bg_opa(mini_panel, LV_OPA_0, 0);
  // lv_obj_set_style_radius(mini_panel, 0, 0);        // 设置倒角的半径为0像素
  // lv_obj_set_style_border_width(mini_panel, 0, 0);  // 设置边框的宽度为0像素
  // lv_obj_set_scrollbar_mode(mini_panel, LV_SCROLLBAR_MODE_OFF);  //
  // 取消滑动效果 lv_obj_add_flag(mini_panel, LV_OBJ_FLAG_CLICKABLE |
  // LV_OBJ_FLAG_EVENT_BUBBLE);

  // lv_obj_t* label = lv_label_create(inside_panel);
  // lv_label_set_text(label, text);
  // lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);
  // lv_obj_set_style_text_font(label, &HarmonyOS_Sans_SC_Regular_26, 0);
  // lv_obj_add_flag(label, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
}

static lv_obj_t* hot_drink_options_method(const char* icon_path,
                                          const char* icon_text,
                                          const char* icon_text2, int index) {
  // 创建一个内小面板对象
  lv_obj_t* sliding_inside_panel = lv_obj_create(sliding_panel);
  // 禁用 sliding_inside_panel 的滚动
  lv_obj_set_scroll_dir(sliding_inside_panel, LV_DIR_NONE);
  lv_obj_set_size(sliding_inside_panel, 134, 264);
  lv_obj_set_style_bg_color(sliding_inside_panel, lv_color_hex(0x000000), 0);
  lv_obj_set_style_pad_all(sliding_inside_panel, 0, 0);
  lv_obj_set_style_margin_all(sliding_inside_panel, 21, 0);
  lv_obj_set_style_bg_opa(sliding_inside_panel, LV_OPA_0, 0);
  lv_obj_set_style_radius(sliding_inside_panel, 0, 0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(sliding_inside_panel, 0,
                                0);  // 设置边框的宽度为0像素
  lv_obj_add_flag(sliding_inside_panel,
                  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t* bg = lv_obj_create(sliding_inside_panel);
  lv_obj_set_size(bg, 134, 181);
  lv_obj_set_pos(bg, 0, 60);
  lv_obj_set_style_bg_color(bg, lv_color_hex(0xB5B5D1), 0);
  lv_obj_set_style_radius(bg, 30, 0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(bg, 0,
                                0);  // 设置边框的宽度为0像素

  lv_obj_t* img = lv_image_create(sliding_inside_panel);
  lv_image_set_src(img, icon_path);
  lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
  // img居中
  // lv_obj_align(img, LV_ALIGN_TOP_LEFT, 0, 0);
  lv_obj_set_pos(img, 0, 0);

  lv_obj_t* add_btn = lv_image_create(sliding_inside_panel);
  lv_image_set_src(add_btn, LVGL_IMAGE_PATH("cute_main_menu/add_btn.png"));
  lv_obj_add_flag(add_btn, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);
  lv_obj_set_pos(add_btn, 92, 221);

  lv_obj_t* sliding_inside_text = lv_label_create(sliding_inside_panel);
  lv_label_set_text(sliding_inside_text, icon_text);
  lv_obj_set_style_text_color(sliding_inside_text, lv_color_black(), 0);
  lv_obj_set_style_text_font(sliding_inside_text, lanapixel_md, 0);
  // 居中对齐
  lv_obj_align(sliding_inside_text, LV_ALIGN_TOP_LEFT, 12, 160);
  lv_obj_add_flag(sliding_inside_text,
                  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_t* sliding_inside_text2 = lv_label_create(sliding_inside_panel);
  lv_label_set_text(sliding_inside_text2, icon_text2);
  lv_obj_set_size(sliding_inside_text2, 114, 100);
  lv_label_set_long_mode(sliding_inside_text2, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_color(sliding_inside_text2, lv_color_hex(0x6E6E6E), 0);
  lv_obj_set_style_text_font(sliding_inside_text2, lanapixel_sm, 0);
  lv_obj_align(sliding_inside_text2, LV_ALIGN_TOP_LEFT, 12, 190);
  lv_obj_add_flag(sliding_inside_text2,
                  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

  lv_obj_add_event_cb(sliding_inside_panel, coffee_select_event,
                      LV_EVENT_CLICKED, (void*)(drink_item_data + index));

  return sliding_inside_panel;
}

static lv_obj_t* cold_drink_options_method(const char* icon_path,
                                           const char* icon_text, int index) {
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

  return sliding_inside_panel;
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
    lv_obj_scroll_to_x(panel, scroll_end_x - panel_width + 70, LV_ANIM_ON);
  }
}

lv_obj_t* cute_main_menu_view_init(void) {
  count = 5;
  cute_main_menu_view = lv_obj_create(NULL);
  lv_obj_set_size(cute_main_menu_view, 1280, 480);
  lv_obj_set_style_bg_color(cute_main_menu_view, lv_color_hex(0x000000), 0);
  // 取消内边距
  lv_obj_set_style_pad_all(cute_main_menu_view, 0, 0);
  // 禁用 main_menu_view 的滚动
  lv_obj_set_scroll_dir(cute_main_menu_view, LV_DIR_NONE);

  img_main_menu_bg = lv_image_create(cute_main_menu_view);
  lv_image_set_src(img_main_menu_bg, LVGL_IMAGE_PATH("cute_main_menu/bg.png"));
  lv_obj_center(img_main_menu_bg);

  // 创建一个滑动外面板对象
  sliding_panel = lv_obj_create(cute_main_menu_view);
  lv_obj_set_size(sliding_panel, 1024, 264);
  lv_obj_set_flex_flow(sliding_panel, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(sliding_panel, LV_FLEX_ALIGN_START,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  // 设置子元素之间的间隔为 20px
  lv_obj_set_style_pad_column(sliding_panel, 0, 0);
  lv_obj_set_pos(sliding_panel, 0, 180);
  lv_obj_set_style_bg_color(sliding_panel, lv_color_hex(0x000000), 0);
  lv_obj_set_style_bg_opa(sliding_panel, LV_OPA_0, 0);
  lv_obj_set_style_radius(sliding_panel, 0, 0);  // 设置倒角的半径为0像素
  lv_obj_set_style_border_width(sliding_panel, 0, 0);  // 设置边框的宽度为0像素
  lv_obj_set_scrollbar_mode(sliding_panel,
                            LV_SCROLLBAR_MODE_OFF);  // 取消滑动效果
  // 设置左边距为 25px
  lv_obj_set_style_pad_left(sliding_panel, 71, 0);
  // 设置右边距为 25px
  lv_obj_set_style_pad_right(sliding_panel, 71, 0);
  // 设置上边距为 0px
  lv_obj_set_style_pad_top(sliding_panel, 0, 0);
  // 设置下边距为 0px
  lv_obj_set_style_pad_bottom(sliding_panel, 0, 0);
  // 添加滑动结束事件回调
  lv_obj_add_event_cb(sliding_panel, sliding_panel_scroll_end_event,
                      LV_EVENT_SCROLL_END, NULL);
  lv_obj_add_flag(sliding_panel,
                  LV_OBJ_FLAG_CLICKABLE);  // 确保能点击到，不然点不到文字()

  create_hot_drinks();

  lv_style_init(&hot_cold_btn_style);
  lv_style_set_radius(&hot_cold_btn_style, 16);
  lv_style_set_bg_opa(&hot_cold_btn_style, LV_OPA_100);
  lv_style_set_bg_color(&hot_cold_btn_style, lv_color_hex(0xd9d9d9));
  lv_style_set_text_color(&hot_cold_btn_style, lv_color_black());
  lv_style_set_border_width(&hot_cold_btn_style, 0);
  lv_style_set_pad_all(&hot_cold_btn_style, 0);
  lv_style_set_size(&hot_cold_btn_style, 43, 32);
  lv_style_set_text_font(&hot_cold_btn_style, lanapixel_md);

  lv_style_init(&hot_cold_btn_style_selected);
  lv_style_set_radius(&hot_cold_btn_style_selected, 16);
  lv_style_set_bg_opa(&hot_cold_btn_style_selected, LV_OPA_100);
  lv_style_set_bg_color(&hot_cold_btn_style_selected, lv_color_hex(0x9F73B3));
  lv_style_set_text_color(&hot_cold_btn_style_selected, lv_color_black());
  lv_style_set_border_width(&hot_cold_btn_style_selected, 0);
  lv_style_set_pad_all(&hot_cold_btn_style_selected, 0);
  lv_style_set_size(&hot_cold_btn_style_selected, 43, 32);
  lv_style_set_text_font(&hot_cold_btn_style_selected, lanapixel_md);

  hot_btn = lv_button_create(cute_main_menu_view);
  lv_obj_remove_style_all(hot_btn);
  lv_obj_add_style(hot_btn, &hot_cold_btn_style_selected, 0);
  lv_obj_set_pos(hot_btn, 60, 137);
  lv_obj_set_scrollbar_mode(hot_btn, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_scroll_dir(hot_btn, LV_DIR_NONE);
  lv_obj_t* hot_label = lv_label_create(hot_btn);
  lv_label_set_text(hot_label, "热");
  lv_obj_center(hot_label);

  cold_btn = lv_button_create(cute_main_menu_view);
  lv_obj_remove_style_all(cold_btn);
  lv_obj_add_style(cold_btn, &hot_cold_btn_style, 0);
  lv_obj_set_pos(cold_btn, 134, 137);
  lv_obj_set_scrollbar_mode(cold_btn, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_scroll_dir(cold_btn, LV_DIR_NONE);
  lv_obj_t* cold_label = lv_label_create(cold_btn);
  lv_label_set_text(cold_label, "冷");
  lv_obj_center(cold_label);

  lv_obj_t* welcome_label_1 = lv_label_create(cute_main_menu_view);
  lv_label_set_text(welcome_label_1, "早上好！来杯咖啡开启活力满满的一天！");
  lv_obj_set_pos(welcome_label_1, 52, 45);
  lv_obj_set_style_text_color(welcome_label_1, lv_color_black(), 0);
  lv_obj_set_style_text_font(welcome_label_1, lanapixel_md, 0);

  lv_obj_t* welcome_label_2 = lv_label_create(cute_main_menu_view);
  lv_label_set_text(welcome_label_2, "今天想喝点什么呢？");
  lv_obj_set_pos(welcome_label_2, 52, 80);
  lv_obj_set_style_text_color(welcome_label_2, lv_color_hex(0x9F73B3), 0);
  lv_obj_set_style_text_font(welcome_label_2, lanapixel_sm, 0);

  // main_menu_hot_water_text = lv_label_create(cute_main_menu_view);
  // lv_label_set_text(main_menu_hot_water_text, "热饮");
  // lv_obj_add_flag(main_menu_hot_water_text,
  //                 LV_OBJ_FLAG_CLICKABLE);  // 确保能点击到，不然点不到文字
  // lv_obj_set_style_text_color(main_menu_hot_water_text,
  // lv_color_hex(0xE9BD85),
  //                             0);  // 设置标签宽度
  // lv_obj_set_style_text_font(main_menu_hot_water_text,
  //                            &HarmonyOS_Sans_SC_Regular_26, 0);  //
  //                            设置标签宽度
  // lv_obj_set_width(main_menu_hot_water_text, 200);               //
  // 设置标签宽度 lv_obj_set_height(main_menu_hot_water_text, 78); //
  // 设置标签高度 lv_obj_set_style_text_align(main_menu_hot_water_text,
  // LV_TEXT_ALIGN_CENTER,
  //                             0);  // 添加文字居中对齐
  // lv_obj_set_style_pad_top(
  //     main_menu_hot_water_text,
  //     (78 - lv_font_get_line_height(&HarmonyOS_Sans_SC_Regular_26)) / 2,
  //     0);  // 添加顶部内边距实现垂直居中
  // lv_obj_align(main_menu_hot_water_text, LV_ALIGN_CENTER, -98, -188);
  // lv_obj_add_event_cb(main_menu_hot_water_text, h_or_c_text_click_event,
  //                     LV_EVENT_CLICKED, NULL);

  // main_menu_cold_water_text = lv_label_create(cute_main_menu_view);
  // lv_label_set_text(main_menu_cold_water_text, "冷饮");
  // lv_obj_add_flag(main_menu_cold_water_text,
  //                 LV_OBJ_FLAG_CLICKABLE);  // 确保能点击到，不然点不到文字
  // lv_obj_set_style_text_color(main_menu_cold_water_text,
  // lv_color_hex(0xFFFFFF),
  //                             0);
  // lv_obj_set_style_text_font(main_menu_cold_water_text,
  //                            &HarmonyOS_Sans_SC_Regular_26, 0);
  // lv_obj_set_width(main_menu_cold_water_text, 200);  // 设置标签宽度
  // lv_obj_set_height(main_menu_cold_water_text, 78);  // 设置标签高度
  // lv_obj_set_style_text_align(main_menu_cold_water_text,
  // LV_TEXT_ALIGN_CENTER,
  //                             0);  // 添加文字居中对齐
  // lv_obj_set_style_pad_top(
  //     main_menu_cold_water_text,
  //     (78 - lv_font_get_line_height(&HarmonyOS_Sans_SC_Regular_26)) / 2,
  //     0);  // 添加顶部内边距实现垂直居中
  // lv_obj_align(main_menu_cold_water_text, LV_ALIGN_CENTER, 98, -188);
  // lv_obj_add_event_cb(main_menu_cold_water_text, h_or_c_text_click_event,
  //                     LV_EVENT_CLICKED, NULL);

  // img_warning_icon = lv_image_create(cute_main_menu_view);
  // lv_image_set_src(img_warning_icon,
  //                  LVGL_IMAGE_PATH("main_menu_images/img_warning_icon.png"));
  // // build_label_method(const char *img_path, const char *text, int x, int y)
  // lv_obj_align(img_warning_icon, LV_ALIGN_CENTER, 502, -201);
  // img_wifi_icon = lv_image_create(cute_main_menu_view);
  // lv_image_set_src(img_wifi_icon,
  //                  LVGL_IMAGE_PATH("main_menu_images/img_wifi_icon.png"));
  // lv_obj_align(img_wifi_icon, LV_ALIGN_CENTER, 571, -201);

  build_label_method(main_menu_img_list[0], "锁屏", 159, 523, 0);
  build_label_method(main_menu_img_list[1], "用户", 318, 523, 1);
  build_label_method(main_menu_img_list[2], "设置", 482, 523, 2);
  build_label_method(main_menu_img_list[3], "收藏", 643, 523, 3);
  build_label_method(main_menu_img_list[4], "收藏", 848, 511, 4);
  // build_label_method(main_menu_img_list[4], "快速冲洗", 1045, 406, 4);

  timer = lv_timer_create(animate_timer_cb, 1000, NULL);
  // 注册全局点击事件回调函数
  lv_indev_add_event_cb(lv_indev_active(), global_click_cb, LV_EVENT_ALL, 0);

  return cute_main_menu_view;
}