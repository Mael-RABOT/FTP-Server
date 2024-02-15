/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** user.c
*/

#include <string.h>

#include "../../include/protoype.h"

void user(t_ftp **ftp, char **arg, int *client_socket)
{
    bool found = false;
    int i = 0;
    t_client *client = get_client(ftp, client_socket);

    if (array_len(arg) != 2) {
        send_to_socket(ftp, C501, client_socket);
        return;
    }
    while ((*ftp)->login_array[i].user != NULL) {
        if (strcmp((*ftp)->login_array[i].user, arg[1]) == 0) {
            found = true;
            break;
        }
        i++;
    }
    if (found == false)
        return (void)send_to_socket(ftp, C530, client_socket);
    client->user->username = strdup(arg[1]);
    send_to_socket(ftp, C331, client_socket);
}

void pass(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);

    if (!client->user->username || strcmp(client->user->username, "") == 0) {
        send_to_socket(ftp, C332, client_socket);
        return;
    }
    client->user->password = strdup((array_len(arg) != 2) ? "" : arg[1]);
    if (check_user(ftp, client) == false) {
        send_to_socket(ftp, C530, client_socket);
        return;
    }
    client->user->is_logged = true;
    send_to_socket(ftp, C230, client_socket);
}
