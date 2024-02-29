/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** pasv.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../include/protoype.h"

void pasv(t_ftp **ftp, char **arg, int *client_socket)
{
    struct sockaddr_in data_addr;
    t_client *client = get_client(ftp, client_socket);

    printf("Debug: Entering pasv function\n");
    (void)arg;
    data_addr.sin_family = AF_INET;
    data_addr.sin_port = htons(0);
    data_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client->mode = Passive;
}
