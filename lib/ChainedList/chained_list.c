/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** chained_list.c
*/

#include <stdlib.h>
#include <string.h>

#include "../../include/types.h"

t_node* create_node(char *data)
{
    t_node *new_node = (t_node*)malloc(sizeof(t_node));

    new_node->data = strdup(data);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void insert_node(t_node **head, char *data)
{
    t_node *new_node = create_node(data);
    t_node *last;

    if (*head == NULL) {
        *head = new_node;
        return;
    }
    last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
    new_node->prev = last;
}

void delete_node(t_node **head, t_node *node_to_delete)
{
    if (*head == NULL || node_to_delete == NULL) {
        return;
    }
    if (*head == node_to_delete) {
        *head = node_to_delete->next;
    }
    if (node_to_delete->next != NULL) {
        node_to_delete->next->prev = node_to_delete->prev;
    }
    if (node_to_delete->prev != NULL) {
        node_to_delete->prev->next = node_to_delete->next;
    }
    free(node_to_delete->data);
    free(node_to_delete);
}

void delete_list(t_node **head)
{
    t_node *current_node = *head;
    t_node *next_node;

    while (current_node != NULL) {
        next_node = current_node->next;
        free(current_node->data);
        free(current_node);
        current_node = next_node;
    }
    *head = NULL;
}

t_node *get_last(t_node *head)
{
    t_node *last = head;

    while (last && last->next) {
        last = last->next;
    }
    return last;
}
