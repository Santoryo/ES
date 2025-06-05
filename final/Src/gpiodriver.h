#pragma once
#include <stdint.h>

// MAIN TYPES
typedef volatile uint32_t REG32;
typedef volatile uint16_t REG16;
typedef volatile uint8_t REG8;

typedef uint32_t RESTRICTED32;
typedef uint16_t RESTRICTED16;
typedef uint8_t RESTRICTED8;

// BIT MACROS
#define SET_BIT(REG, BIT_POS) ((REG) |= (1 << (BIT_POS)))
#define CLEAR_BIT(REG, BIT_POS) ((REG) &= ~(1 << (BIT_POS)))
#define READ_BIT(REG, BIT_POS) (((REG) & (1 << (BIT_POS))) ? 1 : 0)
#define F_CK 4000000

// GPIO STRUCT
typedef struct
{
    REG32 MODER;
    REG16 OTYPER;
    uint16_t RESERVED0;
    REG32 OSPEEDR;
    REG32 PUPDR;
    REG16 IDR;
    uint16_t RESERVED1;
    REG16 ODR;
    uint16_t RESERVED2;
    REG32 BSRR;
    REG32 LCKR;
    REG32 AFRL;
    REG32 AFRH;
    REG16 BRR;
    uint16_t RESERVED3;
    REG16 ASCR;
    uint16_t RESERVED4;
} GPIO_TypeDef;

// GPIO BASE ADDRESSES
#define GPIOA_BASE (0x48000000)
#define GPIOB_BASE (0x48000400)
#define GPIOC_BASE (0x48000800)
#define GPIOD_BASE (0x48000C00)
#define GPIOE_BASE (0x48001000)
#define GPIOF_BASE (0x48001400)
#define GPIOG_BASE (0x48001800)
#define GPIOH_BASE (0x48001C00)

// GPIO PORTS
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

// RCC BITS MAPPING
#define GPIOAEN 0
#define GPIOBEN 1
#define GPIOCEN 2
#define GPIODEN 3
#define GPIOEEN 4
#define GPIOFEN 5
#define GPIOGEN 6
#define GPIOHEN 7
#define GPIOIEN 8

// PWR STRUCT
typedef struct {
    REG16 CR1;
    uint16_t RESERVED1;
    REG16 CR2;
    uint16_t RESERVED2;
    REG16 CR3;
    uint16_t RESERVED3;
    REG16 CR4;
    uint16_t RESERVED4;
    REG16 SR1;
    uint16_t RESERVED5;
    REG16 SR2;
    uint16_t RESERVED6;
    REG16 SCR;
    uint16_t RESERVED7;
    uint32_t RESERVED8;
    REG16 PUCRA;
    uint16_t RESERVED9;
    REG16 PDCRA;
    uint16_t RESERVED10;
    REG16 PUCRB;
    uint16_t RESERVED11;
    REG16 PDCRB;
    uint16_t RESERVED12;
    REG16 PUCRC;
    uint16_t RESERVED13;
    REG16 PDCRC;
    uint16_t RESERVED14;
    REG16 PUCRD;
    uint16_t RESERVED15;
    REG16 PDCRD;
    uint16_t RESERVED16;
    REG16 PUCRE;
    uint16_t RESERVED17;
    REG16 PDCRE;
    uint16_t RESERVED18;
    REG16 PUCRF;
    uint16_t RESERVED19;
    REG16 PDCRF;
    uint16_t RESERVED20;
    REG16 PUCRG;
    uint16_t RESERVED21;
    REG16 PDCRG;
    uint16_t RESERVED22;
    REG16 PUCRH;
    uint16_t RESERVED23;
    REG16 PDCRH;
    uint16_t RESERVED24;
    REG16 PUCRI;
    uint16_t RESERVED25;
    REG16 PDCRI;
} PWR_TypeDef;

#define PWR_BASE (0x40007000)
#define PWR ((PWR_TypeDef *) PWR_BASE)

// GPIO INIT STRUCT
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

// RCC STRUCT
typedef struct
{
    REG32 CR;
    REG32 ICSCR;
    REG32 CFGR;
    REG32 PLLCFGR;
    REG32 PLLSAI1CFGR;
    REG32 PLLSAI2CFGR;
    volatile uint8_t CIER;
    uint8_t RESERVED0[3];
    volatile uint8_t CIFR;
    uint8_t RESERVED1[3];
    volatile uint8_t CICR;
    uint8_t RESERVED2[3];
    uint8_t RESERVED3[4];
    REG32 AHB1RSTR;
    REG32 AHB2RSTR;
    REG32 AHB3RSTR;
    uint8_t RESERVED4[4];
    REG32 APB1RSTR1;
    REG32 APB1RSTR2;
    REG32 APB2RSTR;
    uint8_t RESERVED5[4];
    REG32 AHB1ENR;
    REG32 AHB2ENR;
    REG32 AHB3ENR;
    uint8_t RESERVED6[4];
    REG32 APB1ENR1;
    REG32 APB1ENR2;
    REG32 APB2ENR;
    uint8_t RESERVED7[4];
    REG32 AHB1SMENR;
    REG32 AHB2SMENR;
    REG32 AHB3SMENR;
    uint8_t RESERVED8[4];
    REG32 APB1SMENR1;
    REG32 APB1SMENR2;
    REG32 APB2SMENR;
    uint8_t RESERVED9[4];
    REG32 CCIPR;
    uint8_t RESERVED10[4];
    REG32 BDCR;
    REG32 CSR;
    REG32 CRRCR;
    REG8 CCIPR2;
    uint8_t RESERVED11[3];
} RCC_TypeDef;

#define RCC_BASE (0x40021000)
#define RCC ((RCC_TypeDef *)RCC_BASE)

// TIM6 STRUCT
typedef struct
{
    REG16 CR1;
    uint16_t RESERVED1;
    REG16 CR2;
    uint16_t RESERVED2;
    uint32_t RESERVED3;
    REG16 DIER;
    uint16_t RESERVED4;
    REG16 SR;
    uint16_t RESERVED5;
    REG16 EGR;
    uint16_t RESERVED6;
    uint32_t RESERVED7;
    uint32_t RESERVED8;
    uint32_t RESERVED9;
    REG32 CNT;
    REG16 PSC;
    uint16_t RESERVED10;
    REG16 ARR;
    uint16_t RESERVED11;
} TIMx_TypeDef;

#define TIM6_BASE (0x40001000)
#define TIM6 ((TIMx_TypeDef *)TIM6_BASE)

#define NVIC_BASE (0xE000E100)
#define NVIC_ISER1 ((volatile uint32_t *)(NVIC_BASE + 0x04)) // Interrupt Set-Enable Register 1


// FUNCTIONS
void activate_clock_for(REG32 *reg, int gpio_en_bit);
void gpio_init(GPIO_TypeDef *GPIOx, GPIO_InitStruct *init);
void gpio_write_pin(GPIO_TypeDef *GPIOx, uint32_t pin, uint32_t state);
uint32_t gpio_read_pin(GPIO_TypeDef *GPIOx, uint32_t pin);
void enable_VddIO2();
void tim6_init(uint16_t prescaler, uint16_t autoreload);
void delay(uint32_t val);


