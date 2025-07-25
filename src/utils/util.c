//
// Created by pedro on 29/04/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <util.h>
void remover_clrf(char *str) {
    char *aux = str;
    while (*aux) {
        if(*aux == '\r' || *aux == '\n') {
            *aux = '\0';
            break;
        }
        aux++;
    }
}

char *from_int_to_string(int number) {
    int length = snprintf(NULL, 0, "%d", number);
    if (length < 0) {
        return NULL;
    }
    char *str = malloc(length + 1);
    if(!str) return NULL;

    sprintf(str, "%d", number);

    return str;
}