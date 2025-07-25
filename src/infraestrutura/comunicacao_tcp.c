//
// Created by pedro on 29/04/2025.
//

#include <comunicacao_tcp.h>
#include <stdio.h>

SOCKET conectarAoServidor(const char *ip_servidor, int porta) {
    SOCKET sock;
    struct sockaddr_in endereco_servidor;

    // Cria o socket
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Erro ao criar socket. Código: %d\n", WSAGetLastError());
        return INVALID_SOCKET;
    }

    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_port = htons(porta);
    endereco_servidor.sin_addr.s_addr = inet_addr(ip_servidor);

    if(connect(sock, (struct sockaddr *)&endereco_servidor, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
        printf("Erro ao conectar. Código: %d\n", WSAGetLastError());
        closesocket(sock);
        return INVALID_SOCKET;
    }

    return sock;
}

int enviarSentenca(SOCKET socket, const char *sentenca) {
    return send(socket, sentenca, strlen(sentenca), 0);
}

int receberDadosDoServidor(SOCKET socket, char *buffer, int tamanhoBuffer) {
    return recv(socket, buffer, tamanhoBuffer, 0);
}

void encerrarConexao(SOCKET socket) {
    closesocket(socket);
    WSACleanup();
}