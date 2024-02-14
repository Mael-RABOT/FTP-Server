/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** str_to_word_array.c
*/

#include <stdlib.h>
#include <string.h>

static int count_words(char *str)
{
    int i = 0;
    int words = 1;

    for (i = 0; str[i]; i++)
        if (str[i] == ' ' && str[i + 1] != ' ')
            words++;
    return words;
}

static char **split_into_words(char *str, int words)
{
    int i = 0;
    char **array = malloc((words + 1) * sizeof(char *));
    char *token;

    if (!array)
        return NULL;
    token = strtok(str, " ");
    while (token) {
        array[i] = malloc(strlen(token) + 1);
        if (!array[i])
            return NULL;
        strcpy(array[i], token);
        token = strtok(NULL, " ");
        i++;
    }
    array[i] = NULL;
    return array;
}

static void normalize(char ***array)
{
    if (!(*array))
        return;
    for (int i = 0; (*array)[i]; i++) {
        for (int j = 0; (*array)[i][j]; j++)
            (*array)[i][j] = ((*array)[i][j] == '\n') ? '\0' : (*array)[i][j];
    }
    for (int i = 0; (*array)[i]; i++) {
        for (int j = 0; (*array)[i][j]; j++)
            (*array)[i][j] = ((*array)[i][j] == '\r') ? '\0' : (*array)[i][j];
    }
}

char **str_to_word_array(char *str)
{
    int words;
    char **array;

    if (!str)
        return NULL;
    words = count_words(str);
    array = split_into_words(str, words);
    normalize(&array);
    return array;
}

int array_len(char **array)
{
    int i = 0;

    for (i = 0; array[i]; i++);
    return i;
}
