#pragma once
#include "gpiodriver.h"

#define ON 1
#define OFF 0

#define SLED_MAX 9999
#define SLED_MIN 0

void sled_init();
int sled_set(int num);
void sled_display();
int sled_get();
