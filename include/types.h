/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** types.h
*/

#pragma once

#define BUFFER_SIZE 4096

typedef enum e_bool {
    false = 0,
    true = 1
} bool;

typedef struct s_circular_buffer {
    char *buffer;
    int read_head;
    int write_head;
    int tail;
    int size;
} t_circular_buffer;

typedef struct s_user {
    char *username;
    char *password;
    bool is_logged;
    char *home;
} t_user;

typedef struct s_ftp {
    int port;
    t_user *user;
    int sockfd;
    int new_socket;
    struct sockaddr_in *server_addr;
    t_circular_buffer *cb_write;
    t_circular_buffer *cb_read;
    bool is_running;
} t_ftp;

typedef void (*func_ptr)(t_ftp **ftp, char **);

typedef struct {
    char *command;
    func_ptr function;
} command_map;
