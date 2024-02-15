/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** path.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../../include/protoype.h"

char *get_pwd(t_ftp **ftp, int *client_socket)
{
    char *cwd = malloc(1000);
    t_client *client = get_client(ftp, client_socket);
    t_node *current_node = client->user->dir;
    bool first = true;

    if (cwd == NULL) {
        return NULL;
    }
    cwd[0] = '\0';
    while (current_node != NULL) {
        if (!first && strcmp(cwd, "/") != 0) {
            strcat(cwd, "/");
        }
        strcat(cwd, current_node->data);
        current_node = current_node->next;
        first = false;
    }
    return cwd;
}

void pwd(t_ftp **ftp, char **arg, int *client_socket)
{
    char cwd[1000] = "";
    char message[sizeof(cwd) + 24];
    t_client *client = get_client(ftp, client_socket);
    t_node *current_node = client->user->dir;
    bool first = true;

    (void)arg;
    while (current_node != NULL) {
        if (!first && strcmp(cwd, "/") != 0) {
            strcat(cwd, "/");
        }
        strcat(cwd, current_node->data);
        current_node = current_node->next;
        first = false;
    }
    snprintf(message, sizeof(message), "250 \"%s\".\r\n", cwd);
    send_to_socket(ftp, message, client_socket);
}

static bool check_directory_exists(char *new_dir)
{
    struct stat st = {0};

    if (stat(new_dir, &st) == -1) {
        return false;
    }
    return true;
}

static bool verify_dir(t_ftp **ftp, char *dest, int *client_socket)
{
    char *pwd = get_pwd(ftp, client_socket);
    char *new_dir = malloc(strlen(pwd) + strlen(dest) + 2);
    bool directory_exists;

    if (new_dir == NULL) {
        free(pwd);
        return false;
    }
    sprintf(new_dir, "%s/%s", pwd, dest);
    directory_exists = check_directory_exists(new_dir);
    free(pwd);
    free(new_dir);
    return directory_exists;
}

static bool special_case(t_ftp **ftp, char **arg, t_client *client)
{
    if (strcmp(arg[1], "..") == 0) {
        cdup(ftp, arg, &client->socket);
        return true;
    }
    if (arg[1][0] == '.') {
        send_to_socket(ftp, C250, &client->socket);
        return true;
    }
    if (arg[1][0] == '/') {
        delete_list(&client->user->dir);
        client->user->dir = create_node((*ftp)->server_home);
        send_to_socket(ftp, C250, &client->socket);
        return true;
    }
    return false;
}

void cwd(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);

    if (arg == NULL || arg[1] == NULL) {
        send_to_socket(ftp, C501, client_socket);
        return;
    }
    if (special_case(ftp, arg, client))
        return;
    if (!verify_dir(ftp, arg[1], client_socket)) {
        send_to_socket(ftp, C550, client_socket);
        return;
    }
    insert_node(&client->user->dir, arg[1]);
    send_to_socket(ftp, C250, client_socket);
}

void cdup(t_ftp **ftp, char **arg, int *client_socket)
{
    t_client *client = get_client(ftp, client_socket);
    t_node *last_node;

    (void)arg;
    if (client->user->dir->next == NULL) {
        send_to_socket(ftp, C550, client_socket);
        return;
    }
    last_node = get_last(client->user->dir);
    delete_node(&client->user->dir, last_node);
    send_to_socket(ftp, C250, client_socket);
}
