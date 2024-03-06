/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** main.c
*/

#include <string.h>
#include <dirent.h>

#include "../include/protoype.h"

t_bool check_path(char *path)
{
    DIR *dir = opendir(path);

    return (dir) ? True + 0 * closedir(dir) : False;
}

int main(int ac, char **av)
{
    t_ftp *ftp;
    int ret;

    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        display_help();
        return 0;
    }
    if (ac != 3)
        return 84;
    if (!check_path(av[2]))
        return 84;
    ret = init_ftp(av, &ftp);
    if (ret == 0)
        main_loop(&ftp);
    big_free(&ftp, (ret == 0 ? 0 : 84));
}
