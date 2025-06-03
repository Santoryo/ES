#pragma once
#include "gpiodriver.h"

Pin RGBPin[] = {
		{GPIOD, 1<<13}, //RED
		{GPIOB, 1<<8}, // GREEN
		{GPIOD, 1<<12} // BLUE
};

Pin LEDPin[] = {
		{GPIOC, 1<<6}, // LED0
		{GPIOC, 1<<7}, // LED1
		{GPIOC, 1<<8}, // LED2
		{GPIOC, 1<<9}, // LED3
		{GPIOE, 1<<4}, // LED4
		{GPIOD, 1<<3}, // LED5
		{GPIOE, 1<<5}, // LED6
		{GPIOE, 1<<6}  // LED7
};

// LED 0-7
// RGB 8-10

void LED_init()
{
	activate_clock_for(&RCC->AHB2ENR, GPIOEEN);
	activate_clock_for(&RCC->AHB2ENR, GPIOCEN);
	activate_clock_for(&RCC->AHB2ENR, GPIODEN);
	activate_clock_for(&RCC->AHB2ENR, GPIOBEN);

	//   for(int i = 0; i < 8; i++)
	//   {
	// 	  GPIO_InitStruct initStruct;
	// 	  HAL_GPIO_WritePin(pins[i].port, pins[i].pin, GPIO_PIN_RESET);
	// 	  GPIO_InitStruct.Pin = pins[i].pin;
	// 	  GPIO_InitStruct.Mode = MODE_OUTPUT;
	// 	  GPIO_InitStruct.Pull = PULL_NO;
	// 	  GPIO_InitStruct.Speed = OUTPUT_LOWSPEED;
	// 	  gpio_init(LEDPin[i].port, &initStruct);
	//   }

	//   /* CONFIGURE RGB */
	//   for(int i = 0; i < 3; i++)
	//   {
	// 	  GPIO_InitStruct initStruct;
	// 	  GPIO_InitStruct.Pin = RGBPin[i].pin;
	// 	  GPIO_InitStruct.Mode = MODE_OUTPUT;
	// 	  GPIO_InitStruct.Pull = PULL_NO;
	// 	  GPIO_InitStruct.Speed = OUTPUT_LOWSPEED;
	// 	  gpio_init(RGBPin[i].port, &initStruct);
	//   }
}

int LED_set(int id, int state)
{
	if(id >= 0 && id <= 7)
	{
		gpio_write_pin(LEDPin[id].port, LEDPin[id].pin, state);
		return 0;
	}
	else if(id >= 8 && id <= 10)
	{
		gpio_write_pin(RGBPin[id].port, RGBPin[id].pin, state);
		return 0;
	}
	return -1;
}

int LED_get(int id)
{
	if(id >= 0 && id <= 7)
	{
		return gpio_read_pin(LEDPin[id].port, LEDPin[id].pin);
	}
	else if(id >= 8 && id <= 10)
	{
		return gpio_write_pin(RGBPin[id].port, RGBPin[id].pin);
	}
	return -1;
}


