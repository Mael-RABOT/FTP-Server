/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** launch_data_connections.c
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../include/protoype.h"

static int launch_passive_connection(t_client *client)
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int new_socket;

    if (listen(client->data_socket, 1) == -1)
        return 1;
    new_socket = accept(client->data_socket,
        (struct sockaddr *)&client_addr, &client_addr_len);
    if (new_socket == -1)
        return 1;
    close(client->data_socket);
    client->data_socket = new_socket;
    return 0;
}

static int launch_active_connection(t_client *client)
{
    struct sockaddr_in client_addr;
    int new_socket;

    new_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (new_socket == -1)
        return 1;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(
        client->port->port[0] * 256 + client->port->port[1]);
    client_addr.sin_addr.s_addr = htonl(client->port->ip[0] << 24
        | client->port->ip[1] << 16 | client->port->ip[2] << 8
        | client->port->ip[3]);
    if (connect(new_socket,
        (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
        close(new_socket);
        return 1;
    }
    client->data_socket = new_socket;
    return 0;
}

int launch_data_connections(t_ftp **ftp, t_client *client)
{
    (void)ftp;
    if (client->mode == Passive) {
        return launch_passive_connection(client);
    } else if (client->mode == Active) {
        return launch_active_connection(client);
    }
    return 1;
}
