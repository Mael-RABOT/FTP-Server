/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** help.c
*/

#include <stdio.h>

void display_help(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which "
        "the server socket listens\n");
    printf("\tpath is the path to the home "
        "directory for the Anonymous user\n");
}
