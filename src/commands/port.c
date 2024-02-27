/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** mode.c
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../include/protoype.h"

void connect_to_client(
    t_ftp **ftp, char *ip_parts[], int port_parts[], int *client_socket)
{
    struct sockaddr_in client_addr;
    t_client *client = NULL;

    for (int i = 0; i < (*ftp)->nb_clients; i++)
        if ((*ftp)->clients[i]->socket == *client_socket)
            client = (*ftp)->clients[i];
    if (client == NULL)
        return (void)send_to_socket(ftp, "Invalid client", client_socket);
    client->active_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->active_socket == -1)
        return (void)send_to_socket(ftp, "Invalid socket", client_socket);
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port_parts[0] * 256 + port_parts[1]);
    client_addr.sin_addr.s_addr = inet_addr(ip_parts[0]);
    if (connect(client->active_socket,
            (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
        close(client->active_socket);
        return (void)send_to_socket(ftp, C425, client_socket);
    }
    send_to_socket(ftp, C200, client_socket);
}

void port(t_ftp **ftp, char **arg, int *client_socket)
{
    char *ip_and_port = arg[1];
    char *token;
    char *ip_parts[4];
    int port_parts[2];

    if (array_len(arg) <= 1)
        return (void)send_to_socket(ftp, C501, client_socket);
    for (int i = 0; i < 4; i++) {
        token = strsep(&ip_and_port, ".");
        if (!token)
            return (void)send_to_socket(ftp, C501, client_socket);
        ip_parts[i] = token;
    }
    for (int i = 0; i < 2; i++) {
        token = strsep(&ip_and_port, ",");
        if (!token)
            return (void)send_to_socket(ftp, C501, client_socket);
        port_parts[i] = atoi(token);
    }
    connect_to_client(ftp, ip_parts, port_parts, client_socket);
}
