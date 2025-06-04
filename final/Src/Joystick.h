#pragma once
#include "gpiodriver.h"

typedef struct {
	int arrayId;
	char id;
} JoystickButton;

void joystick_init();
int joystick_read(char button);

