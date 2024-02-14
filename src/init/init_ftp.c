/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** init_ftp.c
*/

#include <stdlib.h>
#include <string.h>

#include "../../include/protoype.h"

static void init_user(t_ftp **ftp, char *home)
{
    (*ftp)->user = malloc(sizeof(t_user));
    (*ftp)->user->home = strdup(home);
    (*ftp)->user->username = malloc(256 * sizeof(char));
    (*ftp)->user->password = malloc(256 * sizeof(char));
    (*ftp)->user->is_logged = false;
    (*ftp)->user->dir = create_node(home);
    if ((*ftp)->user->username == NULL || (*ftp)->user->password == NULL) {
        exit(84);
    }
}

int init_ftp(char **av, t_ftp **ftp)
{
    (*ftp) = malloc(sizeof(t_ftp));
    (*ftp)->cb_write = cb_init(BUFFER_SIZE);
    (*ftp)->cb_read = cb_init(BUFFER_SIZE);
    (*ftp)->port = atoi(av[1]);
    (*ftp)->is_running = true;
    (*ftp)->login_array = parse_file("login.txt");
    init_user(ftp, av[2]);
    if (init_socket(ftp) == -1) {
        return -1;
    }
    if (accept_socket(ftp) == -1) {
        return -1;
    }
    send_to_socket(ftp, C220);
    return 0;
}
