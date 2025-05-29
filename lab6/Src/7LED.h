#include "gpiodriver.h"
#define ON 1
#define OFF 0

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

void display_seven_segment(int num)
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