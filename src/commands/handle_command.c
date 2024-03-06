/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** handle_command.c
*/

#include <string.h>

#include "../../include/protoype.h"

static void admin_only(t_ftp **ftp, char **arg, int *client_socket)
{
    (void)arg;
    send_to_socket(ftp,
        "200 Only admin can use this command.\r\n", client_socket);
}

static command_map *get_commands(void)
{
    static command_map commands[] = {
        {"USER", user, False, USER, False},
        {"PASS", pass, False, USER, False},
        {"QUIT", quit, False, USER, False},
        {"CWD", cwd, True, USER, False},
        {"CDUP", cdup, True, USER, False},
        {"DELE", delete, True, USER, False},
        {"PWD", pwd, True, USER, False},
        {"PASV", pasv, True, USER, False},
        {"PORT", port, True, USER, False},
        {"HELP", help, False, USER, False},
        {"NOOP", noop, False, USER, False},
        {"RETR", retr, True, USER, True},
        {"STOR", stor, True, USER, True},
        {"LIST", list, True, USER, True},
        {"ADMIN", admin_only, False, ADMIN, False},
        {NULL, NULL, False, USER, False}
    };

    return commands;
}

static t_bool login_check(
    t_ftp **ftp, command_map *command, int *client_socket)
{
    if ((*ftp)->clients == NULL)
        return False;
    for (int i = 0; i < (*ftp)->nb_clients; i++) {
        if ((*ftp)->clients[i]->socket == *client_socket) {
            return ((*ftp)->clients[i]->user->is_logged ==
                False && command->need_login == True)
                ? 0 * send_to_socket(ftp, C530, client_socket) : True;
        }
        return False;
    }
    return True;
}

static t_bool check_permission(
    t_ftp **ftp, int *client_socket,
    t_permission user_perm, t_permission command_perm)
{
    return (user_perm < command_perm)
        ? 0 * send_to_socket(ftp, "550 Permission denied.\r\n", client_socket)
        : True;
}

static t_bool check_mode(
    t_ftp **ftp, int *client_socket, t_mode user_mode, t_bool need_mode)
{
    if (!need_mode)
        return True;
    if (user_mode == None)
        return 0 * send_to_socket(ftp, C425MODE, client_socket);
    return True;
}

static t_command_checker check_command(
    t_ftp **ftp, int *client_socket, char **args, command_map *commands)
{
    t_client *client = get_client(ftp, client_socket);

    if (strcmp(args[0], commands->command) == 0) {
        if (login_check(ftp, commands, client_socket) == False
        || check_permission(ftp, client_socket, client->user->permission,
        commands->permission) == False || check_mode(ftp, client_socket,
        client->mode, commands->need_mode) == False) {
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
