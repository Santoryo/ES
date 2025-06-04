#include "lpuart.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 
#include "commands.h"
#include "7LED.h"
#include "gpiodriver.h"
#include "Joystick.h"
#include "LED.h"

#define BACKSPACE 8
#define DELETE 127
#define MAX_INPUT_LEN 25

unsigned char ch;
unsigned char buffer[MAX_INPUT_LEN];
unsigned char tLevel[] = "";
int idx = 0;
int counter = 0;
void to_lowercase(char *str);
void new_line();

int interruptCycles = 0;

#define LED_BLINK_INTERVAL 250
#define INTERRUPT_LENGTH 5

void check_command()
{
    buffer[idx] = '\0';

    to_lowercase((char *)buffer);

    char *cmd = strtok((char *)buffer, " ");
    char *args = strtok(NULL, "");

    if (cmd == NULL) return;

    Command *cmd_list = get_current_commands();
    int cmd_count = 0;

    while(cmd_list[cmd_count].command != NULL)
    {
        if (strcmp(cmd, cmd_list[cmd_count].command) == 0)
        {
            if (cmd_list[cmd_count].function)
                cmd_list[cmd_count].function(args);
            else
                print("Command exists but not implemented.\r\n");
            return;
        }
        cmd_count++;
    }

    print("Unknown command. Type 'help'.\r\n");
    strcpy((char *)buffer, "");
    idx = 0;
}


void input(void)
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
                new_line();
                buffer[idx] = '\0';
                check_command();
                idx = 0;
                buffer[0] = '\0';
                print(get_current_prefix());
                print(">");
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
}

void new_line()
{
    LPUART_SendChar('\r');
    LPUART_SendChar('\n');
}

void to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}


int main(void)
{
    LPUART_init();
    sled_init();
    joystick_init();
    LED_init();
    tim6_init(3999, INTERRUPT_LENGTH - 1); 

    // Send welcome string
    print("\r\nSimple menu by 252575\r\nWrite `help` to obtain more information\r\n");
    print(get_current_prefix());
    print(">");

    while(1)
    {
        input();
    }

    return 0;
}

void TIM6_DACUNDER_IRQHandler(void)
{
    if (READ_BIT(TIM6->SR, 0))
    {
        CLEAR_BIT(TIM6->SR, 0);
        sled_display();
        interruptCycles++;
        if (interruptCycles >= LED_BLINK_INTERVAL / 5)
        {
            interruptCycles = 0;
            LED_blink();
        }
    }
}

