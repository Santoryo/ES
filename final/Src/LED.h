#pragma once
#include "gpiodriver.h"

#define ON 1
#define OFF 0

void LED_init();
int LED_set(int id, int state);
int LED_get(char id);
void LED_blink();
int LED_set_blink(char id, int count);
