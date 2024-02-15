/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** main.c
*/

#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include "../include/protoype.h"

void big_free(t_ftp **ftp)
{
    free((*ftp)->server_addr);
    free((*ftp)->server_home);
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
    clear_clients(ftp);
    free((*ftp)->clients);
    free((*ftp));
}

static void sigint_handler(int sig)
{
    (void)sig;
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
    signal(SIGINT, sigint_handler);
    ret = init_ftp(av, &ftp);
    if (ret == 0)
        main_loop(&ftp);
    big_free(&ftp);
    return (ret == 0 ? 84 : 0);
}
