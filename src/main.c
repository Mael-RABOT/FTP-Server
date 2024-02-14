/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** main.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/protoype.h"

static void main_loop(t_ftp **ftp)
{
    while ((*ftp)->is_running) {
        read_from_socket(ftp);
        handle_command(ftp, get_command(&(*ftp)->cb_read));
    }
}

int main(int ac, char **av)
{
    t_ftp *ftp;
    int ret = 0;

    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        display_help();
        return 0;
    }
    if (ac != 3)
        return 84;
    ret = init_ftp(av, &ftp);
    if (ret == 0)
        main_loop(&ftp);
    free(ftp->server_addr);
    free(ftp);
    return (ret <= 0 ? 84 : 0);
}
