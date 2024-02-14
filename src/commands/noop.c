/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** noop.c
*/

#include "../../include/protoype.h"

void noop(t_ftp **ftp, char **arg, int *client_socket)
{
    (void)arg;
    send_to_socket(ftp, C200, client_socket);
}
