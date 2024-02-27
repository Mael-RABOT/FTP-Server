/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** pasv.c
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../include/protoype.h"

static int create_data_socket(t_ftp **ftp, int *client_socket)
{
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (data_socket == -1)
        send_to_socket(ftp,
        "500 Error creating data socket\r\n", client_socket);
    return data_socket;
}

static void bind_data_socket(
    t_ftp **ftp, int *client_socket, int data_socket,
    struct sockaddr_in *data_addr)
{
    if (bind(data_socket, (struct sockaddr *)data_addr,
    sizeof(*data_addr)) == -1)
        send_to_socket(ftp,
        "500 Error binding data socket\r\n", client_socket);
}

static void listen_data_socket(
    t_ftp **ftp, int *client_socket, int data_socket)
{
    if (listen(data_socket, 1) == -1)
        send_to_socket(ftp,
        "500 Error listening on data socket\r\n", client_socket);
}

static void send_pasv_response(
    t_ftp **ftp, int *client_socket, int data_socket,
    struct sockaddr_in *data_addr)
{
    char response[256];
    socklen_t len = sizeof(*data_addr);

    if (getsockname(data_socket, (struct sockaddr *)data_addr, &len) == -1)
        send_to_socket(ftp, "500 Error getting socket name", client_socket);
    sprintf(response, "227 Entering Passive Mode (%s,%d,%d)\r\n",
            inet_ntoa(data_addr->sin_addr),
            ntohs(data_addr->sin_port) / 256,
            ntohs(data_addr->sin_port) % 256);
    send_to_socket(ftp, response, client_socket);
}

static void set_client_data_socket(
    t_ftp **ftp, int *client_socket, int data_socket)
{
    t_client *client = get_client(ftp, client_socket);

    if (client != NULL) {
        client->data_socket = data_socket;
        client->mode = Passive;
    }
}

void pasv(t_ftp **ftp, char **arg, int *client_socket)
{
    struct sockaddr_in data_addr;
    int data_socket;

    (void)arg;
    data_addr.sin_family = AF_INET;
    data_addr.sin_port = htons(0);
    data_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    data_socket = create_data_socket(ftp, client_socket);
    if (data_socket == -1)
        return;
    bind_data_socket(ftp, client_socket, data_socket, &data_addr);
    listen_data_socket(ftp, client_socket, data_socket);
    send_pasv_response(ftp, client_socket, data_socket, &data_addr);
    set_client_data_socket(ftp, client_socket, data_socket);
}
