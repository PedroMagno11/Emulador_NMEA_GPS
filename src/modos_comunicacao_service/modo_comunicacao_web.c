//
// Created by pedro on 24/07/2025.
//

#include "modo_comunicacao_web.h"

#include <stdio.h>

#include "web_server.h"

void executar_modo_comunicacao_web(t_posicao posicao){
    int portaDoServidorWeb;
    getchar();
    printf("Porta:");
    scanf("%d", &portaDoServidorWeb);
    getchar();
    printf("\nIniciando servidor web");
    char sentenca[256];

    // gera sentença NMEA
    gerarSentencaGPGGA(posicao,sentenca,gerarQuantidadeSatelites(),gerarAltitude(),gerarSeparacaoGeoide());
    executarServidorWeb(portaDoServidorWeb,posicao,sentenca);
}
