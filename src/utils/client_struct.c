/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** client_struct.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../../include/protoype.h"

static t_user *init_user(char *home)
{
    t_user *new_user = malloc(sizeof(t_user));

    if (new_user == NULL) {
        return NULL;
    }
    new_user->home = strdup(home);
    if (new_user->home == NULL) {
        return NULL;
    }
    new_user->username = NULL;
    new_user->password = NULL;
    new_user->permission = USER;
    new_user->is_logged = False;
    new_user->dir = create_node(home);
    if (new_user->dir == NULL) {
        return NULL;
    }
    return new_user;
}

int add_client(t_ftp **ftp, int *client_socket)
{
    t_client *new_client = malloc(sizeof(t_client));

    if (new_client == NULL) {
        return -1;
    }
    new_client->user = init_user((*ftp)->server_home);
    new_client->socket = *client_socket;
    new_client->cb_write = NULL;
    new_client->cb_read = NULL;
    new_client->mode = None;
    (*ftp)->clients[(*ftp)->nb_clients] = new_client;
    (*ftp)->nb_clients++;
    return 0;
}

static void free_client(t_client *client)
{
    free(client->cb_write);
    free(client->cb_read);
    delete_list(&client->user->dir);
    free(client->user->home);
    free(client->user->username);
    free(client->user->password);
    free(client->user);
    free(client);
}

void remove_client(t_ftp **ftp, int *client_socket)
{
    for (int i = 0; i < (*ftp)->nb_clients; i++) {
        if ((*ftp)->clients[i]
            && (*ftp)->clients[i]->socket == *client_socket) {
            free_client((*ftp)->clients[i]);
            (*ftp)->clients[i] = NULL;
            (*ftp)->nb_clients--;
            close(*client_socket);
            break;
        }
    }
}

void clear_clients(t_ftp **ftp)
{
    for (int i = 0; i < (*ftp)->nb_clients; i++) {
        free_client((*ftp)->clients[i]);
        (*ftp)->clients[i] = NULL;
    }
    (*ftp)->nb_clients = 0;
}

t_client *get_client(t_ftp **ftp, int *client_socket)
{
    for (int i = 0; i < (*ftp)->nb_clients; i++) {
        if ((*ftp)->clients[i]
            && (*ftp)->clients[i]->socket == *client_socket) {
            return (*ftp)->clients[i];
        }
    }
    return NULL;
}
