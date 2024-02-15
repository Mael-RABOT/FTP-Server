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
#include <fcntl.h>

#include "../include/protoype.h"

static void handle_new_connection(t_ftp **ftp)
{
    int new_socket;
    socklen_t addrlen = sizeof((*ftp)->server_addr);

    if (FD_ISSET((*ftp)->server_socket, &(*ftp)->read_fds)) {
        new_socket = accept((*ftp)->server_socket,
                            (struct sockaddr *)(*ftp)->server_addr, &addrlen);
        if (new_socket < 0)
            return;
        if (add_client(ftp, &new_socket) < 0) {
            close(new_socket);
            return;
        }
        send_to_socket(ftp, C220, &new_socket);
    }
}

static void handle_buffer(t_ftp **ftp, int i)
{
    int bytes_read;
    char buffer[BUFFER_SIZE];

    if (FD_ISSET((*ftp)->clients[i]->socket, &(*ftp)->read_fds)) {
        bytes_read = read((*ftp)->clients[i]->socket, buffer, BUFFER_SIZE - 1);
        if (bytes_read == 0) {
            remove_client(ftp, &(*ftp)->clients[i]->socket);
            return;
        }
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            handle_command(ftp, buffer, &(*ftp)->clients[i]->socket);
        }
    }
}

static void check_connection(t_ftp **ftp)
{
    for (int i = 0; i < (*ftp)->nb_clients; i++) {
        handle_buffer(ftp, i);
    }
}

static void iteration(t_ftp **ftp)
{
    struct timeval timeout = {TIMEOUT_SEC, TIMEOUT_USEC};
    int max_sd = (*ftp)->server_socket;

    FD_ZERO(&(*ftp)->read_fds);
    FD_SET((*ftp)->server_socket, &(*ftp)->read_fds);
    for (int i = 0; i < (*ftp)->nb_clients; i++) {
        if ((*ftp)->clients[i]->socket > 0)
            FD_SET((*ftp)->clients[i]->socket, &(*ftp)->read_fds);
        if ((*ftp)->clients[i]->socket > max_sd)
            max_sd = (*ftp)->clients[i]->socket;
    }
    select(max_sd + 1, &(*ftp)->read_fds, NULL, NULL, &timeout);
    handle_new_connection(ftp);
    check_connection(ftp);
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
    while ((*ftp)->is_running) {
        if (check_stdin_for_eof()) {
            (*ftp)->is_running = false;
            break;
        }
        iteration(ftp);
    }
}
