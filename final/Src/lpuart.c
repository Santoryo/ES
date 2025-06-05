#include "lpuart.h"
#include <stdlib.h>

Pin vCOM_TX = {GPIOC, 0};
Pin vCOM_RX = {GPIOC, 1};

typedef struct {
    int val;
    const char *description;
} Bit_Description;

Bit_Description stopBits[] =
{
    {0, "1 stop bit"},
    {1, "Reserved"},
    {2, "2 stop bits"},
    {3, "Reserved"},
    {-1, NULL}
};

Bit_Description MBits[] =
{
    {0, "1 star bit, 8 data bits"},
    {1, "1 start bit, 9 data bits"},
    {2, "0 start bit, 7 data bits"},
    {-1, NULL}
};

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
    CLEAR_BIT(LPUART->CR1, CR1_M1);
    CLEAR_BIT(LPUART->CR1, CR1_M0);

    // Tx/Rx baud = (256 * f_ck) / LPUARTDIV
    LPUART->BRR = (256 * F_CK) / LPUARTDIV;

    // 1 stop bit
    LPUART->CR2 &= ~(0b11 << CR2_STOP_BIT);

    // Disable parity
    CLEAR_BIT(LPUART->CR1, CR1_PCE);

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

void print(const char *str)
{
    LPUART_SendString((unsigned char *)str);
}

int get_baud_rate(void)
{
    return (256 * F_CK) / LPUART->BRR;
}

char* get_stop_bits(void)
{
    int stopBitsValue = READ_BIT(LPUART->CR2, CR2_STOP_BIT);
    int i = 0;
    while(stopBits[i].val != -1)
    {
        if (stopBits[i].val == stopBitsValue)
        {
            return (char *)stopBits[i].description;
        }
        i++;
    }
    return "Unknown stop bits";
}

char* get_m_bits(void)
{
    int m0 = READ_BIT(LPUART->CR1, CR1_M0);
    int m1 = READ_BIT(LPUART->CR1, CR1_M1);
    int mBitsValue = (m1 << 1) | m0;
    int i = 0;
    while(MBits[i].val != -1)
    {
        if (MBits[i].val == mBitsValue)
        {
            return (char *)MBits[i].description;
        }
        i++;
    }
    return "Unknown M bits";
}

char* get_parity(void)
{
    if (!READ_BIT(LPUART->CR1, CR1_PCE))
    {
        return "Parity disabled";
    }
    if (READ_BIT(LPUART->CR1, CR1_PCE) && READ_BIT(LPUART->CR1, 9))
    {
        return "Even parity";
    }
    else if (READ_BIT(LPUART->CR1, CR1_PCE) && !READ_BIT(LPUART->CR1, 9))
    {
        return "Odd parity";
    }
    return "Unknown parity setting";
}




