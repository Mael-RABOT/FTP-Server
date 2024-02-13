/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** init_ftp.c
*/

#include <stdlib.h>

#include "../include/protoype.h"

void init_ftp(char **av, t_ftp **ftp)
{
    (*ftp) = malloc(sizeof(t_ftp));
    (*ftp)->cb_write = cb_init(BUFFER_SIZE);
    (*ftp)->cb_read = cb_init(BUFFER_SIZE);
    (*ftp)->port = atoi(av[1]);
    (*ftp)->path = av[2];
    init_socket(ftp);
    accept_socket(ftp);
    send_to_socket(ftp, "220 Service ready for new user.\r\n");
}
