#include "7LED.h"

int sled_value = SLED_MIN;
int current_digit = 0;

Pin seventSegmentDisplay[] = {
    { GPIOG, 0 }, // A
    { GPIOG, 1 }, // B
    { GPIOG, 2 }, // C
    { GPIOG, 3 }, // D
    { GPIOG, 4 }, // E
    { GPIOG, 5 }, // F
    { GPIOG, 6 }, // G
};

Pin digits[] = { { GPIOB, 2 }, { GPIOB, 3 }, { GPIOB, 4 }, { GPIOB, 5 } };

int numbers[10][7] = { { ON, ON, ON, ON, ON, ON, OFF },     // 0
    { OFF, ON, ON, OFF, OFF, OFF, OFF }, // 1
    { ON, ON, OFF, ON, ON, OFF, ON },    // 2
    { ON, ON, ON, ON, OFF, OFF, ON },    // 3
    { OFF, ON, ON, OFF, OFF, ON, ON },   // 4
    { ON, OFF, ON, ON, OFF, ON, ON },    // 5
    { ON, OFF, ON, ON, ON, ON, ON },    // 6
    { ON, ON, ON, OFF, OFF, OFF, OFF },  // 7
    { ON, ON, ON, ON, ON, ON, ON },      // 8
    { ON, ON, ON, ON, OFF, ON, ON }      // 9
};

void sled_init() {
	enable_VddIO2();
	activate_clock_for(&RCC->AHB2ENR, GPIOBEN);
	activate_clock_for(&RCC->AHB2ENR, GPIOGEN);

	for (int i = 0; i < 7; i++) {
		GPIO_InitStruct initStruct;
		initStruct.Pin = seventSegmentDisplay[i].pin;
		initStruct.Mode = MODE_OUTPUT;
		initStruct.Pull = PULL_NO;
		initStruct.Speed = OUTPUT_LOWSPEED;
		gpio_init(GPIOG, &initStruct);
	}

	for (int i = 0; i < 4; i++) {
		GPIO_InitStruct initStruct;
		initStruct.Pin = digits[i].pin;
		initStruct.Mode = MODE_OUTPUT;
		initStruct.Pull = PULL_NO;
		initStruct.Speed = OUTPUT_LOWSPEED;
		gpio_init(digits[i].port, &initStruct);
		gpio_write_pin(digits[i].port, digits[i].pin, HIGH);
	}
}

int sled_set(int num)
{
	if(num > SLED_MAX || num < SLED_MIN)
	{
		return -1;
	}

	sled_value = num;

	return 0;
}

void sled_display()
{
	int d[4] = {
			(sled_value / 1000) % 10,
			(sled_value / 100) % 10,
			(sled_value / 10) % 10,
			(sled_value) % 10
	};
	
	for (int k = 0; k < 4; k++) {
		gpio_write_pin(digits[k].port, digits[k].pin, LOW);
	}

	for (int i = 0; i < 7; i++) {
		gpio_write_pin(seventSegmentDisplay[i].port, seventSegmentDisplay[i].pin, numbers[d[current_digit]][i]);
	}

	gpio_write_pin(digits[current_digit].port, digits[current_digit].pin, HIGH);
	current_digit = (current_digit + 1) % 4;
}

int sled_get()
{
	return sled_value;
}


