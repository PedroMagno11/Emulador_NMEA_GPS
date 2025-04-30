//
// Created by pedro on 29/04/2025.
//

#ifndef COMUNICACAO_TCP_H
#define COMUNICACAO_TCP_H

#include <winsock2.h>

SOCKET conectarAoServidor(const char *ip_servidor, int porta);

int enviarSentenca(SOCKET socket, const char *sentenca);

int receberDadosDoServidor(SOCKET socket, char *buffer, int tamanhoBuffer);

void encerrarConexao(SOCKET socket);

#endif //COMUNICACAO_TCP_H
