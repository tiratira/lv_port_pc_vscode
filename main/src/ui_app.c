#include "ui_app.h"
#include <src/display/lv_display.h>
#include "lvgl.h"
#include "ui_style.h"

extern lv_obj_t* screen_saver_view;
extern void screen_saver_view_init(void);

extern lv_obj_t* main_menu_view;
extern void main_menu_view_init(void);

extern lv_obj_t* boot_view;
extern void boot_view_init(void);

extern lv_obj_t* self_check_view;
extern void self_check_view_init(void);

extern lv_obj_t* child_lock_view;
extern void child_lock_view_init(void);

extern lv_obj_t* lan_sel_view;
extern void lan_sel_view_init(void);

extern lv_obj_t* main_menu_view;
extern void main_menu_view_init(void);

// UI从这里开始
void ui_app_init(void) {
  ui_style_init();
  // boot_view_init();
  // lv_screen_load(boot_view);
  // self_check_view_init();
  // lv_screen_load(self_check_view);
  // screen_saver_view_init();
  // lv_screen_load(screen_saver_view);
  // child_lock_view_init();
  // lv_screen_load(child_lock_view);
  // lan_sel_view_init();
  // lv_screen_load(lan_sel_view);
  main_menu_view_init();
  lv_screen_load(main_menu_view);
}