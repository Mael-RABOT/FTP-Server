/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** quit.c
*/

#include <unistd.h>

#include "../../include/protoype.h"

void quit(t_ftp **ftp, char **arg)
{
    (void)arg;
    send_to_socket(ftp, C221);
    close((*ftp)->new_socket);
}
