//
// Created by pedro on 24/07/2025.
//
#include "modo_comunicacao_tcp.h"

#include <stdio.h>

#include "comunicacao_tcp.h"
#include "rede_util.h"
#include "util.h"

void executar_modo_comunicacao_tcp(t_posicao posicao) {
    char enderecoDoServidor[256];
    int portaDoServidor;
    getchar(); // Consome o \n que ficou do scanf anterior
    printf("Ip do servidor:");
    fgets(enderecoDoServidor, sizeof(enderecoDoServidor), stdin);
    remover_clrf(enderecoDoServidor);
    printf("Porta:");
    scanf("%d", &portaDoServidor);
    getchar();
    printf("\nIniciando conexão com o servidor: %s e porta: %d\n", enderecoDoServidor, portaDoServidor);

    // Inicia o socket
    inicializarWinsock();
    SOCKET clientSocket = conectarAoServidor(enderecoDoServidor, portaDoServidor);
    char sentencaNmea[256];

    // gera sentença NMEA
    gerarSentencaGPGGA(posicao,sentencaNmea,gerarQuantidadeSatelites(),gerarAltitude(),gerarSeparacaoGeoide());
    enviarSentenca(clientSocket, sentencaNmea);

    // recebe dados do servidor
    char recebido[200];
    receberDadosDoServidor(clientSocket, recebido, 200);
    // encerra conexão
    encerrarConexao(clientSocket);
}
