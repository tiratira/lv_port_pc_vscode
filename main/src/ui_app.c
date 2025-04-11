#include "ui_app.h"
#include "ui_style.h"
#include "route.h"
#include "drink_type.h"

// UI从这里开始
void ui_app_init(void) {
  ui_style_init();
  init_routes();

  // 开启第一个页面
  navigate_to_view("cute_main_menu_view", NULL);
  // navigate_to_view("cute_make_coffee_view", drink_item_data + 1);
  // navigate_to_view("cute_settings_view", drink_item_data + 1);
  // navigate_to_view("cute_bean_mode_view", drink_item_data + 1);
  // navigate_to_view("cute_powder_detail_view", drink_item_data + 1);
}