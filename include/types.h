/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** types.h
*/

#pragma once

#define BUFFER_SIZE 4096

#define MAX_LINE_LENGTH 256
#define MAX_LOGINS 100

#define C230 "230 User logged in, proceed.\r\n"
#define C220 "220 Service ready for new user.\r\n"
#define C221 "221 Service closing control connection.\r\n"
#define C331 "331 User name okay, need password.\r\n"
#define C332 "332 Need account for login.\r\n"
#define C500 "500 Syntax error, command unrecognized.\r\n"
#define C501 "501 Syntax error in parameters or arguments.\r\n"
#define C530 "530 Not logged in.\r\n"

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

typedef struct s_node {
    char *data;
    struct s_node *next;
    struct s_node *prev;
} t_node;

typedef struct s_user {
    char *username;
    char *password;
    bool is_logged;
    t_node *dir;
    char *home;
} t_user;

typedef struct s_login {
    char *user;
    char *pass;
} t_login;

typedef struct s_ftp {
    int port;
    t_user *user;
    int sockfd;
    int client_socket;
    t_login *login_array;
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
