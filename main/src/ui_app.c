#include "ui_app.h"
#include <src/display/lv_display.h>
#include "lvgl.h"
#include "ui_style.h"
#include "route.h"

// UI从这里开始
void ui_app_init(void) {
  ui_style_init();
  init_routes();

  navigate_to_view("lan_sel_view");
}