#include "gpiodriver.h"
#define LPUART_BASE (0x40008000)
#define LPUARTEN 0

Pin vCOM_TX = {GPIOC, 0};
Pin vCOM_RX = {GPIOC, 1};

int LPUART_init(void);
int LPUART_SendChar(unsigned char data);
int LPUART_ReceiveChar(unsigned char *data);
int LPUART_SendString(unsigned char *data);

typedef struct
{
    REG32 CR1;       // Offset 0x00: Control Register 1
    REG32 CR2;       // Offset 0x04: Control Register 2
    REG32 CR3;       // Offset 0x08: Control Register 3
    REG32 BRR;       // Offset 0x0C: Baud Rate Register
    REG32 RESERVED1; // Offset 0x10: Reserved
    REG32 RESERVED2; // Offset 0x14: Reserved
    REG32 RQR;       // Offset 0x18: Request Register
    REG32 ISR;       // Offset 0x1C: Interrupt & Status Register
    REG32 ICR;       // Offset 0x20: Interrupt Clear Register
    REG16 RDR;       // Offset 0x24: Receive Data Register
    REG16 RESERVED3; // Offset 0x26: Reserved
    REG16 TDR;       // Offset 0x28: Transmit Data Register
    REG16 RESERVED4; // Offset 0x2A: Reserved
} LPUART_TypeDef;

#define LPUART ((LPUART_TypeDef *)LPUART_BASE)

int LPUART_init(void)
{
    activate_clock_for(&RCC->AHB2ENR, GPIOCEN);
    activate_clock_for(&RCC->APB1ENR2, LPUARTEN);

    GPIOC->AFRL &= ~(0b1111 << (vCOM_TX.pin * 4));
    GPIOC->AFRL |= (0b1000 << (vCOM_TX.pin * 4));

    GPIOC->AFRL &= ~(0b1111 << (vCOM_RX.pin * 4));
    GPIOC->AFRL |= (0b1000 << (vCOM_RX.pin * 4));

    GPIO_InitStruct initStruct;
    initStruct.Pin = vCOM_TX.pin;
    initStruct.Mode = MODE_ALTERNATE;
    initStruct.Pull = PULL_NO;
    initStruct.Speed = OUTPUT_LOWSPEED;
    gpio_init(vCOM_TX.port, &initStruct);

    initStruct.Pin = vCOM_RX.pin;
    initStruct.Mode = MODE_ALTERNATE;
    initStruct.Pull = PULL_NO;
    initStruct.Speed = OUTPUT_LOWSPEED;
    gpio_init(vCOM_RX.port, &initStruct);

    CLEAR_BIT(LPUART->CR1, 0);

    // 1 Start bit, 8 data bits, n stop bits
    CLEAR_BIT(LPUART->CR1, 12);
    CLEAR_BIT(LPUART->CR1, 28);

    // Tx/Rx baud = (256 * f_ck) / LPUARTDIV
    LPUART->BRR = (256 * 4000000) / 115200;

    // 1 stop bit
    LPUART->CR2 &= ~(0b11 << 12);

    // Enable LPUART
    SET_BIT(LPUART->CR1, 0);

    // Disable DMA
    CLEAR_BIT(LPUART->CR3, 6);

    // Enable Receiver and Transmitter
    SET_BIT(LPUART->CR1, 2);
    SET_BIT(LPUART->CR1, 3);

    return 0;
}

int LPUART_SendChar(unsigned char data)
{
    while (!(LPUART->ISR & (1 << 7)));
    LPUART->TDR = data;
    return 0;
}

int LPUART_ReceiveChar(unsigned char *data)
{
    if (LPUART->ISR & (1 << 5))
    {
        *data = (unsigned char)LPUART->RDR;
        return 0;
    }
    return -1; // No data
}

int LPUART_SendString(unsigned char *str)
{
    while (*str)
    {
        LPUART_SendChar(*str++);
    }
    return 0;
}
