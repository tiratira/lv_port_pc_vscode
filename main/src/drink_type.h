#pragma once
#include <stddef.h>
#include <stdint.h>
#include "global_def.h"

typedef enum DrinkType {
  HOT_DRINK,
  COLD_DRINK,
} drink_type_t;

typedef struct DrinkItemData {
  const char* icon_path;
  const char* icon_xl_path;
  const char* title_cn;
  const char* title_en;
  drink_type_t type;
} drink_item_data_t;

drink_item_data_t* drink_item_data;

size_t drink_count();