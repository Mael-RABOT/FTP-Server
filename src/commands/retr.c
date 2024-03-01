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

static void send_file(t_client *client, char **args)
{
    FILE *file;
    char buffer[1024];
    int bytes_read;

    file = fopen(args[1], "r");
    if (file == NULL)
        return;
    bytes_read = fread(buffer, 1, 1024, file);
    while (bytes_read > 0) {
        write(client->data_socket, buffer, bytes_read);
        bytes_read = fread(buffer, 1, 1024, file);
    }
    fclose(file);
}

static int check_args(char **args)
{
    int size;

    for (size = 0; args[size]; size++)
        ;
    return (size != 2) ? 1 : 0;
}

void retr(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);
    int pid;

    if (check_args(arg))
        return;
    pid = fork();
    if (pid == -1)
        return (void)send_to_socket(ftp, C451, client_socket);
    if (pid == 0) {
        if (launch_data_connections(ftp, client) == 1)
            return;
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
