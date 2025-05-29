#include "lpuart.h"
#include "gpiodriver.h"

#define BACKSPACE 8
#define DELETE 127
#define MAX_INPUT_LEN 128

void change_case_and_echo(void)
{
    unsigned char ch;
    unsigned char buffer[MAX_INPUT_LEN];
    int index = 0;

    while (1)
    {
        if (LPUART_ReceiveChar(&ch) == 0)
        {
            if (ch == BACKSPACE || ch == DELETE)
            {
                if (index > 0)
                {
                    index--; // remove last char from buffer

                    // Send backspace sequence to terminal: move back, erase, move back
                    LPUART_SendChar('\b');
                    LPUART_SendChar(' ');
                    LPUART_SendChar('\b');
                }
            }
            else if (ch == '\r' || ch == '\n') // handle enter key if needed
            {
                LPUART_SendChar('\r');
                LPUART_SendChar('\n');
                index = 0; // reset buffer
            }
            else
            {
                // Convert case
                if (ch >= 'a' && ch <= 'z')
                {
                    ch -= 32;
                }
                else if (ch >= 'A' && ch <= 'Z')
                {
                    ch += 32;
                }

                // Echo and store only if buffer not full
                if (index < MAX_INPUT_LEN - 1)
                {
                    buffer[index++] = ch;
                    LPUART_SendChar(ch);
                }
            }
        }
    }
}

int main(void)
{
    LPUART_init();
    init_seven_segment();

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
    LPUART_SendString((unsigned char *)"\r\nWelcome message\r\n");

    change_case_and_echo();

    return 0;
}
