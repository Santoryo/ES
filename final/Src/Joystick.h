#include "gpiodriver.h"


Pin joystick[] = {
		{GPIOE, 2}, // DOWN
		{GPIOE, 0}, // RIGHT
		{GPIOE, 1}, // LEFT
		{GPIOE, 15} // CLICK/OK
};


enum JoystickButtons {
	DOWN,
	RIGHT,
	LEFT,
	CLICK
};

void joystick_init()
{
	activate_clock_for(&RCC->AHB2ENR, GPIOEEN);

	for(int i = 0; i < 4; i++)
	{
		GPIO_InitStruct initStruct;
		initStruct.Pin = joystick[i].pin;
		initStruct.Mode = MODE_INPUT;
		initStruct.Pull = PULL_UP;
		gpio_init(joystick[i].port, &initStruct);
		gpio_write_pin(joystick[i].port, joystick[i].pin, HIGH);
	}
}

int joystick_read(int button)
{
	return !gpio_read_pin(joystick[button].port, joystick[button].pin);
}





