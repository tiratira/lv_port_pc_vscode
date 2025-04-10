#include "ui_app.h"
#include "ui_style.h"
#include "route.h"

// UI从这里开始
void ui_app_init(void) {
  ui_style_init();
  init_routes();

  // 开启第一个页面
  navigate_to_view("cute_main_menu_view", NULL);
}