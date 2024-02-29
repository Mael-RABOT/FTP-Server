/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** mode.c
*/

#include <string.h>
#include <stdlib.h>

#include "../../include/protoype.h"

static int parser_port(char *token, int *port)
{
    int part;

    for (int i = 0; i < 2; i++) {
        token = strtok(NULL, ",");
        if (token == NULL)
            return 1;
        part = atoi(token);
        if (part < 0 || part > 255)
            return 1;
        *port = (i == 0) ? part * 256 : *port + part;
    }
    return 0;
}

static int parse_input(char *arg, int *ip, int *port)
{
    char *token;

    for (int i = 0; i < 4; i++) {
        token = strtok((i == 0) ? arg : NULL, ",");
        if (token == NULL)
            return 1;
        ip[i] = atoi(token);
        if (ip[i] < 0 || ip[i] > 255)
            return 1;
    }
    parser_port(token, port);
    return 0;
}

static int validate_input(int *ip, int port)
{
    for (int i = 0; i < 4; i++) {
        if (ip[i] < 0 || ip[i] > 255) {
            return 1;
        }
    }
    if (port < 0 || port > 65535) {
        return 1;
    }
    return 0;
}

void port(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);

    client->port = malloc(sizeof(t_port));
    if (parse_input(arg[1], client->port->ip, client->port->port) != 0)
        return (void)send_to_socket(ftp, C451, client_socket);
    if (validate_input(client->port->ip, *client->port->port) != 0)
        return (void)send_to_socket(ftp, C451, client_socket);
    client->mode = Active;
    send_to_socket(ftp, C200, client_socket);
}
