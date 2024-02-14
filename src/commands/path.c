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

void pwd(t_ftp **ftp, char **arg)
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
    send_to_socket(ftp, message);
}

static char *construct_path(t_ftp **ftp, char **arg)
{
    char *new_dir;
    t_node *current_node = (*ftp)->user->dir;
    int total_length = strlen((*ftp)->user->home);

    for (; current_node != NULL; current_node = current_node->next)
        total_length += strlen(current_node->data) + 1;
    total_length += strlen(arg[1]) + 2;
    new_dir = malloc(total_length);
    strcpy(new_dir, (*ftp)->user->home);
    for (current_node = (*ftp)->user->dir; current_node != NULL;
            current_node = current_node->next) {
        if (strcmp(new_dir, "/") != 0)
            strcat(new_dir, "/");
        strcat(new_dir, current_node->data);
    }
    strcat(strcat(new_dir, "/"), arg[1]);
    return new_dir;
}

static bool check_directory_exists(char *new_dir)
{
    struct stat st = {0};

    if (stat(new_dir, &st) == -1) {
        free(new_dir);
        return false;
    }
    free(new_dir);
    return true;
}

static bool verify_dir(t_ftp **ftp, char **arg)
{
    char *new_dir = construct_path(ftp, arg);

    return check_directory_exists(new_dir);
}

void cwd(t_ftp **ftp, char **arg)
{
    if (arg == NULL || arg[1] == NULL) {
        send_to_socket(ftp, C501);
        return;
    }
    if (strcmp(arg[1], "..") == 0) {
        cdup(ftp, arg);
        return;
    }
    if (!verify_dir(ftp, arg)) {
        send_to_socket(ftp, C550);
        return;
    }
    insert_node(&(*ftp)->user->dir, arg[1]);
    send_to_socket(ftp, C250);
}

void cdup(t_ftp **ftp, char **arg)
{
    t_node *last_node;

    (void)arg;
    if ((*ftp)->user->dir->next == NULL) {
        send_to_socket(ftp, C550);
        return;
    }
    last_node = get_last((*ftp)->user->dir);
    delete_node(&(*ftp)->user->dir, last_node);
    send_to_socket(ftp, C250);
}
