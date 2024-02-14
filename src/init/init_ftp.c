/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** init_ftp.c
*/

#include <stdlib.h>
#include <string.h>

#include "../../include/protoype.h"

static int init_user(t_ftp **ftp, char *home)
{
    (*ftp)->user = malloc(sizeof(t_user));
    if ((*ftp)->user == NULL) {
        return 84;
    }
    (*ftp)->user->home = strdup(home);
    if ((*ftp)->user->home == NULL) {
        return 84;
    }
    (*ftp)->user->username = NULL;
    (*ftp)->user->password = NULL;
    (*ftp)->user->is_logged = false;
    (*ftp)->user->dir = create_node(home);
    if ((*ftp)->user->dir == NULL) {
        return 84;
    }
    return 0;
}

int init_ftp(char **av, t_ftp **ftp)
{
    (*ftp) = malloc(sizeof(t_ftp));
    if ((*ftp) == NULL)
        return 84;
    (*ftp)->cb_write = cb_init(BUFFER_SIZE);
    (*ftp)->cb_read = cb_init(BUFFER_SIZE);
    (*ftp)->port = atoi(av[1]);
    (*ftp)->is_running = true;
    (*ftp)->login_array = parse_file("login.txt");
    if (!(*ftp)->login_array)
        return 84;
    if (init_user(ftp, av[2]) == 84)
        return 84;
    if (init_socket(ftp) == -1)
        return 84;
    if (accept_socket(ftp) == -1)
        return 84;
    send_to_socket(ftp, C220);
    return 0;
}
