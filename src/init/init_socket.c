/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** init_server_socket.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../../include/types.h"

static int bind_socket(t_ftp **ftp)
{
    if (bind((*ftp)->server_socket, (struct sockaddr *)(*ftp)->server_addr,
        sizeof((*(*ftp)->server_addr))) < 0) {
        perror("bind");
        return -1;
    }
    return 0;
}

static int listen_socket(t_ftp **ftp)
{
    if (listen((*ftp)->server_socket, 5) == -1) {
        perror("listen");
        return -1;
    }
    return 0;
}

int init_server_socket(t_ftp **ftp)
{
    (*ftp)->server_addr = malloc(sizeof(struct sockaddr_in));
    (*ftp)->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    (*ftp)->server_addr->sin_family = AF_INET;
    (*ftp)->server_addr->sin_port = htons((*ftp)->port);
    (*ftp)->server_addr->sin_addr.s_addr = INADDR_ANY;
    if (bind_socket(&(*ftp)) == -1) {
        return -1;
    }
    printf("Server listening on port %d\n", (*ftp)->port);
    if (listen_socket(&(*ftp)) == -1) {
        return -1;
    }
    return 0;
}
