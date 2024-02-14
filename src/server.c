/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** server.c
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#include "../include/protoype.h"

static void add_new_socket_to_client_sockets(
    int *client_socket, int new_socket)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_socket[i] == 0) {
            client_socket[i] = new_socket;
            break;
        }
    }
}

static void handle_new_connection(t_ftp **ftp, int **client_socket)
{
    int new_socket;
    socklen_t addrlen = sizeof((*ftp)->server_addr);

    if (FD_ISSET((*ftp)->server_socket, &(*ftp)->read_fds)) {
        new_socket = accept((*ftp)->server_socket,
                            (struct sockaddr *)(*ftp)->server_addr, &addrlen);
        if (new_socket < 0)
            return;
        add_new_socket_to_client_sockets(*client_socket, new_socket);
        send_to_socket(ftp, C220, &new_socket);
    }
}

static void handle_buffer(t_ftp **ftp, int i, int **client_socket)
{
    int sd;
    int bytes_read;
    char buffer[BUFFER_SIZE];

    sd = (*client_socket)[i];
    if (FD_ISSET(sd, &(*ftp)->read_fds)) {
        bytes_read = read(sd, buffer, BUFFER_SIZE - 1);
        if (bytes_read == 0) {
            close(sd);
            (*client_socket)[i] = 0;
        }
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            handle_command(ftp, buffer, &sd);
        }
    }
}

static void check_connection(t_ftp **ftp, int **client_socket)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        handle_buffer(ftp, i, client_socket);
    }
}

static void iteration(t_ftp **ftp, int *client_socket)
{
    struct timeval timeout = {TIMEOUT_SEC, TIMEOUT_USEC};
    int max_sd = (*ftp)->server_socket;
    int sd;

    FD_ZERO(&(*ftp)->read_fds);
    FD_SET((*ftp)->server_socket, &(*ftp)->read_fds);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        sd = client_socket[i];
        if (sd > 0)
            FD_SET(sd, &(*ftp)->read_fds);
        if (sd > max_sd)
            max_sd = sd;
    }
    select(max_sd + 1, &(*ftp)->read_fds, NULL, NULL, &timeout);
    handle_new_connection(ftp, &client_socket);
    check_connection(ftp, &client_socket);
}

static int check_stdin_for_eof(void)
{
    char buffer[2];

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    if (read(STDIN_FILENO, buffer, 1) == 0) {
        return 1;
    }
    return 0;
}

void main_loop(t_ftp **ftp)
{
    int client_socket[MAX_CLIENTS];

    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_socket[i] = 0;
    }
    while ((*ftp)->is_running) {
        if (check_stdin_for_eof()) {
            (*ftp)->is_running = false;
            break;
        }
        iteration(ftp, client_socket);
    }
}
