#include "gpiodriver.h"

Pin seventSegmentDisplay[] = {
		{GPIOG, 0}, // A
		{GPIOG, 1}, // B
		{GPIOG, 2}, // C
		{GPIOG, 3}, // D
		{GPIOG, 4}, // E
		{GPIOG, 5}, // F
		{GPIOG, 6}, // G
};

Pin digits[] = {
		{GPIOB, 2},
		{GPIOB, 3},
		{GPIOB, 4},
		{GPIOB, 5}
};

Pin joystick[] = {
		{GPIOE, 2}, // DOWN
		{GPIOE, 0}, // RIGHT
		{GPIOE, 1}, // LEFT
		{GPIOE, 15} // CLICK/OK
};

#define JOYSTICK_DOWN   joystick[0]
#define JOYSTICK_RIGHT  joystick[1]
#define JOYSTICK_LEFT 	joystick[2]
#define JOYSTICK_CLICK 	joystick[3]
#define DELAY_IN_MS 1000

#define ON 1
#define OFF 0

int numbers[10][7] = {
    {ON, ON, ON, ON, ON, ON, OFF},     // 0
    {OFF, ON, ON, OFF, OFF, OFF, OFF}, // 1
    {ON, ON, OFF, ON, ON, OFF, ON},    // 2
    {ON, ON, ON, ON, OFF, OFF, ON},    // 3
    {OFF, ON, ON, OFF, OFF, ON, ON},   // 4
    {ON, OFF, ON, ON, OFF, ON, ON},    // 5
    {ON, OFF, ON, ON, ON,  ON, ON},    // 6
    {ON, ON, ON, OFF, OFF, OFF, OFF},  // 7
    {ON, ON, ON, ON, ON, ON, ON},      // 8
    {ON, ON, ON, ON, OFF, ON, ON}      // 9
};

#define COUNTER_MAX 9999
#define COUNTER_MIN 0

int counter = COUNTER_MIN;
int cycle = 0;

void init_seven_segment()
{
	enable_VddIO2();
	activate_clock_for(&RCC->AHB2ENR, GPIOBEN);
	activate_clock_for(&RCC->AHB2ENR, GPIOGEN);

	for(int i = 0; i < 7; i++)
	{
		GPIO_InitStruct initStruct;
		initStruct.Pin = seventSegmentDisplay[i].pin;
		initStruct.Mode = MODE_OUTPUT;
		initStruct.Pull = PULL_NO;
		initStruct.Speed = OUTPUT_LOWSPEED;
		gpio_init(GPIOG, &initStruct);
	}

	for(int i = 0; i < 4; i++)
	{
		GPIO_InitStruct initStruct;
		initStruct.Pin = digits[i].pin;
		initStruct.Mode = MODE_OUTPUT;
		initStruct.Pull = PULL_NO;
		initStruct.Speed = OUTPUT_LOWSPEED;
		gpio_init(digits[i].port, &initStruct);
		gpio_write_pin(digits[i].port, digits[i].pin, HIGH);
	}
}


void init_joystick()
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


void setNumber(int num)
{
	int d[4] = {
			(num / 1000) % 10,
			(num / 100) % 10,
			(num / 10) % 10,
			(num / 1) % 10
	};

	for(int j = 0; j < 4; j++)
	{
	  for(int i = 0; i < 7; i++)
	  {
		  gpio_write_pin(seventSegmentDisplay[i].port, seventSegmentDisplay[i].pin, numbers[d[j]][i]);
	  }
	  gpio_write_pin(digits[j].port, digits[j].pin, HIGH);
	  delay(15);
	  gpio_write_pin(digits[j].port, digits[j].pin, LOW);
	}
}


int main(void)
{
	init_seven_segment();
	init_joystick();
	tim6_init(3999, DELAY_IN_MS - 1); // 1s delay
	while(1)
	{
		int clicked = !gpio_read_pin(JOYSTICK_CLICK.port, JOYSTICK_CLICK.pin);
		setNumber(counter);

		 if (READ_BIT(TIM6->SR, 0))
		 {
			CLEAR_BIT(TIM6->SR, 0);
		 	clicked ? counter-- : counter++;

		 	if(counter > COUNTER_MAX)
		 		counter = COUNTER_MIN;
		 	else if(counter < COUNTER_MIN)
		 		counter = COUNTER_MAX;
		 }
	}
}
