
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

#ifndef LVGL_STORAGE_PATH
#ifdef _WIN32
#define LVGL_STORAGE_PATH "E:/Projects/lv_port_pc_vscode/main/assets"
#elif __APPLE__
#define LVGL_STORAGE_PATH \
  "/Users/luyangbin/Projects/lv_port_pc_vscode/main/assets"
#endif
#endif

#define LVGL_DIR LVGL_STORAGE_PATH "/"
#define FILE_LIST_PATH LVGL_STORAGE_PATH "/video/"

#define CONN(x, y) x #y
#define LVGL_PATH(y) CONN(LVGL_DIR, y)
#define LVGL_FILE_LIST_PATH(y) CONN(FILE_LIST_PATH, y)
#define LVGL_PATH_ORI(y) CONN(LVGL_STORAGE_PATH "/", y)
#define LVGL_FONT_PATH(y) LVGL_DIR "font/" y
#define LVGL_IMAGE_PATH(y) LVGL_DIR "image/" y
#define LVGL_VIDEO_PATH(y) \
  CONN(LVGL_STORAGE_PATH   \
       "/"                 \
       "video/",           \
       y)