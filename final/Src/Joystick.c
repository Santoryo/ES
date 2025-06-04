#include "Joystick.h"

Pin joystick[] = {
    {GPIOE, 3}, // UP
    {GPIOE, 2}, // DOWN
    {GPIOE, 0}, // RIGHT
    {GPIOE, 1}, // LEFT
    {GPIOE, 15} // CLICK/OK
};

JoystickButton joystick_buttons[] = {
    {0, 'u'}, // UP
    {1, 'd'}, // DOWN
    {2, 'r'}, // RIGHT
    {3, 'l'}, // LEFT
    {4, 'c'},  // CLICK/OK
};


void joystick_init()
{
activate_clock_for(&RCC->AHB2ENR, GPIOEEN);

for(int i = 0; i < 5; i++)
{
    GPIO_InitStruct initStruct;
    initStruct.Pin = joystick[i].pin;
    initStruct.Mode = MODE_INPUT;
    initStruct.Pull = PULL_UP;
    gpio_init(joystick[i].port, &initStruct);
    gpio_write_pin(joystick[i].port, joystick[i].pin, HIGH);
}
}

int joystick_read(char button)
{
    for(int i = 0; i < 5; i++)
    {
        if(joystick_buttons[i].id == button)
        {
            return !gpio_read_pin(joystick[i].port, joystick[i].pin);
        }
    }
    return -1;
}