#include "common_widget.h"
#include "global_def.h"

lv_obj_t* create_back_btn(lv_obj_t* parent, lv_event_cb_t event_cb, void* user_data){
    lv_obj_t* back_btn = lv_btn_create(parent);
    lv_obj_set_size(back_btn, 80, 80);
    lv_obj_set_style_bg_color(back_btn, lv_color_hex(0x000000), 0);
    lv_obj_set_style_bg_opa(back_btn, LV_OPA_0, 0);
    lv_obj_set_style_border_width(back_btn, 0, 0);
    lv_obj_set_style_border_opa(back_btn, LV_OPA_0, 0);
    lv_obj_set_style_shadow_width(back_btn, 0, 0);
    lv_obj_set_style_radius(back_btn, 0, 0);
    lv_obj_align(back_btn, LV_ALIGN_TOP_LEFT, 21, 14);
    lv_obj_set_scrollbar_mode(back_btn, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(back_btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(back_btn, event_cb, LV_EVENT_CLICKED, user_data);

    lv_obj_t* back_btn_img = lv_img_create(back_btn);
    lv_img_set_src(back_btn_img, LVGL_IMAGE_PATH("general_images/img_back_btn.png"));
    lv_obj_center(back_btn_img);
    lv_obj_add_flag(back_btn_img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_EVENT_BUBBLE);

    return back_btn;
    
}
