/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** list.c
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "../../include/protoype.h"

static void send_files(t_ftp **ftp, t_client *client)
{
    DIR *dir;
    struct dirent *entry;
    char *pwd = get_pwd(ftp, &client->socket);

    dir = opendir(pwd);
    if (dir == NULL)
        return;
    while (entry != NULL) {
        entry = readdir(dir);
        send_to_socket(ftp, entry->d_name, &client->data_socket);
    }
    send_to_socket(ftp, "\r\n", &client->data_socket);
    closedir(dir);
}

void list(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);
    int pid;

    (void)arg;
    if (client == NULL || client->mode != Passive) {
        send_to_socket(ftp, "425 Use PORT or PASV first.\r\n", client_socket);
        return;
    }
    pid = fork();
    if (pid == -1) {
        return (void)send_to_socket(ftp, C451, client_socket);
    } else if (pid == 0) {
        send_files(ftp, client);
        exit(EXIT_SUCCESS);
    } else {
        waitpid(pid, NULL, 0);
        close(client->data_socket);
        client->mode = None;
        send_to_socket(ftp, C226, client_socket);
    }
}
