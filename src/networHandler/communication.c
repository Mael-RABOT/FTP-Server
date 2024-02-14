/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** communication.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../include/protoype.h"

int send_to_socket(t_ftp **ftp, const char *data)
{
    char *buffer_data;

    cb_push(&(*ftp)->cb_write, data);
    buffer_data = get_command(&(*ftp)->cb_write);
    if (buffer_data == NULL)
        return -1;
    dprintf((*ftp)->client_socket, "%s", buffer_data);
    return 0;
}

int read_from_socket(t_ftp **ftp)
{
    char *buffer = malloc(BUFFER_SIZE);
    ssize_t bytes_read;

    if (buffer == NULL) {
        return -1;
    }
    bytes_read = read((*ftp)->client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        free(buffer);
        return -1;
    }
    buffer[bytes_read] = '\0';
    cb_push(&(*ftp)->cb_read, buffer);
    free(buffer);
    return 0;
}
