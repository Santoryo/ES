#include "commands.h"
#include <stdio.h>
#include "7LED.h"
#include "lpuart.h"

Command root_commands[] = {
    {"up", root_cmd, "Go to root level"},
    {"7led", sled_cmd, "Go to 7-LED level"},
    {"led", led_cmd, "Go to LED level"},
    {"joy", joy_cmd, "Go to Joystick level"},
    {"help", help_cmd, "Display this help message"},
    {NULL, NULL, NULL} // End of command list
};

Command sled_commands[] = {
    {"up", root_cmd, "Go to root level"},
    {"display", sled_cmd_display, "Display number from 0 to 9999 on the 7-LED display. Usage: 'Display <value>'"},
    {"read", sled_cmd_read, "Display on the terminal the number from 7-LED display"},
    {"help", help_cmd, "Display this help message"},
    {NULL, NULL, NULL} // End of command list
};

Command led_commands[] = {
    {"up", root_cmd, "Go to root level"},
    {"set", NULL, "Turn on LED. Usage: 'set <led_id>' where <led_id> is 0-7 or R, G, B"},
    {"clear", NULL, "Turn off LED. Usage: 'clear <led_id>' where <led_id> is 0-7 or R, G, B"},
    {"blink", NULL, "Blink LED five times. Usage: 'blink <led_id>' where <led_id> is 0-7 or R, G, B"},
    {"status", NULL, "Read LED state. Usage: 'read <led_id>' where <led_id> is 0-7 or R, G, B"},
    {"toggle", NULL, "Toggle LED state. Usage: 'toggle <led_id>' where <led_id> is 0-7 or R, G, B"},
    {"help", help_cmd, "Display this help message"},
    {NULL, NULL, NULL} // End of command list
};

Command joy_commands[] = {
    {"up", root_cmd, "Go to root level"},
    {"read", NULL, "Read joystick state. Usage: 'read <id>' where <id> is 'L' – left, 'R' – right, 'U' – up, 'D' – down, 'C' - center)"},
    {"help", help_cmd, "Display this help message"},
    {NULL, NULL, NULL} // End of command list
};

Command lpuart_commands[] = {
    {"up", root_cmd, "Go to root level"},
    {"status", NULL, "Display baudrate, number of databits and parity bits, informations read from registers and then calculated baudrate"},
    {"help", help_cmd, "Display this help message"},
    {NULL, NULL, NULL} // End of command list
};

char *prefix = "";

Command *current_commands = root_commands;

int empty_args(char *args, char *cmd_name)
{
    if (args == NULL || strlen(args) == 0)
    {
        char message[100];
        snprintf(message, sizeof(message), "Usage: %s <value>\r\n", cmd_name);
        LPUART_SendString(message);
        return -1;
    }
    return 0;
}

void root_cmd(char *args)
{
    current_commands = root_commands;
    prefix = "";
    LPUART_SendString("You are now at the root level.\r\n");
}

void help_cmd(char* args)
{
    LPUART_SendString("Available commands:\r\n");

    int i = 0;

    while(current_commands[i].command != NULL)
    {
        LPUART_SendString(current_commands[i].command);
        LPUART_SendString(": ");
        LPUART_SendString(current_commands[i].description);
        LPUART_SendString("\r\n");
        i++;
    }
}

void sled_cmd(char *args)
{
    current_commands = sled_commands;
    prefix = "7LED";
}
void led_cmd(char *args)
{
    current_commands = led_commands;
    prefix = "LED";
}
void joy_cmd(char *args)
{
    current_commands = joy_commands;
    prefix = "JOY";
}

void lpuart_cmd(char *args)
{
    current_commands = lpuart_commands;
    prefix = "LPUART";
}

void sled_cmd_display(char *args)
{
    if (empty_args(args, "display"))
        return;

    char *endptr;
    int value = strtol(args, &endptr, 10);

    if (*endptr != '\0' || args == endptr)
    {
        LPUART_SendString("Invalid value. Please enter a number between 0 and 9999.\r\n");
        return;
    }

    int res = sled_set(value);
    if (!res)
    {
        LPUART_SendString("Invalid value. Please enter a number between 0 and 9999.\r\n");
        return;
    }

    sled_display();
}

void sled_cmd_read(char *args)
{
    char message[50];
    snprintf(message, sizeof(message), "Current value on 7-LED display: %d\r\n", sled_get());
    LPUART_SendString(message);
}

Command *get_current_commands()
{
    return current_commands;
}

char *get_current_prefix()
{
    return prefix;
}
