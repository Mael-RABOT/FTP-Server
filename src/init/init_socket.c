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
#include <errno.h>
#include <fcntl.h>

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

static int set_non_blocking(int *socket)
{
    int flags;

    flags = fcntl(*socket, F_GETFL, 0);
    if (flags == -1)
        return -1;
    if (fcntl(*socket, F_SETFL, flags | O_NONBLOCK) == -1)
        return -1;
    return 0;
}

int init_server_socket(t_ftp **ftp)
{
    (*ftp)->server_addr = malloc(sizeof(struct sockaddr_in));
    (*ftp)->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    (*ftp)->server_addr->sin_family = AF_INET;
    (*ftp)->server_addr->sin_port = htons((*ftp)->port);
    (*ftp)->server_addr->sin_addr.s_addr = INADDR_ANY;
    setsockopt((*ftp)->server_socket, SOL_SOCKET,
        SO_REUSEADDR | SO_REUSEPORT | SO_KEEPALIVE, &(int){1}, sizeof(int));
    if (set_non_blocking(&(*ftp)->server_socket) == -1)
        return -1;
    if (bind_socket(&(*ftp)) == -1) {
        return -1;
    }
    printf("Server listening on port %d\n", (*ftp)->port);
    if (listen_socket(&(*ftp)) == -1) {
        return -1;
    }
    return 0;
}
