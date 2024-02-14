/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** path.c
*/

#include <stdio.h>
#include <unistd.h>

#include "../../include/protoype.h"

void pwd(t_ftp **ftp, char **arg)
{
    char cwd[1000];
    char message[sizeof(cwd) + 24];

    (void)arg;
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        snprintf(message, sizeof(message), "257 \"%s\" created.\r\n", cwd);
        send_to_socket(ftp, message);
    } else {
        send_to_socket(ftp, C550);
    }
}
