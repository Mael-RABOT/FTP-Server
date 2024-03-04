/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** pasv.c
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../include/protoype.h"

static int create_data_socket(void)
{
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (data_socket == -1)
        return -1;
    return data_socket;
}

static int bind_data_socket(int data_socket, struct sockaddr_in *sin)
{
    sin->sin_family = AF_INET;
    sin->sin_addr.s_addr = htonl(INADDR_ANY);
    sin->sin_port = 0;
    if (bind(data_socket, (struct sockaddr *)sin, sizeof(*sin)) == -1) {
        perror("bind");
        close(data_socket);
        return -1;
    }
    return 0;
}

static int get_port_number(
    int data_socket, struct sockaddr_in *sin, socklen_t *len)
{
    if (getsockname(data_socket, (struct sockaddr *)sin, len) == -1) {
        close(data_socket);
        return -1;
    }
    return ntohs(sin->sin_port);
}

static void store_data_socket_and_port(
    t_client *client, int data_socket, int port)
{
    client->data_socket = data_socket;
    client->pasv.port = port;
    client->mode = Passive;
}

static void send_reply_to_client(
    t_ftp **ftp, char *ip, int port, int *client_socket)
{
    char reply[256];

    for (int i = 0; ip[i] != '\0'; i++) {
        if (ip[i] == '.')
            ip[i] = ',';
    }
    sprintf(reply, "227 Entering Passive Mode (%s,%d,%d).\r\n",
        ip, port / 256, port % 256);
    send_to_socket(ftp, reply, client_socket);
}

void pasv(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    int data_socket;
    char *ip;
    int port;

    (void)arg;
    data_socket = create_data_socket();
    if (data_socket == -1)
        return;
    if (bind_data_socket(data_socket, &sin) == -1)
        return;
    port = get_port_number(data_socket, &sin, &len);
    if (port == -1)
        return;
    store_data_socket_and_port(client, data_socket, port);
    ip = inet_ntoa((*ftp)->server_addr->sin_addr);
    send_reply_to_client(ftp, ip, port, client_socket);
}
