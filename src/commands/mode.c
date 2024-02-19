/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** mode.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../include/protoype.h"

void assign_to_client(
    t_ftp **ftp, char **ip_parts, int *port_parts, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);
    char ip_address[16];

    client->active_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->active_socket == -1) {
        return (void)send_to_socket(ftp, "socket error", &client->socket);
    }
    client->act_addr.sin_family = AF_INET;
    client->act_addr.sin_port = htons(port_parts[0] * 256 + port_parts[1]);
    sprintf(ip_address, "%s.%s.%s.%s",
            ip_parts[0], ip_parts[1], ip_parts[2], ip_parts[3]);
    client->act_addr.sin_addr.s_addr = inet_addr(ip_address);
    if (client->act_addr.sin_addr.s_addr == INADDR_NONE)
        return (void)send_to_socket(ftp, C501, &client->socket);
    if (connect(client->active_socket,
                (struct sockaddr *)&client->act_addr,
                sizeof(client->act_addr)) < 0) {
        return (void)send_to_socket(ftp, C425, &client->socket);
    }
    client->mode = Active;
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
        token = strsep(&ip_and_port, ",");
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
    assign_to_client(ftp, ip_parts, port_parts, client_socket);
}

void pasv(t_ftp **ftp, char **arg, int *client_socket)
{
    (void)arg;
    (void)ftp;
    (void)client_socket;
    send_to_socket(ftp, C502, client_socket);
}
