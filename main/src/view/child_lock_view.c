#include "global_def.h"
#include "lvgl.h"
#include "stdio.h"

LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_26)
LV_FONT_DECLARE(HarmonyOS_Sans_SC_Regular_30)

lv_obj_t* child_lock_view = 0;
lv_obj_t* img_child_lock_round = 0;
lv_obj_t* img_child_lock = 0;
lv_obj_t* child_lock_text = 0;

static void child_lock_unlock_handler(lv_event_t * e);

void child_lock_view_init(void) {
  child_lock_view = lv_obj_create(NULL);
  lv_obj_set_size(child_lock_view, 1280, 480);
  lv_obj_set_style_bg_color(child_lock_view, lv_color_hex(0x000000), 0);

  img_child_lock_round = lv_image_create(child_lock_view);
  lv_image_set_src(
      img_child_lock_round,
      LVGL_IMAGE_PATH("boot_view_images/img_child_lock_round.png"));
  lv_obj_align(img_child_lock_round, LV_ALIGN_CENTER, 0, 0);

  img_child_lock = lv_image_create(child_lock_view);
  lv_image_set_src(img_child_lock,
                   LVGL_IMAGE_PATH("boot_view_images/img_child_lock.png"));
  lv_obj_align(img_child_lock, LV_ALIGN_CENTER, 0, -51);
  // 添加点击事件监听器
  lv_obj_add_event_cb(img_child_lock, child_lock_unlock_handler, LV_EVENT_CLICKED, NULL);
  lv_obj_add_flag(img_child_lock, LV_OBJ_FLAG_CLICKABLE);

  child_lock_text = lv_label_create(child_lock_view);
  lv_label_set_text(child_lock_text, "童锁已开启,\n点击图标可解锁");
  lv_obj_set_style_text_color(child_lock_text, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_text_font(child_lock_text, &HarmonyOS_Sans_SC_Regular_26, 0);
  lv_obj_set_style_text_line_space(child_lock_text, 8, 0);  // 设置行间距为8像素
  lv_obj_set_width(child_lock_text, 182);  // 设置标签宽度
  lv_label_set_long_mode(child_lock_text, LV_LABEL_LONG_WRAP);  // 启用自动换行
  lv_obj_set_style_text_align(child_lock_text, LV_TEXT_ALIGN_CENTER,
                              0);  // 添加文字居中对齐
  lv_obj_align(child_lock_text, LV_ALIGN_CENTER, 0, 48);
}

static void child_lock_unlock_handler(lv_event_t * e) {
    // 处理童锁解锁事件
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_del(obj);    
    // 例如：关闭童锁界面，更新状态等
    printf("童锁已解锁\n");
  }