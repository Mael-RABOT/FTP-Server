/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** user.c
*/

#include <string.h>

#include "../../include/protoype.h"

void user(t_ftp **ftp, char **arg)
{
    bool found = false;
    int i = 0;

    if (array_len(arg) != 2) {
        send_to_socket(ftp, C501);
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
        return (void)send_to_socket(ftp, C530);
    (*ftp)->user->username = strdup(arg[1]);
    send_to_socket(ftp, C331);
}

void pass(t_ftp **ftp, char **arg)
{
    (*ftp)->user->password = strdup((array_len(arg) != 2) ? "" : arg[1]);
    if (!(*ftp)->user->username || strcmp((*ftp)->user->username, "") == 0) {
        send_to_socket(ftp, C332);
        return;
    }
    if (check_user(ftp) == false) {
        send_to_socket(ftp, C530);
        return;
    }
    (*ftp)->user->is_logged = true;
    send_to_socket(ftp, C230);
}
