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
        {"USER", user, false},
        {"PASS", pass, false},
        {"QUIT", quit, false},
        {"CWD", cwd, true},
        {"CDUP", cdup, true},
        {"DELE", not_implemented, true},
        {"PWD", pwd, true},
        {"PASV", pasv, true},
        {"PORT", port, true},
        {"HELP", help, false},
        {"NOOP", noop, false},
        {"RETR", not_implemented, true},
        {"STOR", not_implemented, true},
        {"LIST", list, true},
        {NULL, NULL, false}
    };

    return commands;
}

static bool login_check(t_ftp **ftp, command_map *command, int *client_socket)
{
    if ((*ftp)->clients == NULL)
        return false;
    for (int i = 0; i < (*ftp)->nb_clients; i++) {
        if ((*ftp)->clients[i]->socket == *client_socket) {
            return ((*ftp)->clients[i]->user->is_logged ==
                false && command->need_login == true)
                ? 0 * send_to_socket(ftp, C530, client_socket) : true;
        }
        return false;
    }
    return true;
}

static t_command_checker check_command(
    t_ftp **ftp, int *client_socket, char **args, command_map *commands)
{
    if (strcmp(args[0], commands->command) == 0) {
        if (login_check(ftp, commands, client_socket) == false) {
            free_array(args);
            return login_failed;
        }
        commands->function(ftp, args, client_socket);
        free_array(args);
        return login_success;
    }
    return command_not_found;
}

static void execute_command(
    t_ftp **ftp, int *client_socket, command_map *commands, char **args)
{
    int i = 0;

    while (commands[i].command != NULL) {
        switch (check_command(ftp, client_socket, args, &commands[i])) {
            case command_not_found:
                break;
            case login_failed:
                return;
            case login_success:
                return;
        }
        i++;
    }
    send_to_socket(ftp, C500, client_socket);
    free_array(args);
}

void handle_command(t_ftp **ftp, char *command, int *client_socket)
{
    char **args;
    command_map *commands;

    if (command == NULL)
        return;
    args = str_to_word_array(command);
    if (args == NULL)
        return;
    commands = get_commands();
    execute_command(ftp, client_socket, commands, args);
}
