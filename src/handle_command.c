/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** handle_command.c
*/

#include <string.h>

#include "../include/protoype.h"

static void user(t_ftp **ftp, char **arg)
{
    if (array_len(arg) != 2) {
        send_to_socket(ftp, "500 Missing Argument.\r\n");
        return;
    }
    send_to_socket(ftp, "200 Command 1 okay.\r\n");
}

static void pass(t_ftp **ftp, char **arg __attribute__((unused)))
{
    send_to_socket(ftp, "200 Command 2 okay.\r\n");
}

void handle_command(t_ftp **ftp, char *command)
{
    int i = 0;
    char **args = str_to_word_array(command);
    command_map commands[] = {
            {"USER", user},
            {"PASS", pass},
            {NULL, NULL}
    };

    if (command == NULL || args == NULL || args[0] == NULL)
        return;
    while (commands[i].command != NULL) {
        if (strcmp(args[0], commands[i].command) == 0) {
            commands[i].function(ftp, args);
            return;
        }
        i++;
    }
    send_to_socket(ftp, "500 Unknown command.\r\n");
}
