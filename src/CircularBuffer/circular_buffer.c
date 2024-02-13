/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** circular_buffer.c
*/

#include <stdlib.h>
#include <string.h>

#include "../../include/types.h"

#include <stdio.h>

t_circular_buffer *cb_init(int size)
{
    t_circular_buffer *cb;

    if (size <= 0) {
        return NULL;
    }
    cb = malloc(sizeof(t_circular_buffer));
    cb->buffer = memset(malloc(size), 0, size);
    cb->size = size;
    cb->write_head = 0;
    cb->read_head = 0;
    cb->tail = 0;
    if (cb->size == 0) {
        printf("Error: malloc failed\n");
        return NULL;
    }
    return cb;
}

void cb_free(t_circular_buffer **cb)
{
    free((*cb)->buffer);
    free((*cb));
}

void cb_push(t_circular_buffer **cb, const char *str)
{
    while (*str) {
        (*cb)->buffer[(*cb)->write_head] = *str;
        (*cb)->write_head = ((*cb)->write_head + 1) % (*cb)->size;
        if ((*cb)->write_head == (*cb)->tail) {
            (*cb)->tail = ((*cb)->tail + 1) % (*cb)->size;
        }
        str++;
    }
}

char *get_command(t_circular_buffer **cb)
{
    int current_position = (*cb)->read_head;
    char *command = malloc((*cb)->size + 1);
    int i = 0;

    if (command == NULL) {
        return NULL;
    }
    while (current_position != (*cb)->write_head) {
        command[i] = (*cb)->buffer[current_position];
        if (i > 0 && command[i - 1] == '\r' && command[i] == '\n') {
            command[i + 1] = '\0';
            (*cb)->read_head = (current_position + 1) % (*cb)->size;
            return command;
        }
        current_position = (current_position + 1) % (*cb)->size;
        i++;
    }
    free(command);
    return NULL;
}
