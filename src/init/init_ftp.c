/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** init_ftp.c
*/

#include <stdlib.h>
#include <string.h>

#include "../../include/protoype.h"

int init_ftp(char **av, t_ftp **ftp)
{
    (*ftp) = malloc(sizeof(t_ftp));
    if ((*ftp) == NULL)
        return 84;
    (*ftp)->cb_write = cb_init(BUFFER_SIZE);
    (*ftp)->cb_read = cb_init(BUFFER_SIZE);
    (*ftp)->port = atoi(av[1]);
    (*ftp)->is_running = True;
    (*ftp)->nb_clients = 0;
    (*ftp)->clients = malloc(sizeof(t_client *) * MAX_CLIENTS);
    (*ftp)->login_array = parse_file("login.txt");
    if (!(*ftp)->login_array)
        return 84;
    (*ftp)->server_home = strdup(av[2]);
    if (init_server_socket(ftp) == -1)
        return 84;
    return 0;
}
