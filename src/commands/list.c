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

static DIR *open_directory(char *pwd, char **str)
{
    DIR *dir = opendir(pwd);

    if (dir == NULL) {
        free(*str);
        *str = NULL;
    }
    return dir;
}

static char *append_directory_entries(DIR *dir, char *str, size_t *size)
{
    struct dirent *entry;
    size_t entry_len;
    char *temp;

    entry = readdir(dir);
    while (entry != NULL) {
        entry_len = strlen(entry->d_name);
        temp = realloc(str, *size + entry_len + 2);
        if (temp == NULL) {
            free(str);
            return NULL;
        }
        str = temp;
        *size += entry_len + 2;
        snprintf(str + strlen(str), *size - strlen(str), "%s ", entry->d_name);
        entry = readdir(dir);
    }
    return str;
}

static char *read_directory_entries(DIR *dir, char *str)
{
    size_t size = 1;

    str = append_directory_entries(dir, str, &size);
    if (str == NULL)
        return NULL;
    if (str[strlen(str) - 1] == ' ')
        str[strlen(str) - 1] = '\0';
    strcat(str, "\r\n");
    closedir(dir);
    return str;
}

static char *get_directory_entries(t_ftp **ftp, t_client *client)
{
    char *pwd = get_pwd(ftp, &client->socket);
    char *str = malloc(1);
    DIR *dir;

    if (str == NULL)
        return NULL;
    str[0] = '\0';
    dir = open_directory(pwd, &str);
    if (dir == NULL)
        return NULL;
    str = read_directory_entries(dir, str);
    return str;
}

static void send_directory_entries(
    t_ftp **ftp, t_client *client, char *dir_entries)
{
    if (dir_entries != NULL) {
        send_to_socket(ftp, dir_entries, &client->data_socket);
        free(dir_entries);
    }
}

static void send_files(t_ftp **ftp, t_client *client)
{
    char *dir_entries = get_directory_entries(ftp, client);

    send_directory_entries(ftp, client, dir_entries);
}

void list(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);
    int pid;

    (void)arg;
    pid = fork();
    if (pid == -1)
        return (void)send_to_socket(ftp, C451, client_socket);
    if (pid == 0) {
        if (launch_data_connections(ftp, client) == 1)
            return;
        send_files(ftp, client);
        send_to_socket(ftp, C226, client_socket);
        close(client->data_socket);
        exit(EXIT_SUCCESS);
    } else {
        send_to_socket(ftp, C150, client_socket);
        close(client->data_socket);
        client->mode = None;
    }
}
