#include "ui_app.h"
#include <src/display/lv_display.h>
#include "lvgl.h"

extern lv_obj_t* screen_saver;
extern void screen_saver_init(void);

void ui_app_init(void) {
  screen_saver_init();
  lv_screen_load(screen_saver);
}