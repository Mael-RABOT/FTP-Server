/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** delete.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../../include/protoype.h"

void delete(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);
    char *pwd = get_pwd(ftp, &client->socket);
    char *file = arg[1];
    char *path = malloc(strlen(pwd) + strlen(file) + 2);

    if (path == NULL)
        return;
    path[0] = '\0';
    strcat(path, pwd);
    strcat(path, "/");
    strcat(path, file);
    if (remove(path) == 0)
        send_to_socket(ftp, "250 File deleted.\r\n", client_socket);
    else
        send_to_socket(ftp, "550 File not found.\r\n", client_socket);
    free(path);
}
