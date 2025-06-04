#include "LED.h"
#include "lpuart.h"

Pin ledsArray[] = {
        {GPIOC, 6}, // LED 0
        {GPIOC, 7}, // LED 1
        {GPIOC, 8}, // LED 2
        {GPIOC, 9}, // LED 3
        {GPIOE, 4}, // LED 4
        {GPIOD, 3}, // LED 5
        {GPIOE, 5}, // LED 6
        {GPIOE, 6}, // LED 7
        {GPIOD, 13},// RED LED
        {GPIOB, 8}, // GREEN LED
        {GPIOD, 12} // BLUE LED
};

char ledsId[] = {'0', '1', '2', '3', '4', '5', '6', '7', 'r', 'g', 'b'};

int blink_count = 0;
char current_led_id = '0';

void LED_init()
{
	activate_clock_for(&RCC->AHB2ENR, GPIOEEN);
	activate_clock_for(&RCC->AHB2ENR, GPIOCEN);
	activate_clock_for(&RCC->AHB2ENR, GPIODEN);
	activate_clock_for(&RCC->AHB2ENR, GPIOBEN);

    for(int i = 0; i < 11; i++)
    {
        GPIO_InitStruct initStruct;
        initStruct.Pin = ledsArray[i].pin;
        initStruct.Mode = MODE_OUTPUT;
        initStruct.Pull = PULL_NO;
        initStruct.Speed = OUTPUT_LOWSPEED;
        gpio_init(ledsArray[i].port, &initStruct);
        gpio_write_pin(ledsArray[i].port, ledsArray[i].pin, LOW);
    }
}

int LED_set(int id, int state)
{
	for(int i = 0; i < 11; i++)
	{
		if(ledsId[i] == id)
		{
			if(state == ON)
			{
				gpio_write_pin(ledsArray[i].port, ledsArray[i].pin, HIGH);
			}
			else if(state == OFF)
			{
				gpio_write_pin(ledsArray[i].port, ledsArray[i].pin, LOW);
			}
			else
			{
				return -1;
			}
			return 0; // Success
		}
	}
	return -1;
}

int LED_get(char id)
{
	for(int i = 0; i < 11; i++)
	{
		if(ledsId[i] == id)
		{
			return gpio_read_pin(ledsArray[i].port, ledsArray[i].pin);
		}
	}
	return -1;
}

int LED_set_blink(char id, int count)
{
    for(int i = 0; i < 11; i++)
    {
        if(ledsId[i] == id)
        {
            current_led_id = id;
            blink_count = count * 2; // Multiply by 2 for on/off cycles
            return 0;
        }
    }
    return -1;
}

void LED_blink()
{
    int status = LED_get(current_led_id);
    if (status == -1)
    {
        LPUART_SendString((unsigned char *)"Invalid LED ID. Use 0-7 or 'R', 'G', 'B'.\r\n");
        return;
    }

    if(blink_count == 0)
    {
        return;
    }

    LED_set(current_led_id, !status);
    blink_count--;
}


