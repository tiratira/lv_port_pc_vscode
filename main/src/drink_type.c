#include "drink_type.h"

static drink_item_data_t internal_drink_item_data[] = {
    {LVGL_IMAGE_PATH("cute_main_menu/美式咖啡.png"),
     LVGL_IMAGE_PATH("cute_main_menu/large/美式咖啡.png"), "美式咖啡",
     "Americano", HOT_DRINK},
    {LVGL_IMAGE_PATH("cute_main_menu/拿铁咖啡.png"),
     LVGL_IMAGE_PATH("cute_main_menu/large/拿铁咖啡.png"), "拿铁咖啡",
     "Coffee Latte", HOT_DRINK},
    {LVGL_IMAGE_PATH("cute_main_menu/雪顶咖啡.png"),
     LVGL_IMAGE_PATH("cute_main_menu/large/雪顶咖啡.png"), "雪顶咖啡",
     "Cream Top Coffee", HOT_DRINK},
    {LVGL_IMAGE_PATH("cute_main_menu/雪顶美式.png"),
     LVGL_IMAGE_PATH("cute_main_menu/large/雪顶美式.png"), "雪顶美式",
     "Cream Top Americano", HOT_DRINK},
    {LVGL_IMAGE_PATH("cute_main_menu/卡布奇诺.png"),
     LVGL_IMAGE_PATH("cute_main_menu/large/卡布奇诺.png"), "卡布奇诺",
     "Cappuccino", HOT_DRINK},
    {LVGL_IMAGE_PATH("cute_main_menu/玛奇朵.png"),
     LVGL_IMAGE_PATH("cute_main_menu/large/玛奇朵.png"), "玛奇朵", "Machiato",
     HOT_DRINK}};

drink_item_data_t* drink_item_data = internal_drink_item_data;

size_t drink_count() {
  return sizeof(internal_drink_item_data) / sizeof(drink_item_data[0]);
}