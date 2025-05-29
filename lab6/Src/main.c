#include "lpuart.h"
#include "gpiodriver.h"
#include "constants.h"
#include <string.h>
#include <ctype.h>
#include "7LED.h"
#include <stdlib.h> 

#define BACKSPACE 8
#define DELETE 127
#define MAX_INPUT_LEN 128

unsigned char ch;
unsigned char buffer[MAX_INPUT_LEN];
int idx = 0;

int counter = 0;

void check_command()
{
    char * pEnd;
    counter = strtol(buffer, &pEnd, 10);
    display_seven_segment(counter);
    buffer[0] = '\0';
}


void change_case_and_echo(void)
{
    while (1)
    {
        if (LPUART_ReceiveChar(&ch) == 0)
        {
            if (ch == BACKSPACE || ch == DELETE)
            {
                if (idx > 0)
                {
                    idx--;
                    LPUART_SendChar('\b');
                    LPUART_SendChar(' ');
                    LPUART_SendChar('\b');
                }
            }
            else if (ch == '\r' || ch == '\n')
            {
                LPUART_SendChar('\r');
                LPUART_SendChar('\n');
                idx = 0;
                LPUART_SendString(PREFIX);
                check_command();
            }
            else
            {
                if (idx < MAX_INPUT_LEN - 1)
                {
                    buffer[idx++] = ch;
                    LPUART_SendChar(ch);
                }
            }
        }

        display_seven_segment(counter);
    }
}

int main(void)
{
    LPUART_init();
    init_seven_segment();

    // Send welcome string
    LPUART_SendString((unsigned char *)"\r\nSimple menu by lucy\r\nWrite `help` to obtain more information");

    change_case_and_echo();

    return 0;
}
