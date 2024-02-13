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

bool handle_command(char *command)
{
    printf("Command: %s\n", command);
    return true;
}

static void main_loop(t_ftp **ftp)
{
    bool running = true;

    while (running) {
        read_from_socket(ftp);
        running = handle_command(get_command(&(*ftp)->cb_read));
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
