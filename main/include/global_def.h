#ifndef LVGL_STORAGE_PATH
#define LVGL_STORAGE_PATH "D:/Projects/lv_port_pc_vscode/main/assets"
#endif

#define LVGL_DIR LVGL_STORAGE_PATH "/"
#define FILE_LIST_PATH LVGL_STORAGE_PATH "/video/"

#define CONN(x, y) x #y
#define LVGL_PATH(y) CONN(LVGL_DIR, y)
#define LVGL_FILE_LIST_PATH(y) CONN(FILE_LIST_PATH, y)
#define LVGL_PATH_ORI(y) CONN(LVGL_STORAGE_PATH "/", y)
#define LVGL_FONT_PATH(y) \
  CONN(LVGL_STORAGE_PATH  \
       "/"                \
       "font/",           \
       y)
#define LVGL_IMAGE_PATH(y) CONN(LVGL_DIR "image/", y)
#define LVGL_VIDEO_PATH(y) \
  CONN(LVGL_STORAGE_PATH   \
       "/"                 \
       "video/",           \
       y)