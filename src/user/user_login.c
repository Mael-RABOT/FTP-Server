/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** parse.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/protoype.h"

static FILE* open_file(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Failed to open file");
    }
    return file;
}

static t_login* allocate_login_array(void)
{
    t_login *login_array = malloc(MAX_LOGINS * sizeof(t_login));

    if (login_array == NULL) {
        perror("Failed to allocate memory");
    }
    return login_array;
}

static void parse_line(char *line, t_login *login_array, int i)
{
    char user[MAX_LINE_LENGTH] = "";
    char pass[MAX_LINE_LENGTH] = "";
    int ret = sscanf(line, "%[^:]:%s", user, pass);

    if (ret >= 1) {
        login_array[i].user = strdup(user);
        if (ret == 2) {
            login_array[i].pass = strdup(pass);
        } else {
            login_array[i].pass = strdup("");
        }
    } else {
        login_array[i].user = strdup("");
        login_array[i].pass = strdup("");
    }
}

static void end_init(t_login **login_array, FILE **file, int pos)
{
    (*login_array)[pos].user = NULL;
    (*login_array)[pos].pass = NULL;
    fclose(*file);
}

t_login *parse_file(const char *filename)
{
    FILE *file = open_file(filename);
    t_login *login_array;
    char line[MAX_LINE_LENGTH];
    int i = 0;

    if (file == NULL)
        return NULL;
    login_array = allocate_login_array();
    if (login_array == NULL) {
        fclose(file);
        return NULL;
    }
    while (fgets(line, sizeof(line), file)) {
        if (i >= MAX_LOGINS)
            break;
        parse_line(line, login_array, i);
        i++;
    }
    end_init(&login_array, &file, i);
    return login_array;
}

bool check_user(t_ftp **ftp, t_client *client)
{
    int i = 0;
    char *encrypted_pass = xor_cipher(client->user->password);

    while ((*ftp)->login_array[i].user != NULL) {
        if (strcmp((*ftp)->login_array[i].user, client->user->username) == 0
            && strcmp((*ftp)->login_array[i].pass, "") == 0)
            return true;
        if (strcmp((*ftp)->login_array[i].pass, encrypted_pass) == 0) {
            free(encrypted_pass);
            return true;
        }
        i++;
    }
    free(encrypted_pass);
    return false;
}
