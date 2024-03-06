/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** big_free.c
*/

#include <stdlib.h>

#include "../../include/protoype.h"

void big_free(t_ftp **ftp, int exit_value)
{
    free((*ftp)->server_addr);
    free((*ftp)->server_home);
    if ((*ftp)->login_array != NULL) {
        for (int i = 0; (*ftp)->login_array[i].user != NULL; i++) {
            free((*ftp)->login_array[i].user);
            free((*ftp)->login_array[i].pass);
        }
        free((*ftp)->login_array);
    }
    free((*ftp)->cb_read->buffer);
    free((*ftp)->cb_read);
    free((*ftp)->cb_write->buffer);
    free((*ftp)->cb_write);
    clear_clients(ftp);
    free((*ftp)->clients);
    free((*ftp));
    exit(exit_value);
}
