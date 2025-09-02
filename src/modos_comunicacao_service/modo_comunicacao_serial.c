//
// Created by pedro on 24/07/2025.
//
#include "modo_comunicacao_serial.h"
#include <stdio.h>
#include <conio.h>
#include <util.h>

#include "comunicacao_serial.h"
#include "comunicacao_tcp.h"

int executar_modo_comunicacao_serial(t_posicao posicao) {

    getchar();
    printf("Porta Serial (\\\\.\\SERIAL): ");
    char portaSerial[10];
    fgets(portaSerial, 10, stdin);
    remover_clrf(portaSerial);
    printf("%s\n", portaSerial);
    printf("Baud Rate: ");
    uint32_t baudRate;
    scanf("%u", &baudRate);
    char sentencaNmeaQueSeraEnviadaViaPortaSerial[256];
    gerarSentencaGPGGA(posicao, sentencaNmeaQueSeraEnviadaViaPortaSerial, gerarQuantidadeSatelites(), gerarAltitude(), gerarSeparacaoGeoide());

    HANDLE portaSerialAberta = abrirPortaSerial(portaSerial, baudRate);

    while(1) {
        printf("%s\n", sentencaNmeaQueSeraEnviadaViaPortaSerial);

        // Muda o comportamento do terminal
        if(_kbhit()) {
            char caracterPressionado = _getch();
            if(caracterPressionado == '\r') {
                break;
            }
        }

        if(escreverNaPortaSerial(portaSerialAberta, sentencaNmeaQueSeraEnviadaViaPortaSerial) < 0) {
            CloseHandle(portaSerial);
            return 1;
        }

        Sleep(1000);
        char response[256];
        int bytesLidos = lerNaPortaSerial(portaSerial, response, sizeof(response));
        if (bytesLidos > 0) {
            printf("[+] -> Resposta do microcontrolador: %s\n", response);
        } else {
            printf("Nenhuma resposta recebida.\n");
        }
    }
    CloseHandle(portaSerial);
    return 0;
}
