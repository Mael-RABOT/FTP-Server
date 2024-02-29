/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** types.h
*/

#pragma once

#include <sys/select.h>
#include <netinet/in.h>

#define BUFFER_SIZE 4096

#define MAX_LINE_LENGTH 256
#define MAX_LOGINS 100
#define MAX_CLIENTS 30

#define TIMEOUT_SEC 1
#define TIMEOUT_USEC 0

#define C150 "150 File status okay, about to open data connection.\r\n"
#define C200 "200 Command okay.\r\n"
#define C230 "230 User logged in, proceed.\r\n"
#define C220 "220 Service ready for new user.\r\n"
#define C221 "221 Service closing control connection.\r\n"
#define C226 "226 Closing data connection." C226END
#define C226END " Requested file action successful.\r\n"
#define C250 "250 Requested file action okay, completed.\r\n"
#define C331 "331 User name okay, need password.\r\n"
#define C332 "332 Need account for login.\r\n"
#define C425 "425 Can't open data connection.\r\n"
#define C425MODE "425 Use PORT or PASV first.\r\n"
#define C451 "451 Requested action aborted. Local error in processing.\r\n"
#define C500 "500 Syntax error, command unrecognized.\r\n"
#define C501 "501 Syntax error in parameters or arguments.\r\n"
#define C502 "502 Command not implemented.\r\n"
#define C530 "530 Not logged in.\r\n"
#define C550 "550 Requested action not taken.\r\n"

#define C214 "214 Help message.\r\n"
#define HELP H1 H2 H3 H4 H5 H6 H7 H8 H9 H10 H11 H12 LABEL H13 H14 H15
#define H1 "\tThe following commands are recognized:\n"
#define H2A "\tUSER <SP> <username> <CRLF>   : "
#define H2B "Specify user for authentication.\n"
#define H2 H2A H2B
#define H3A "\tPASS <SP> <password> <CRLF>   : "
#define H3B "Specify password for authentication.\n"
#define H3 H3A H3B
#define H4A "\tCWD  <SP> <pathname> <CRLF>   : "
#define H4B "Change working directory.\n"
#define H4 H4A H4B
#define H5A "\tCDUP <CRLF>                   : "
#define H5B "Change working directory to parent directory.\n"
#define H5 H5A H5B
#define H6 "\tQUIT <CRLF>                   : Disconnection.\n"
#define H7A "\tDELE <SP> <pathname> <CRLF>   : "
#define H7B "Delete file on the server.\n"
#define H7 H7A H7B
#define H8A "\tPWD  <CRLF>                   : "
#define H8B "Print working directory.\n"
#define H8 H8A H8B
#define H9A "\tPASV <CRLF>                   : "
#define H9B "Enable \"passive\" mode for data transfer.\n"
#define H9 H9A H9B
#define H10A "\tPORT <SP> <host-port> <CRLF>  : "
#define H10B "Enable \"active\" mode for data transfer.\n"
#define H10 H10A H10B
#define H11A "\tHELP [<SP> <string>] <CRLF>   : "
#define H11B "List available commands.\n"
#define H11 H11A H11B
#define H12 "\tNOOP <CRLF>                   : Do nothing.\n"
#define LABEL "\t(the following are commands using data transfer)\n"
#define H13A "\tRETR <SP> <pathname> <CRLF>   : "
#define H13B "Download file from server to client.\n"
#define H13 H13A H13B
#define H14A "\tSTOR <SP> <pathname> <CRLF>   : "
#define H14B "Upload file from client to server.\n"
#define H14 H14A H14B
#define H15A "\tLIST [<SP> <pathname>] <CRLF> : "
#define H15B "List files in the current working directory.\r\n"
#define H15 H15A H15B

typedef enum e_bool {
    false = 0,
    true = 1
} bool;

typedef enum e_mode {
    None = -1,
    Active = 0,
    Passive = 1
} t_mode;

typedef enum e_command_checker {
    command_not_found = -1,
    login_failed = 0,
    login_success = 1,
} t_command_checker;

typedef enum e_permission {
    USER = 0,
    ADMIN = 1,
} t_permission;

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
    t_permission permission;
    bool is_logged;
    t_node *dir;
    char *home;
} t_user;

typedef struct s_login {
    char *user;
    char *pass;
    t_permission permission;
} t_login;

typedef struct s_port {
    int ip[4];
    int port[4];
} t_port;

typedef struct s_pasv {
    int port;
} t_pasv;

typedef struct s_client {
    t_mode mode;
    int socket;
    int data_socket;
    struct sockaddr_in act_addr;
    t_user *user;
    t_circular_buffer *cb_write;
    t_circular_buffer *cb_read;
    t_port *port;
    t_pasv pasv;
} t_client;

typedef struct s_ftp {
    int port;
    int server_socket;
    t_login *login_array;
    t_client **clients;
    int nb_clients;
    char *server_home;
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
    bool need_login;
    t_permission permission;
    bool need_mode;
} command_map;
