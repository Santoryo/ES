#include "lpuart.h"
#include "gpiodriver.h"

void change_case_and_echo(void)
{
    unsigned char ch;
    while (1)
    {
        if (LPUART_ReceiveChar(&ch) == 0)
        {
            if (ch >= 'a' && ch <= 'z')
            {
                ch -= 32;
            }
            else if (ch >= 'A' && ch <= 'Z')
            {
                ch += 32;
            }
            LPUART_SendChar(ch);
        }
    }
}

int main(void)
{
    LPUART_init();

    // Send alphabet
    for (char c = 'a'; c <= 'z'; c++)
    {
        LPUART_SendChar(c);
    }
    for (char c = 'A'; c <= 'Z'; c++)
    {
        LPUART_SendChar(c);
    }

    // Send welcome string
    LPUART_SendString((unsigned char *)"\r\nWelcome message - Leo Ryba 252575\r\n");

    change_case_and_echo();

    return 0;
}
