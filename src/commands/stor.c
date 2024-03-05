/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** stor.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../../include/protoype.h"

static void get_file(t_ftp **ftp, t_client *client, char *filename)
{
    FILE *file;
    char buffer[1024];
    int bytes_read;
    char *pwd = get_pwd(ftp, &client->socket);
    char *path = malloc(strlen(pwd) + strlen(filename) + 2);

    sprintf(path, "%s/%s", pwd, filename);
    file = fopen(path, "w");
    if (file == NULL)
        return;
    do {
        bytes_read = read(client->data_socket, buffer, sizeof(buffer));
        if (bytes_read > 0) {
            fwrite(buffer, 1, bytes_read, file);
        }
    } while (bytes_read > 0);
    fclose(file);
}

static int check_args(char **args)
{
    int size;

    for (size = 0; args[size]; size++);
    return (size != 2) ? 1 : 0;
}

void stor(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);
    int pid;

    if (check_args(arg))
        return (void) send_to_socket(ftp, "451: bad args", client_socket);
    pid = fork();
    if (pid == -1)
        return (void)send_to_socket(ftp, "451: fork failed", client_socket);
    if (pid == 0) {
        if (launch_data_connections(ftp, client) == 1)
            return;
        get_file(ftp, client, arg[1]);
        send_to_socket(ftp, C226, client_socket);
        close(client->data_socket);
        exit(EXIT_SUCCESS);
    } else {
        send_to_socket(ftp, C150, client_socket);
        close(client->data_socket);
        client->mode = None;
    }
}
