/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** circular_buffer.c
*/

#include <stdlib.h>
#include <string.h>

#include "../../include/types.h"

t_circular_buffer *cb_init(int size)
{
    t_circular_buffer *cb = malloc(sizeof(t_circular_buffer));

    cb->buffer = malloc(size);
    cb->size = size;
    cb->head = 0;
    cb->tail = 0;
    return cb;
}

void cb_free(t_circular_buffer *cb)
{
    free(cb->buffer);
    free(cb);
}

void cb_push(t_circular_buffer *cb, const char *str)
{
    while (*str) {
        cb->buffer[cb->head] = *str;
        cb->head = (cb->head + 1) % cb->size;
        if (cb->head == cb->tail) {
            cb->tail = (cb->tail + 1) % cb->size;
        }
        str++;
    }
}

char *get_command(char *buffer)
{
    char *command_end = strstr(buffer, "\r\n");
    int command_length;
    char *command;

    if (command_end == NULL) {
        return NULL;
    }
    command_length = command_end - buffer + 2;
    command = malloc(command_length + 1);
    if (command == NULL) {
        return NULL;
    }
    strncpy(command, buffer, command_length);
    command[command_length] = '\0';
    return command;
}
