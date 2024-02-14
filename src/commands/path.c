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

char *get_pwd(t_ftp **ftp)
{
    char *cwd = malloc(1000);
    t_node *current_node = (*ftp)->user->dir;
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
    t_node *current_node = (*ftp)->user->dir;
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
    snprintf(message, sizeof(message), "257 \"%s\" created.\r\n", cwd);
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

static bool verify_dir(t_ftp **ftp, char *dest)
{
    char *pwd = get_pwd(ftp);
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

void cwd(t_ftp **ftp, char **arg, int *client_socket)
{
    if (arg == NULL || arg[1] == NULL) {
        send_to_socket(ftp, C501, client_socket);
        return;
    }
    if (strcmp(arg[1], "..") == 0) {
        cdup(ftp, arg, client_socket);
        return;
    }
    if (!verify_dir(ftp, arg[1])) {
        send_to_socket(ftp, C550, client_socket);
        return;
    }
    insert_node(&(*ftp)->user->dir, arg[1]);
    send_to_socket(ftp, C250, client_socket);
}

void cdup(t_ftp **ftp, char **arg, int *client_socket)
{
    t_node *last_node;

    (void)arg;
    if ((*ftp)->user->dir->next == NULL) {
        send_to_socket(ftp, C550, client_socket);
        return;
    }
    last_node = get_last((*ftp)->user->dir);
    delete_node(&(*ftp)->user->dir, last_node);
    send_to_socket(ftp, C250, client_socket);
}
