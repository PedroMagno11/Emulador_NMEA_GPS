#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include "web_server.h"

#include "gps.h"
#include "rede_util.h"
#include "util.h"

#pragma comment(lib, "Ws2_32.lib")

SOCKET criarSocketServidorWeb(int porta) {
    SOCKET servidor;
    struct sockaddr_in endereco_servidor;

    if((servidor = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Erro ao inicializar o servidor. Código: %d\n", WSAGetLastError());
        return INVALID_SOCKET;
    }

    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_addr.s_addr = INADDR_ANY;
    endereco_servidor.sin_port = htons(porta);

    bind(servidor, (struct sockaddr*)&endereco_servidor, sizeof(endereco_servidor));
    listen(servidor, 10);

    return servidor;
}

void responderRequisicaoJSON(SOCKET client, t_posicao posicao, char *sentenca) {

    // Remove \n, \r se existirem no final da sentença
    char *sentencaSemClrf = sentenca;
    remover_clrf(sentencaSemClrf);

    char json[1024];
    snprintf(json, sizeof(json),
    "{ \"mensagem\": \"%s\",\"latitude\": %.6f,\"longitude\": %.6f }",
        sentencaSemClrf, posicao.latitude, posicao.longitude
        );

    char response[2048];
    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Methods: GET, OPTIONS\r\n"
        "Access-Control-Allow-Headers: Content-Type\r\n"
        "Referrer-Policy: strict-origin-when-cross-origin\r\n"
        "Content-Length: %d\r\n"
        "\r\n"
        "%s",
        (int)strlen(json), json
    );

    send(client, response, (int)strlen(response), 0);
}

void responderOptionsCORS(SOCKET client) {
    const char *optionsResponse =
        "HTTP/1.1 204 No Content\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Methods: GET, OPTIONS\r\n"
        "Access-Control-Allow-Headers: Content-Type\r\n"
        "Referrer-Policy: strict-origin-when-cross-origin\r\n"
        "Content-Length: 0\r\n"
        "\r\n";
    send(client, optionsResponse, (int)strlen(optionsResponse), 0);
}

void tratarCliente(SOCKET client, t_posicao posicao, char *sentenca) {
    char request[1024] = {0};
    recv(client, request, sizeof(request), 0);

    if (strncmp(request, "GET / ", 6) == 0) {
        responderRequisicaoJSON(client, posicao, sentenca);
    } else if (strncmp(request, "OPTIONS", 7) == 0) {
        responderOptionsCORS(client);
    }

    closesocket(client);
}

int executarServidorWeb(int porta, t_posicao posicao, char *sentenca) {
    if (inicializarWinsock() != 0) {
        printf("Erro ao iniciar Winsock\n");
        return -1;
    }

    SOCKET server = criarSocketServidorWeb(porta);
    if (server == INVALID_SOCKET) {
        printf("Erro ao criar socket servidor\n");
        WSACleanup();
        return -1;
    }

    printf("Servidor escutando em http://localhost:%d/\n", porta);

    while (1) {
        SOCKET client = accept(server, NULL, NULL);
        if (client == INVALID_SOCKET) {
            printf("Erro ao aceitar conexão\n");
            continue;
        }

        tratarCliente(client, posicao, sentenca);
    }

    closesocket(server);
    WSACleanup();
    return 0;
}