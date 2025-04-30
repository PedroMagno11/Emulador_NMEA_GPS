//
// Created by pedro on 29/04/2025.
//
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