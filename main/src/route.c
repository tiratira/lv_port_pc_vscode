#include "route.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define DECLEAR_UI_VIEW(name)          \
  extern lv_obj_t* name##_init(void*); \
  register_view(#name, name##_init);

static view_info_t view_info_list[16] = {0};
static int current_view_count = 0;
static char current_view_name[32] = {0};

void init_routes() {
  DECLEAR_UI_VIEW(screen_saver_view)
  DECLEAR_UI_VIEW(main_menu_view)
  DECLEAR_UI_VIEW(boot_view)
  DECLEAR_UI_VIEW(self_check_view)
  DECLEAR_UI_VIEW(child_lock_view)
  DECLEAR_UI_VIEW(lan_sel_view)
  DECLEAR_UI_VIEW(user_label_view)
  DECLEAR_UI_VIEW(coffee_making_view)

  // 添加view就放在下面
  DECLEAR_UI_VIEW(cute_screen_saver_view)
  DECLEAR_UI_VIEW(cute_main_menu_view)
  DECLEAR_UI_VIEW(cute_coffee_config_view)
}

void register_view(const char* view_name, view_init_func init_func) {
  view_info_t view_info = {0};
  view_info.view_name = view_name;
  view_info.init_func = init_func;
  view_info.view = 0;
  view_info_list[current_view_count] = view_info;
  current_view_count++;
}

void dispose_view(const char* view_name) {
  for (int i = 0; i < current_view_count; i++) {
    if (strcmp(view_name, view_info_list[i].view_name) == 0 &&
        view_info_list[i].view != 0) {
      lv_obj_del(view_info_list[i].view);
      view_info_list[i].view = 0;
      return;
    }
  }
}

void init_view(const char* view_name, void* args) {
  for (int i = 0; i < current_view_count; i++) {
    if (strcmp(view_name, view_info_list[i].view_name) == 0) {
      if (view_info_list[i].view == 0) {
        view_info_list[i].view = view_info_list[i].init_func(args);
      }
      return;
    }
  }
}

void navigate_to_view(const char* view_name, void* args) {
  for (int i = 0; i < current_view_count; i++) {
    if (strcmp(view_name, view_info_list[i].view_name) == 0) {
      if (view_info_list[i].view == 0) {
        view_info_list[i].view = view_info_list[i].init_func(args);
      }
      lv_scr_load(view_info_list[i].view);
      dispose_view(current_view_name);
      memset(current_view_name, 0, 32);
      strcpy(current_view_name, view_name);
      return;
    }
  }
  printf("error: view not found\n");
}