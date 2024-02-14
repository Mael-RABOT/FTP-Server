/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** handle_command.c
*/

#include <string.h>

#include "../../include/protoype.h"

void not_implemented(t_ftp **ftp, char **arg, int *client_socket)
{
    (void)arg;
    send_to_socket(ftp, C502, client_socket);
}

command_map *get_commands(void)
{
    static command_map commands[] = {
        {"USER", user},
        {"PASS", pass},
        {"QUIT", quit},
        {"CWD", cwd},
        {"CDUP", cdup},
        {"DELE", not_implemented},
        {"PWD", pwd},
        {"PASV", not_implemented},
        {"PORT", not_implemented},
        {"HELP", not_implemented},
        {"NOOP", not_implemented},
        {"RETR", not_implemented},
        {"STOR", not_implemented},
        {"LIST", not_implemented},
        {NULL, NULL}
    };

    return commands;
}

void handle_command(t_ftp **ftp, char *command, int *client_socket)
{
    int i = 0;
    char **args;
    command_map *commands;

    if (command == NULL)
        return;
    args = str_to_word_array(command);
    if (args == NULL)
        return;
    commands = get_commands();
    while (commands[i].command != NULL) {
        if (strcmp(args[0], commands[i].command) == 0) {
            commands[i].function(ftp, args, client_socket);
            free_array(args);
            return;
        }
        i++;
    }
    send_to_socket(ftp, C500, client_socket);
    free_array(args);
}
