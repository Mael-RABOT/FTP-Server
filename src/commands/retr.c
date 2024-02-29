/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** list.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>

#include "../../include/protoype.h"

void send_file(t_client *client, char **args)
{
    FILE *file;
    char buffer[1024];
    int bytes_read;

    file = fopen(args[1], "r");
    if (file == NULL)
        return;
    bytes_read = fread(buffer, 1, 1024, file);
    while (bytes_read > 0) {
        bytes_read = fread(buffer, 1, 1024, file);
        write(client->data_socket, buffer, bytes_read);
    }
    fclose(file);
}

void retr(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);
    int pid;

    (void)arg;
    if (launch_data_connections(ftp, client) == 1)
        return;
    pid = fork();
    if (pid == -1)
        return (void)send_to_socket(ftp, C451, client_socket);
    if (pid == 0) {
        send_file(client, arg);
        send_to_socket(ftp, C226, client_socket);
        close(client->data_socket);
        exit(EXIT_SUCCESS);
    } else {
        send_to_socket(ftp, C150, client_socket);
        close(client->data_socket);
        client->mode = None;
    }
}
