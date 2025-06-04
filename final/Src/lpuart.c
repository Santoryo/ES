#include "lpuart.h"

Pin vCOM_TX = {GPIOC, 0};
Pin vCOM_RX = {GPIOC, 1};

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
    if(LPUART->ISR & (1 << 3))
    {
        LPUART->ICR |= (1 << 3);
    }

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

void printc(const char *str, const char *color)
{
    LPUART_SendString((unsigned char *)color);
    LPUART_SendString((unsigned char *)str);
    LPUART_SendString((unsigned char *)COLOR_RESET);
}

void print(const char *str)
{
    LPUART_SendString((unsigned char *)str);
}

