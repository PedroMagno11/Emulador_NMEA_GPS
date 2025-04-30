//
// Created by pedro on 29/04/2025.
//

#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <winsock2.h>

#include "gps.h"

SOCKET criarSocketServidorWeb(int porta);
void responderRequisicaoJSON(SOCKET client, t_posicao posicao, char *sentenca);
void responderOptionsCORS(SOCKET client);
void tratarCliente(SOCKET cliente, t_posicao posicao, char *sentenca);
int executarServidorWeb(int porta, t_posicao posicao, char *sentenca);
#endif //WEB_SERVER_H
