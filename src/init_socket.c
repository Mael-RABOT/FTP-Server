/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** init_socket.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../include/types.h"

static int bind_socket(t_ftp **ftp)
{
    if (bind((*ftp)->sockfd, (struct sockaddr *)(*ftp)->server_addr,
        sizeof((*(*ftp)->server_addr))) < 0) {
        perror("bind");
        return -1;
    }
    return 0;
}

static int listen_socket(t_ftp **ftp)
{
    if (listen((*ftp)->sockfd, 5) == -1) {
        perror("listen");
        return -1;
    }
    return 0;
}

int accept_socket(t_ftp **ftp)
{
    socklen_t addrlen = sizeof((*(*ftp)->server_addr));
    int new_socket;

    new_socket = accept((*ftp)->sockfd,
        (struct sockaddr *)(*ftp)->server_addr, &addrlen);
    if (new_socket < 0) {
        perror("accept");
        return -1;
    }
    (*ftp)->new_socket = new_socket;
    return 0;
}

int init_socket(t_ftp **ftp)
{
    (*ftp)->server_addr = malloc(sizeof(struct sockaddr_in));
    (*ftp)->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    (*ftp)->server_addr->sin_family = AF_INET;
    (*ftp)->server_addr->sin_port = htons((*ftp)->port);
    (*ftp)->server_addr->sin_addr.s_addr = INADDR_ANY;
    setsockopt((*ftp)->sockfd, SOL_SOCKET,
        SO_REUSEADDR | SO_REUSEPORT | SO_KEEPALIVE, &(int){1}, sizeof(int));
    if (bind_socket(&(*ftp)) == -1) {
        return -1;
    }
    printf("Server listening on port %d\n", (*ftp)->port);
    if (listen_socket(&(*ftp)) == -1) {
        return -1;
    }
    return 0;
}
