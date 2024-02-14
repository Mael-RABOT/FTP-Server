/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** main.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

#include "../include/protoype.h"

void main_loop(t_ftp **ftp)
{
    char *command;

    while ((*ftp)->is_running) {
        read_from_socket(ftp);
        command = get_command(&(*ftp)->cb_read);
        if (command != NULL) {
            handle_command(ftp, command);
            free(command);
        }
    }
}

void big_free(t_ftp **ftp)
{
    free((*ftp)->server_addr);
    delete_list(&(*ftp)->user->dir);
    free((*ftp)->user->password);
    free((*ftp)->user->username);
    free((*ftp)->user->home);
    free((*ftp)->user);
    if ((*ftp)->login_array != NULL) {
        for (int i = 0; (*ftp)->login_array[i].user != NULL; i++) {
            free((*ftp)->login_array[i].user);
            free((*ftp)->login_array[i].pass);
        }
        free((*ftp)->login_array);
    }
    free((*ftp)->cb_read->buffer);
    free((*ftp)->cb_read);
    free((*ftp)->cb_write->buffer);
    free((*ftp)->cb_write);
    free((*ftp));
}

int main(int ac, char **av)
{
    t_ftp *ftp;
    int ret;

    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        display_help();
        return 0;
    }
    if (ac != 3)
        return 84;
    ret = init_ftp(av, &ftp);
    if (ret == 0)
        main_loop(&ftp);
    big_free(&ftp);
    return (ret == 0 ? 84 : 0);
}
