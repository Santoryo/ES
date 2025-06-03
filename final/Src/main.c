#include "lpuart.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 
#include "commands.h"
#include "7LED.h"
#include "gpiodriver.h"
#include "Joystick.h"

#define BACKSPACE 8
#define DELETE 127
#define MAX_INPUT_LEN 128

unsigned char ch;
unsigned char buffer[MAX_INPUT_LEN];
unsigned char tLevel[] = "";
int idx = 0;
int counter = 0;
void to_lowercase(char *str);
void new_line();

void check_command()
{
    buffer[idx] = '\0';

    char *cmd = strtok((char *)buffer, " ");
    char *args = strtok(NULL, "");

    if (cmd == NULL) return;

    to_lowercase(cmd);

    Command *cmd_list = get_current_commands();
    int cmd_count = 0;

    while(cmd_list[cmd_count].command != NULL)
    {
        if (strcmp(cmd, cmd_list[cmd_count].command) == 0)
        {
            if (cmd_list[cmd_count].function)
                cmd_list[cmd_count].function(args);
            else
                LPUART_SendString("Command exists but not implemented.\r\n");
            return;
        }
        cmd_count++;
    }

    LPUART_SendString("Unknown command. Type 'help'.\r\n");
    strcpy(buffer, "");
    idx = 0;
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
                new_line();
                buffer[idx] = '\0';
                check_command();
                idx = 0;
                buffer[0] = '\0';
                LPUART_SendString((unsigned char *)get_current_prefix());
                LPUART_SendString(">");
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

        sled_display();
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

    // Send welcome string
    LPUART_SendString((unsigned char *)"\r\nSimple menu by 252575\r\nWrite `help` to obtain more information");

    change_case_and_echo();

    return 0;
}
