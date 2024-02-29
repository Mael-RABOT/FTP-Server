/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** handle_command.c
*/

#include <string.h>

#include "../../include/protoype.h"

static void not_implemented(t_ftp **ftp, char **arg, int *client_socket)
{
    (void)arg;
    send_to_socket(ftp, C502, client_socket);
}

static void admin_only(t_ftp **ftp, char **arg, int *client_socket)
{
    (void)arg;
    send_to_socket(ftp,
        "200 Only admin can use this command.\r\n", client_socket);
}

static command_map *get_commands(void)
{
    static command_map commands[] = {
        {"USER", user, false, USER, false},
        {"PASS", pass, false, USER, false},
        {"QUIT", quit, false, USER, false},
        {"CWD", cwd, true, USER, false},
        {"CDUP", cdup, true, USER, false},
        {"DELE", delete, true, USER, false},
        {"PWD", pwd, true, USER, false},
        {"PASV", pasv, true, USER, false},
        {"PORT", port, true, USER, false},
        {"HELP", help, false, USER, false},
        {"NOOP", noop, false, USER, false},
        {"RETR", retr, true, USER, true},
        {"STOR", not_implemented, true, USER, true},
        {"LIST", list, true, USER, true},
        {"ADMIN", admin_only, false, ADMIN, false},
        {NULL, NULL, false, USER, false}
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

static bool check_permission(
    t_ftp **ftp, int *client_socket,
    t_permission user_perm, t_permission command_perm)
{
    return (user_perm < command_perm)
        ? 0 * send_to_socket(ftp, "550 Permission denied.\r\n", client_socket)
        : true;
}

static bool check_mode(
    t_ftp **ftp, int *client_socket, t_mode user_mode, bool need_mode)
{
    if (!need_mode)
        return true;
    if (user_mode == None)
        return 0 * send_to_socket(ftp, C425, client_socket);
    return true;
}

static t_command_checker check_command(
    t_ftp **ftp, int *client_socket, char **args, command_map *commands)
{
    t_client *client = get_client(ftp, client_socket);

    if (strcmp(args[0], commands->command) == 0) {
        if (login_check(ftp, commands, client_socket) == false
        || check_permission(ftp, client_socket, client->user->permission,
        commands->permission) == false || check_mode(ftp, client_socket,
        client->mode, commands->need_mode) == false) {
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
