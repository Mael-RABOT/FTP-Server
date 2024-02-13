/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** types.h
*/

#pragma once

typedef struct s_circular_buffer {
    char *buffer;
    int head;
    int tail;
    int size;
} t_circular_buffer;

typedef struct s_ftp {
    int port;
    char *path;
    int sockfd;
    struct sockaddr_in *server_addr;
    t_circular_buffer *cb_write;
    t_circular_buffer *cb_read;
} t_ftp;
