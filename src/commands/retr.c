/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** list.c
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../../include/protoype.h"

static void send_file(t_ftp **ftp, t_client *client, char *filename)
{
    FILE *file;
    char buffer[1024];
    int bytes_read;
    char *pwd = get_pwd(ftp, &client->socket);
    char *path = malloc(strlen(pwd) + strlen(filename) + 2);

    sprintf(path, "%s/%s", pwd, filename);
    file = fopen(path, "r");
    if (file == NULL)
        return;
    bytes_read = fread(buffer, 1, 1024, file);
    while (bytes_read > 0) {
        write(client->data_socket, buffer, bytes_read);
        bytes_read = fread(buffer, 1, 1024, file);
    }
    fclose(file);
    free(path);
}

static int check_file(char *filename, t_ftp **ftp, int *client_socket)
{
    char *pwd = get_pwd(ftp, client_socket);
    char *path = malloc(strlen(pwd) + strlen(filename) + 2);
    FILE *file;

    sprintf(path, "%s/%s", pwd, filename);
    file = fopen(path, "r");
    if (file == NULL) {
        free(path);
        return 1;
    }
    fclose(file);
    free(path);
    return 0;
}

static int check_args(char **args, t_ftp **ftp, int *client_socket)
{
    int size;

    for (size = 0; args[size]; size++);
    return (size != 2) ? 1 : check_file(args[1], ftp, client_socket);
}

void retr(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);
    int pid;

    if (check_args(arg, ftp, client_socket))
        return (void) send_to_socket(ftp, C451, client_socket);
    pid = fork();
    if (pid == -1)
        return (void)send_to_socket(ftp, C451, client_socket);
    if (pid == 0) {
        if (launch_data_connections(ftp, client) == 1)
            return;
        send_file(ftp, client, arg[1]);
        send_to_socket(ftp, C226, client_socket);
        close(client->data_socket);
        exit(EXIT_SUCCESS);
    } else {
        send_to_socket(ftp, C150, client_socket);
        close(client->data_socket);
        client->mode = None;
    }
}
