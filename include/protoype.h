/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** protoype.h
*/

#pragma once

#include "types.h"

int init_ftp(char **av, t_ftp **ftp);

int init_socket(t_ftp **ftp);
int accept_socket(t_ftp **ftp);

void display_help(void);

int send_to_socket(t_ftp **ftp, const char *data);
int read_from_socket(t_ftp **ftp);

void handle_command(t_ftp **ftp, char *command);

void user(t_ftp **ftp, char **arg);
void pass(t_ftp **ftp, char **arg);
void quit(t_ftp **ftp, char **arg);
void pwd(t_ftp **ftp, char **arg);

t_login *parse_file(const char *filename);
bool check_user(t_ftp **ftp);
char *xor_cipher(char *input);

t_circular_buffer *cb_init(int size);
void cb_free(t_circular_buffer **cb);
void cb_push(t_circular_buffer **cb, const char *str);
char *get_command(t_circular_buffer **cb);

char **str_to_word_array(char *str);
int array_len(char **array);

t_node* create_node(char *data);
void insert_node(t_node **head, char *data);
void delete_node(t_node **head, t_node *node_to_delete);
void delete_list(t_node **head);
t_node *get_last(t_node *head);
