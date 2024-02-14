/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-mael.rabot
** File description:
** cypher.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *xor_cipher(char *input)
{
    int key = 42;
    int pos = 0;
    char *ciphered = malloc(strlen(input) * 3 + 1);

    if (ciphered == NULL) {
        return NULL;
    }
    for (unsigned int i = 0; i < strlen(input); i++) {
        pos += sprintf(&ciphered[pos], "%d", input[i] ^ key);
    }
    return ciphered;
}
