#pragma once
#include <stdint.h>

// MAIN
typedef volatile uint32_t REG32;
typedef volatile uint16_t REG16;
typedef volatile uint8_t REG8;

typedef uint32_t RESTRICTED32;
typedef uint16_t RESTRICTED16;
typedef uint8_t RESTRICTED8;

#define SET_BIT(REG, BIT_POS) ((REG) |= (1 << (BIT_POS)))
#define CLEAR_BIT(REG, BIT_POS) ((REG) &= ~(1 << (BIT_POS)))
#define READ_BIT(REG, BIT_POS) (((REG) & (1 << (BIT_POS))) ? 1 : 0)

// GPIO SECTION

typedef struct
{
    REG32 MODER;        // Offset 0x00: Mode register
    REG16 OTYPER;       // Offset 0x04: Output type register
    uint16_t RESERVED0; // Reserved
    REG32 OSPEEDR;      // Offset 0x08: Output speed register
    REG32 PUPDR;        // Offset 0x0C: Pull-up/pull-down register
    REG16 IDR;          // Offset 0x10: Input data register
    uint16_t RESERVED1; // Reserved
    REG16 ODR;          // Offset 0x14: Output data register
    uint16_t RESERVED2; // Reserved
    REG32 BSRR;         // Offset 0x18: Bit set/reset register
    REG32 LCKR;         // Offset 0x1C: Configuration lock register
    REG32 AFRL;         // Offset 0x20: Alternate function low register
    REG32 AFRH;         // Offset 0x24: Alternate function high register
    REG16 BRR;          // Offset 0x28: Bit reset register
    uint16_t RESERVED3; // Reserved
    REG16 ASCR;         // Offset 0x2C: Analog switch control register
    uint16_t RESERVED4; // Reserved
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
#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef *)GPIOF_BASE)
#define GPIOG ((GPIO_TypeDef *)GPIOG_BASE)
#define GPIOH ((GPIO_TypeDef *)GPIOH_BASE)

// MODER VALUES
#define MODE_INPUT 0
#define MODE_OUTPUT 1
#define MODE_ALTERNATE 2
#define MODE_ANALOG 3

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
#define GPIOFEN 5
#define GPIOGEN 6
#define GPIOHEN 7
#define GPIOIEN 8

#define PWR_BASE (0x40007000)
#define PWR ((PWR_TypeDef *) PWR_BASE)

typedef struct {
    REG16 CR1;           // Offset 0x00: Power control register 1
    uint16_t RESERVED1;  // Reserved
    REG16 CR2;           // Offset 0x04: Power control register 2
    uint16_t RESERVED2;  // Reserved
    REG16 CR3;           // Offset 0x08: Power control register 3
    uint16_t RESERVED3;  // Reserved
    REG16 CR4;           // Offset 0x0C: Power control register 4
    uint16_t RESERVED4;  // Reserved
    REG16 SR1;           // Offset 0x10: Power status register 1
    uint16_t RESERVED5;  // Reserved
    REG16 SR2;           // Offset 0x14: Power status register 2
    uint16_t RESERVED6;  // Reserved
    REG16 SCR;           // Offset 0x18: Power status clear register
    uint16_t RESERVED7;  // Reserved
    uint32_t RESERVED8;  // Reserved Offset 0x1C
    REG16 PUCRA;        // Offset 0x20: Power port A pull-up control register
    uint16_t RESERVED9;  // Reserved
    REG16 PDCRA;        // Offset 0x24: Power port A pull-down control register
    uint16_t RESERVED10; // Reserved
    REG16 PUCRB;        // Offset 0x28: Power port B pull-up control register
    uint16_t RESERVED11; // Reserved
    REG16 PDCRB;         // Offset 0x2C: Power port B pull-down control register
    uint16_t RESERVED12; // Reserved
    REG16 PUCRC;        // Offset 0x30: Power port C pull-up control register
    uint16_t RESERVED13; // Reserved
    REG16 PDCRC;        // Offset 0x34: Power port C pull-down control register
    uint16_t RESERVED14; // Reserved
    REG16 PUCRD;        // Offset 0x38: Power port D pull-up control register
    uint16_t RESERVED15; // Reserved
    REG16 PDCRD;        // Offset 0x3C: Power port D pull-down control register
    uint16_t RESERVED16; // Reserved
    REG16 PUCRE;        // Offset 0x40: Power port E pull-up control register
    uint16_t RESERVED17; // Reserved
    REG16 PDCRE;       // Offset 0x44: Power port E pull-down control register
    uint16_t RESERVED18; // Reserved
    REG16 PUCRF;        // Offset 0x48: Power port F pull-up control register
    uint16_t RESERVED19; // Reserved
    REG16 PDCRF;        // Offset 0x4C: Power port F pull-down control register
    uint16_t RESERVED20; // Reserved
    REG16 PUCRG;        // Offset 0x50: Power port G pull-up control register
    uint16_t RESERVED21; // Reserved
    REG16 PDCRG;        // Offset 0x54: Power port G pull-down control register
    uint16_t RESERVED22; // Reserved
    REG16 PUCRH;        // Offset 0x58: Power port H pull-up control register
    uint16_t RESERVED23; // Reserved
    REG16 PDCRH;        // Offset 0x5C: Power port H pull-down control register
    uint16_t RESERVED24; // Reserved
    REG16 PUCRI;        // Offset 0x60: Power port I pull-up control register
    uint16_t RESERVED25; // Reserved
    REG16 PDCRI;        // Offset 0x64: Power port I pull-down control register
} PWR_TypeDef;

typedef struct
{
    uint32_t Pin;
    uint32_t Mode;
    uint32_t Pull;
    uint32_t Speed;
} GPIO_InitStruct;

typedef struct Pin
{
    GPIO_TypeDef *port;
    uint32_t pin;
} Pin;

void activate_clock_for(REG32 *reg, int gpio_en_bit)
{
    *reg |= (1 << gpio_en_bit);
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
    if (state == HIGH)
    {
        SET_BIT(GPIOx->BSRR, pin);
    }
    else
    {
        SET_BIT(GPIOx->BRR, pin);
    }
}

uint32_t gpio_read_pin(GPIO_TypeDef *GPIOx, uint32_t pin)
{
    return (GPIOx->IDR & (1 << pin)) ? HIGH : LOW;
}

void enable_VddIO2()
{
    SET_BIT(PWR->CR2, 9);
}

// RCC SECTION

#define RCC_BASE (0x40021000)
#define RCC ((RCC_TypeDef *)RCC_BASE)

typedef struct
{
    REG32 CR;              // Offset 0x00: Clock control register
    REG32 ICSCR;           // Offset 0x04: Internal clock sources calibration register
    REG32 CFGR;            // Offset 0x08: Clock configuration register
    REG32 PLLCFGR;         // Offset 0x0C: PLL configuration register
    REG32 PLLSAI1CFGR;     // Offset 0x10: PLLSAI1 configuration register
    REG32 PLLSAI2CFGR;     // Offset 0x14: PLLSAI2 configuration register
    volatile uint8_t CIER; // Offset 0x18: Clock interrupt enable register (only 8 bits used)
    uint8_t RESERVED0[3];  // Offset 0x19–0x1B: Reserved
    volatile uint8_t CIFR; // Offset 0x1C: Clock interrupt flag register (only 8 bits used)
    uint8_t RESERVED1[3];  // Offset 0x1D–0x1F: Reserved
    volatile uint8_t CICR; // Offset 0x20: Clock interrupt clear register (only 8 bits used)
    uint8_t RESERVED2[3];  // Offset 0x21–0x23: Reserved
    uint8_t RESERVED3[4];  // Offset 0x24–0x27: Reserved
    REG32 AHB1RSTR;        // Offset 0x28: AHB1 peripheral reset register
    REG32 AHB2RSTR;        // Offset 0x2C: AHB2 peripheral reset register
    REG32 AHB3RSTR;        // Offset 0x30: AHB3 peripheral reset register
    uint8_t RESERVED4[4];  // Offset 0x34: Reserved
    REG32 APB1RSTR1;       // Offset 0x38: APB1 peripheral reset register 1
    REG32 APB1RSTR2;       // Offset 0x3C: APB1 peripheral reset register 2
    REG32 APB2RSTR;        // Offset 0x40: APB2 peripheral reset register
    uint8_t RESERVED5[4];  // Offset 0x44: Reserved
    REG32 AHB1ENR;         // Offset 0x48: AHB1 peripheral clocks enable register
    REG32 AHB2ENR;         // Offset 0x4C: AHB2 peripheral clocks enable register
    REG32 AHB3ENR;         // Offset 0x50: AHB3 peripheral clocks enable register
    uint8_t RESERVED6[4];  // Offset 0x54: Reserved
    REG32 APB1ENR1;        // Offset 0x58: APB1 peripheral clocks enable register 1
    REG32 APB1ENR2;        // Offset 0x5C: APB1 peripheral clocks enable register 2
    REG32 APB2ENR;         // Offset 0x60: APB2 peripheral clocks enable register
    uint8_t RESERVED7[4];  // Offset 0x64: Reserved
    REG32 AHB1SMENR;       // Offset 0x68: AHB1 clocks enable in Sleep/Stop modes register
    REG32 AHB2SMENR;       // Offset 0x6C: AHB2 clocks enable in Sleep/Stop modes register
    REG32 AHB3SMENR;       // Offset 0x70: AHB3 clocks enable in Sleep/Stop modes register
    uint8_t RESERVED8[4];  // Offset 0x74: Reserved
    REG32 APB1SMENR1;      // Offset 0x78: APB1 Sleep/Stop enable register 1
    REG32 APB1SMENR2;      // Offset 0x7C: APB1 Sleep/Stop enable register 2
    REG32 APB2SMENR;       // Offset 0x80: APB2 Sleep/Stop enable register
    uint8_t RESERVED9[4];  // Offset 0x84: Reserved
    REG32 CCIPR;           // Offset 0x88: Clock configuration independent register
    uint8_t RESERVED10[4]; // Offset 0x8C: Reserved
    REG32 BDCR;            // Offset 0x90: Backup domain control register
    REG32 CSR;             // Offset 0x94: Control/status register
    REG32 CRRCR;           // Offset 0x98: Clock recovery RC register
    REG8 CCIPR2;           // Offset 0x9C: Peripherals independent clock config reg 2
    uint8_t RESERVED11[3]; // Offset 0x9D–0x9F: Reserved
} RCC_TypeDef;

// TIM SECTION

#define TIM6_BASE (0x40001000)

typedef struct
{
    REG16 CR1;           // Offset 0x00: Control register 1
    uint16_t RESERVED1;  // Reserved
    REG16 CR2;           // Offset 0x04: Control register 2
    uint16_t RESERVED2;  // Reserved
    uint32_t RESERVED3;  // Reserved Offset 0x08
    REG16 DIER;          // Offset 0x0C: DMA/Interrupt enable register
    uint16_t RESERVED4;  // Reserved
    REG16 SR;            // Offset 0x10: Status register
    uint16_t RESERVED5;  // Reserved
    REG16 EGR;           // Offset 0x14: Event generation register
    uint16_t RESERVED6;  // Reserved
    uint32_t RESERVED7;  // Reserved Offset 0x18
    uint32_t RESERVED8;  // Reserved Offset 0x1C
    uint32_t RESERVED9;  // Reserved Offset 0x20
    REG32 CNT;           // Offset 0x24: Counter register
    REG16 PSC;           // Offset 0x28: Prescaler register
    uint16_t RESERVED10; // Reserved
    REG16 ARR;           // Offset 0x2C: Auto-reload register
    uint16_t RESERVED11; // Reserved
} TIMx_TypeDef;

#define TIM6 ((TIMx_TypeDef *)TIM6_BASE)

void tim6_init(uint16_t prescaler, uint16_t autoreload)
{
    activate_clock_for(&RCC->APB1ENR1, 4);
    TIM6->PSC = prescaler;
    TIM6->ARR = autoreload;
    TIM6->CR1 |= (1 << 0);
}

void delay(uint32_t val)
{
    for (int i = 0; i <= val * 100; i++)
    {
        // do nothing
    };
}