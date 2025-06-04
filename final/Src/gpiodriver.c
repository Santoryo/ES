#include "gpiodriver.h"

// Activate clock for peripheral (RCC register and bit)
void activate_clock_for(REG32 *reg, int gpio_en_bit)
{
    *reg |= (1 << gpio_en_bit);
}

// Initialize GPIO pin with mode, speed, pull
void gpio_init(GPIO_TypeDef *GPIOx, GPIO_InitStruct *init)
{
    uint32_t pin_pos = init->Pin * 2U;

    GPIOx->MODER &= ~(0b11 << pin_pos);
    GPIOx->MODER |= (init->Mode << pin_pos);

    GPIOx->OSPEEDR &= ~(0b11 << pin_pos);
    GPIOx->OSPEEDR |= (init->Speed << pin_pos);

    GPIOx->PUPDR &= ~(0b11 << pin_pos);
    GPIOx->PUPDR |= (init->Pull << pin_pos);
}

// Write GPIO pin state
void gpio_write_pin(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t state)
{
    if (state == HIGH)
    {
        SET_BIT(GPIOx->BSRR, pin);
    }
    else
    {
        SET_BIT(GPIOx->BRR, pin);
    }
}

// Read GPIO pin state
uint32_t gpio_read_pin(GPIO_TypeDef *GPIOx, uint32_t pin)
{
    return (GPIOx->IDR & (1 << pin)) ? HIGH : LOW;
}

// Enable VddIO2 power supply
void enable_VddIO2()
{
    SET_BIT(PWR->CR2, 9);
}

// Initialize TIM6 timer
void tim6_init(uint16_t prescaler, uint16_t autoreload)
{
    activate_clock_for(&RCC->APB1ENR1, 4);  // Enable TIM6 clock (bit 4 of APB1ENR1)
    TIM6->PSC = prescaler;
    TIM6->ARR = autoreload;
    TIM6->DIER |= (1 << 0);  // Enable update interrupt
    TIM6->CR1 |= (1 << 0);  // Enable TIM6 counter

    *(NVIC_ISER1) |= (1 << 22);  // Enable TIM6 interrupt in NVIC (IRQ 54)
}

// Simple delay loop
void delay(uint32_t val)
{
    for (uint32_t i = 0; i <= val * 100; i++)
    {
    }
}
