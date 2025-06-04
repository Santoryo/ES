#pragma once
#include "gpiodriver.h"
#define LPUART_BASE (0x40008000)
#define LPUARTEN 0

int LPUART_init(void);
int LPUART_SendChar(unsigned char data);
int LPUART_ReceiveChar(unsigned char *data);
int LPUART_SendString(unsigned char *data);

void printc(const char *str, const char *color);
void print(const char *str);

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

// Terminal Colors
#define COLOR_RESET "\x1b[0m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RED "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_WHITE "\x1b[37m"