/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** handle_command.c
*/

#include <string.h>
#include <stdio.h>

#include "../include/protoype.h"

static bool function1(t_ftp **ftp, char *arg)
{
    send_to_socket(ftp, "200 Command 1 okay.\r\n");
    return true;
}

static bool function2(t_ftp **ftp, char *arg)
{
    send_to_socket(ftp, "200 Command 2 okay.\r\n");
    return true;
}

bool handle_command(t_ftp **ftp, char *command)
{
    int i = 0;
    command_map commands[] = {
            {"command1\r\n", function1},
            {"command2\r\n", function2},
            {NULL, NULL}
    };

    if (command == NULL) {
        return true;
    }
    while (commands[i].command != NULL) {
        if (strcmp(command, commands[i].command) == 0) {
            return commands[i].function(ftp, command);
        }
        i++;
    }
    send_to_socket(ftp, "500 Unknown command.\r\n");
    return true;
}
