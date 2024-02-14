/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** types.h
*/

#pragma once

#include <sys/select.h>

#define BUFFER_SIZE 4096

#define MAX_LINE_LENGTH 256
#define MAX_LOGINS 100
#define MAX_CLIENTS 30

#define TIMEOUT_SEC 1
#define TIMEOUT_USEC 0

#define C200 "200 Command okay.\r\n"
#define C230 "230 User logged in, proceed.\r\n"
#define C220 "220 Service ready for new user.\r\n"
#define C221 "221 Service closing control connection.\r\n"
#define C250 "250 Requested file action okay, completed.\r\n"
#define C331 "331 User name okay, need password.\r\n"
#define C332 "332 Need account for login.\r\n"
#define C500 "500 Syntax error, command unrecognized.\r\n"
#define C501 "501 Syntax error in parameters or arguments.\r\n"
#define C502 "502 Command not implemented.\r\n"
#define C530 "530 Not logged in.\r\n"
#define C550 "550 Requested action not taken.\r\n"

#define C214 "214 Help message.\n" HELP
#define HELP H1 H2 H3 H4 H5 H6 H7 H8 H9 H10 H11 H12 LABEL H13 H14 H15
#define H1 "\tThe following commands are recognized:\n"
#define H2 "\tUSER <SP> <username> <CRLF>   : Specify user for authentication.\n"
#define H3 "\tPASS <SP> <password> <CRLF>   : Specify password for authentication.\n"
#define H4 "\tCWD  <SP> <pathname> <CRLF>   : Change working directory.\n"
#define H5 "\tCDUP <CRLF>                   : Change working directory to parent directory.\n"
#define H6 "\tQUIT <CRLF>                   : Disconnection.\n"
#define H7 "\tDELE <SP> <pathname> <CRLF>   : Delete file on the server.\n"
#define H8 "\tPWD  <CRLF>                   : Print working directory.\n"
#define H9 "\tPASV <CRLF>                   : Enable \"passive\" mode for data transfer.\n"
#define H10 "\tPORT <SP> <host-port> <CRLF>  : Enable \"active\" mode for data transfer.\n"
#define H11 "\tHELP [<SP> <string>] <CRLF>   : List available commands.\n"
#define H12 "\tNOOP <CRLF>                   : Do nothing.\n"
#define LABEL "\t(the following are commands using data transfer)\n"
#define H13 "\tRETR <SP> <pathname> <CRLF>   : Download file from server to client.\n"
#define H14 "\tSTOR <SP> <pathname> <CRLF>   : Upload file from client to server.\n"
#define H15 "\tLIST [<SP> <pathname>] <CRLF> : List files in the current working directory.\r\n"

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
    int server_socket;
    int client_socket;
    t_login *login_array;
    struct sockaddr_in *server_addr;
    t_circular_buffer *cb_write;
    t_circular_buffer *cb_read;
    bool is_running;
    fd_set read_fds;
} t_ftp;

typedef void (*func_ptr)(t_ftp **ftp, char **, int *client_socket);

typedef struct {
    char *command;
    func_ptr function;
} command_map;
