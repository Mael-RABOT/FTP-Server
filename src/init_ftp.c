/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** init_ftp.c
*/

#include <stdlib.h>

#include "../include/protoype.h"

int init_ftp(char **av, t_ftp **ftp)
{
    (*ftp) = malloc(sizeof(t_ftp));
    (*ftp)->cb_write = cb_init(BUFFER_SIZE);
    (*ftp)->cb_read = cb_init(BUFFER_SIZE);
    (*ftp)->port = atoi(av[1]);
    (*ftp)->path = av[2];
    if (init_socket(ftp) == -1) {
        return -1;
    }
    if (accept_socket(ftp) == -1) {
        return -1;
    }
    send_to_socket(ftp, "220 Service ready for new user.\r\n");
    return 0;
}
