//
// Created by pedro on 29/04/2025.
//
#include "rede_util.h"

#include <stdio.h>
#include <winsock2.h>

int inicializarWinsock(void) {
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Erro ao inicializar o Winsock. Código: %d\n", WSAGetLastError());
        return -1;
    }
    return 0;
}