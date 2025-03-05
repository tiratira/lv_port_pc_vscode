#pragma once

#include "lvgl.h"

/**
 * route.h 这个页面专门负责页面跳转逻辑
 */

typedef lv_obj_t* (*view_init_func)(void);

typedef struct ViewInfo {
  const char* view_name;     // 页面名称
  lv_obj_t* view;            // 页面对象
  view_init_func init_func;  // 页面初始化函数
} view_info_t;

void init_routes(void);

void register_view(const char* view_name, view_init_func init_func);

void init_view(const char* view_name);

void dispose_view(const char* view_name);

/**
 * @brief 跳转到某一页
 *
 * @param view 需要跳转页面
 */
void navigate_to_view(const char* view_name);