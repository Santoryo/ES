#pragma once
#include "gpiodriver.h"
#define LPUART_BASE (0x40008000)
#define LPUARTEN 0
#define LPUARTDIV 115200

int LPUART_init(void);
int LPUART_SendChar(unsigned char data);
int LPUART_ReceiveChar(unsigned char *data);
int LPUART_SendString(unsigned char *data);

void print(const char *str);
int get_baud_rate(void);
char* get_stop_bits(void);
char* get_m_bits(void);
char* get_parity(void);

// M-Bits used for word length
#define CR1_M1 28
#define CR1_M0 12

#define CR1_PCE 10
#define CR2_STOP_BIT 12

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

