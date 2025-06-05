#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "lpuart.h"
#include "commands.h"
#include "7LED.h"
#include "gpiodriver.h"
#include "Joystick.h"
#include "LED.h"

// Constants
#define BACKSPACE 8
#define DELETE 127
#define MAX_INPUT_LEN 25
#define LED_BLINK_INTERVAL 250
#define INTERRUPT_LENGTH 5

// Globals
unsigned char ch;
unsigned char buffer[MAX_INPUT_LEN] = {0};
int idx = 0;
int interruptCycles = 0;

// Function Prototypes
void input(void);
void input_handle_backspace(void);
void input_handle_newline(void);
void input_handle_char(unsigned char ch);
void to_lowercase(char *str);
void check_command(void);
void init_peripherals(void);
void print_welcome(void);

void to_lowercase(char *str)
{
    while (*str)
    {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

void check_command(void)
{
    buffer[idx] = '\0';
    to_lowercase((char *)buffer);

    char *cmd = strtok((char *)buffer, " ");
    char *args = strtok(NULL, "");

    if (cmd == NULL) return;

    Command *cmd_list = get_current_commands();
    int cmd_count = 0;

    while (cmd_list[cmd_count].command != NULL)
    {
        // if (strcmp(cmd, cmd_list[cmd_count].command) == 0)
        if(!strncmp(cmd, cmd_list[cmd_count].command, strlen(cmd)))
        {
            if (cmd_list[cmd_count].function)
            {
                cmd_list[cmd_count].function(args);
            }
            else
            {
                print("Command not implemented.\r\n");
            }
            return;
        }
        cmd_count++;
    }

    print("Unknown command. Type 'help' to see all of the available commands.\r\n");
}

void input(void)
{
    if (LPUART_ReceiveChar(&ch) == 0)
    {
        if (ch == BACKSPACE || ch == DELETE)
        {
            input_handle_backspace();
        }
        else if (ch == '\r' || ch == '\n')
        {
            input_handle_newline();
        }
        else
        {
            input_handle_char(ch);
        }
    }
}


void input_handle_backspace()
{
    if (idx > 0)
    {
        idx--;
        LPUART_SendChar('\b');
        LPUART_SendChar(' ');
        LPUART_SendChar('\b');
    }
}

void input_handle_newline()
{
    print("\r\n");
    buffer[idx] = '\0';
    check_command();
    idx = 0;
    buffer[0] = '\0';
    print(get_current_prefix());
    print(">");
}

void input_handle_char(unsigned char ch)
{
    if (idx < MAX_INPUT_LEN - 1)
    {
        buffer[idx++] = ch;
        LPUART_SendChar(ch);
    }
}



void init_peripherals(void)
{
    LPUART_init();
    sled_init();
    joystick_init();
    LED_init();
    tim6_init(3999, INTERRUPT_LENGTH - 1);
}

void print_welcome(void)
{
    print("\r\nSimple menu by 252575\r\nWrite `help` to obtain more information\r\n");
    print(get_current_prefix());
    print(">");
}

int main(void)
{
    init_peripherals();
    print_welcome();

    while (1)
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
