#pragma once
#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;    // Offset 0x00: Mode register
    volatile uint32_t OTYPER;   // Offset 0x04: Output type register
    volatile uint32_t OSPEEDR;  // Offset 0x08: Output speed register
    volatile uint32_t PUPDR;    // Offset 0x0C: Pull-up/pull-down register
    volatile uint32_t IDR;      // Offset 0x10: Input data register
    volatile uint32_t ODR;      // Offset 0x14: Output data register
    volatile uint32_t BSRR;     // Offset 0x18: Bit set/reset register
    volatile uint32_t LCKR;     // Offset 0x1C: Configuration lock register
    volatile uint32_t AFRL;     // Offset 0x20: Alternate function low register
    volatile uint32_t AFRH;     // Offset 0x24: Alternate function high register
    volatile uint32_t BRR;      // Offset 0x28: Bit reset register
} GPIO_TypeDef;

// base addresses
#define GPIOA_BASE (0x48000000)
#define GPIOB_BASE (0x48000400)
#define GPIOC_BASE (0x48000800)
#define GPIOD_BASE (0x48000C00)
#define GPIOE_BASE (0x48001000)
#define GPIOF_BASE (0x48001400)
#define GPIOG_BASE (0x48001800)
#define GPIOH_BASE (0x48001C00)

// gpio ports
#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef*) GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef*) GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef*) GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef*) GPIOF_BASE)
#define GPIOG ((GPIO_TypeDef*) GPIOG_BASE)
#define GPIOH ((GPIO_TypeDef*) GPIOH_BASE)

// MODER VALUES
#define MODE_INPUT     0
#define MODE_OUTPUT    1
#define MODE_ALTERNATE 2
#define MODE_ANALOG    3

// OTYPER VALUES
#define TYPE_PP 0
#define TYPE_OD 1

// OSPEEDR VALUES
#define OUTPUT_LOWSPEED 0
#define OUTPUT_MIDSPEED 1
#define OUTPUT_HIGHSPEED 2
#define OUTPUT_VERYHIGHSPEED 3

// PUPDR VALUES
#define PULL_NO 0
#define PULL_UP 1
#define PULL_DOWN 2
#define PULL_RESERVED 3

// BRR VALUES
#define NO_RESET 0
#define RESET 1

#define HIGH 1
#define LOW 0

// RCC bits mapping
#define GPIOAEN 0
#define GPIOBEN 1
#define GPIOCEN 2
#define GPIODEN 3
#define GPIOEEN 4
#define GPIOGEN 5
#define GPIOFEN 6

#define RCC_BASE (0x40021000)
#define RCC_AHBxENR (*(volatile uint32_t*)(RCC_BASE + 0x4C))

typedef struct {
	uint32_t Pin;
	uint32_t Mode;
	uint32_t Pull;
	uint32_t Speed;
} GPIO_InitStruct;

typedef struct {
    volatile uint32_t CR1;      // 0x00: Power control register 1
    volatile uint32_t CR2;      // 0x04: Power control register 2
    volatile uint32_t CR3;      // 0x08: Power control register 3
    volatile uint32_t CR4;      // 0x0C: Power control register 4
    volatile uint32_t SR1;      // 0x10: Power status register 1
    volatile uint32_t SR2;      // 0x14: Power status register 2
    volatile uint32_t SCR;      // 0x18: Power status clear register
    volatile uint32_t reserved; // 0x1C: Reserved
    volatile uint32_t PUCRA; // 0x20: Power pull-up control register A
    volatile uint32_t PDCRA; // 0x24: Power pull-down control register A
    volatile uint32_t PUCRB; // 0x28: Power pull-up control register B
    volatile uint32_t PDCRB; // 0x2C: Power pull-down control register B
    volatile uint32_t PUCRC; // 0x30: Power pull-up control register C
    volatile uint32_t PDCRC; // 0x34: Power pull-down control register C
    volatile uint32_t PUCRD; // 0x38: Power pull-up control register D
    volatile uint32_t PDCRD; // 0x3C: Power pull-down control register D
    volatile uint32_t PUCRE; // 0x40: Power pull-up control register E
    volatile uint32_t PDCRE; // 0x44: Power pull-down control register E
    volatile uint32_t PUCRF; // 0x48: Power pull-up control register F
    volatile uint32_t PDCRF; // 0x4C: Power pull-down control register F
    volatile uint32_t PUCRG; // 0x50: Power pull-up control register G
    volatile uint32_t PDCRG; // 0x54: Power pull-down control register G
    volatile uint32_t PUCRH; // 0x58: Power pull-up control register H
    volatile uint32_t PDCRH; // 0x5C: Power pull-down control register H
    volatile uint32_t PUCRI; // 0x60: Power pull-up control register I
    volatile uint32_t PDCRI; // 0x64: Power pull-down control register I
} PWR;

#define PWR_BASE (0x40007000)
#define PWR ((PWR*) PWR_BASE)

void set_bit(volatile uint32_t *reg, unsigned int bit_pos) {
    *reg |= (1 << bit_pos);
}

void clear_bit(volatile uint32_t *reg,  uint32_t bit_pos) {
    *reg &= ~(1 << bit_pos);
}

void activate_clock_for(int gpio_en_bit)
{
    RCC_AHBxENR |= (1 << gpio_en_bit);
}

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

void gpio_write_pin(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t state)
{
    if (state == HIGH) {
        GPIOx->BSRR = (1 << pin);
    } else {
        GPIOx->BRR = (1 << pin);
    }
}

uint32_t gpio_read_pin(GPIO_TypeDef *GPIOx, uint32_t pin)
{
    return (GPIOx->IDR & (1 << pin)) ? HIGH : LOW;
}

void enable_VddIO2()
{
    set_bit(&(PWR->CR2), 9);
}