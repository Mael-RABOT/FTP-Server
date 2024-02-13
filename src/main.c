/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** main.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/protoype.h"

static void main_loop(t_ftp **ftp)
{
    int new_socket;
    char *message = "Hello, WORLD!\n";

    while (1) {
        new_socket = accept_socket(&(*ftp));
        dprintf(new_socket, "%s", message);
    }
}

int main(int ac, char **av)
{
    t_ftp *ftp;

    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        display_help();
        return 0;
    }
    if (ac != 3) {
        return 84;
    }
    init_ftp(av, &ftp);
    main_loop(&ftp);
    free(ftp->server_addr);
    free(ftp);
}
