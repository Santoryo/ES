#pragma once
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    const char *command;
    void (*function)(char*);
    const char *description;
} Command;

// Root level commands
void root_cmd(char *args);
void sled_cmd(char *args);
void led_cmd(char *args);
void joy_cmd(char *args);
void lpuart_cmd(char *args);
void help_cmd(char *args);

// 7-LED level commands
void sled_cmd_display(char *args);
void sled_cmd_read(char *args);

// Joystick level commands
void joy_cmd_read(char *args);

// LPUART level commands
void lpuart_cmd_status(char *args);

// LED level commands
void led_cmd_set(char *args);
void led_cmd_clear(char *args);
void led_cmd_status(char *args);
void led_cmd_blink(char *args);
void led_cmd_toggle(char *args);

Command* get_current_commands();
char* get_current_prefix();