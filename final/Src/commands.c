#include "commands.h"
#include <stdio.h>
#include "7LED.h"
#include "lpuart.h"
#include "Joystick.h"
#include "LED.h"

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
    {"set", led_cmd_set, "Turn on LED. Usage: 'set <led_id>' where <led_id> is 0-7 or R, G, B"},
    {"clear", led_cmd_clear, "Turn off LED. Usage: 'clear <led_id>' where <led_id> is 0-7 or R, G, B"},
    {"blink", led_cmd_blink, "Blink LED five times. Usage: 'blink <led_id>' where <led_id> is 0-7 or R, G, B"},
    {"status", led_cmd_status, "Read LED state. Usage: 'read <led_id>' where <led_id> is 0-7 or R, G, B"},
    {"toggle", led_cmd_toggle, "Toggle LED state. Usage: 'toggle <led_id>' where <led_id> is 0-7 or R, G, B"},
    {"help", help_cmd, "Display this help message"},
    {NULL, NULL, NULL} // End of command list
};

Command joy_commands[] = {
    {"up", root_cmd, "Go to root level"},
    {"read", joy_cmd_read, "Read joystick state. Usage: 'read <id>' where <id> is 'L' – left, 'R' – right, 'U' – up, 'D' – down, 'C' - center)"},
    {"help", help_cmd, "Display this help message"},
    {NULL, NULL, NULL} // End of command list
};

Command lpuart_commands[] = {
    {"up", root_cmd, "Go to root level"},
    {"status", lpuart_cmd_status, "Display baudrate, number of databits and parity bits, informations read from registers and then calculated baudrate"},
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
        printc(message, COLOR_YELLOW);
        return -1;
    }
    return 0;
}

void root_cmd(char *args)
{
    current_commands = root_commands;
    prefix = "";
}

void help_cmd(char* args)
{
    print("Available commands:\r\n");

    int i = 0;

    while(current_commands[i].command != NULL)
    {
        print(current_commands[i].command);
        print(": ");
        print(current_commands[i].description);
        print("\r\n");
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
        printc("Invalid value. Please enter a number between 0 and 9999.\r\n", COLOR_RED);
        return;
    }

    int res = sled_set(value);
    if (res)
    {
        printc("Number has to be a value between 0 and 9999.\r\n", COLOR_RED);
        return;
    }
}

void sled_cmd_read(char *args)
{
    char val_str[5];
    snprintf(val_str, sizeof(val_str), "%d", sled_get());
    print("Current value on 7-LED display: ");
    printc(val_str, COLOR_CYAN);
    print("\r\n");
}

void joy_cmd_read(char *args)
{
    if (empty_args(args, "read"))
        return;

    char id = args[0];

    int state = joystick_read(id);

    if(state == -1)
    {
        printc("Invalid joystick ID. Use 'D', 'R', 'L', or 'C'.\r\n", COLOR_RED);
        return;
    }

    print("Joystick state for '");
    printc(&id, COLOR_CYAN);
    print("': ");
    if (state)
    {
        printc("Pressed\r\n", COLOR_GREEN);
    }
    else
    {
        printc("Released\r\n", COLOR_RED);
    }
    print("\r\n");
}

void lpuart_cmd_status(char *args)
{
    // This function should display the status of the LPUART.
    // For now, we will just send a placeholder message.
    print("LPUART status: Placeholder for actual status.\r\n");
}

void led_cmd_set(char *args)
{
    if (empty_args(args, "set"))
        return;

    char id = args[0];
    int res = LED_set(id, ON);
    if (res == -1)
    {
        printc("Invalid LED ID. Use 0-7 or 'R', 'G', 'B'.\r\n", COLOR_RED);
    }
}

void led_cmd_clear(char *args)
{
    if (empty_args(args, "clear"))
        return;

    char id = args[0];
    int res = LED_set(id, OFF);
    if (res == -1)
    {
        printc("Invalid LED ID. Use 0-7 or 'R', 'G', 'B'.\r\n", COLOR_RED);
    }
}

void led_cmd_blink(char *args)
{
    if (empty_args(args, "blink"))
        return;

    char id = args[0];
    int res = LED_set_blink(id, 5);
    if (res == -1)
    {
        printc("Invalid LED ID. Use 0-7 or 'R', 'G', 'B'.\r\n", COLOR_RED);
        return;
    }
}

void led_cmd_status(char *args)
{
    if (empty_args(args, "read"))
        return;

    char id = args[0];
    int state = LED_get(id);
    if (state == -1)
    {
        printc("Invalid LED ID. Use 0-7 or 'R', 'G', 'B'.\r\n", COLOR_RED);
        return;
    }

    print("LED ");
    printc(&id, COLOR_CYAN);
    print(" state: ");
    if (state)
    {
        printc("ON\r\n", COLOR_GREEN);
    }
    else
    {
        printc("OFF\r\n", COLOR_RED);
    }
}

void led_cmd_toggle(char *args)
{
    if (empty_args(args, "toggle"))
        return;

    char id = args[0];
    int state = LED_get(id);
    if (state == -1)
    {
        printc("Invalid LED ID. Use 0-7 or 'R', 'G', 'B'.\r\n", COLOR_RED);
        return;
    }

    int res = LED_set(id, !state);

    if (res == -1)
    {
        printc("Invalid LED ID. Use 0-7 or 'R', 'G', 'B'.\r\n", COLOR_RED);
        return;
    }

    print("LED ");
    printc(&id, COLOR_CYAN);
    print(" toggled to ");
    if (!state)
    {
        printc("ON\r\n", COLOR_GREEN);
    }
    else
    {
        printc("OFF\r\n", COLOR_RED);
    }
}





Command *get_current_commands()
{
    return current_commands;
}

char *get_current_prefix()
{
    return prefix;
}
