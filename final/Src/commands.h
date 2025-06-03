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


Command* get_current_commands();
char* get_current_prefix();