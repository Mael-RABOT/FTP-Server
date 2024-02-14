/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** protoype.h
*/

#pragma once

#include "types.h"

int init_ftp(char **av, t_ftp **ftp);

void main_loop(t_ftp **ftp);

int init_server_socket(t_ftp **ftp);

void display_help(void);

int send_to_socket(t_ftp **ftp, const char *data, int *client_socket);
int read_from_socket(t_ftp **ftp, int *client_socket);

void handle_command(t_ftp **ftp, char *command, int *client_socket);

void user(t_ftp **ftp, char **arg, int *client_socket);
void pass(t_ftp **ftp, char **arg, int *client_socket);
void quit(t_ftp **ftp, char **arg, int *client_socket);
void pwd(t_ftp **ftp, char **arg, int *client_socket);
void cwd(t_ftp **ftp, char **arg, int *client_socket);
void cdup(t_ftp **ftp, char **arg, int *client_socket);
void noop(t_ftp **ftp, char **arg, int *client_socket);
void help(t_ftp **ftp, char **arg, int *client_socket);

t_login *parse_file(const char *filename);
bool check_user(t_ftp **ftp);
char *xor_cipher(char *input);

t_circular_buffer *cb_init(int size);
void cb_free(t_circular_buffer **cb);
void cb_push(t_circular_buffer **cb, const char *str);
char *get_command(t_circular_buffer **cb);

char **str_to_word_array(char *str);
int array_len(char **array);
void free_array(char **array);

t_node* create_node(char *data);
void insert_node(t_node **head, char *data);
void delete_node(t_node **head, t_node *node_to_delete);
void delete_list(t_node **head);
t_node *get_last(t_node *head);
