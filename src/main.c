#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#include "comunicacao_serial.h"
#include "comunicacao_tcp.h"
#include "front.h"
#include "gps.h"
#include "rede_util.h"
#include "util.h"
#include "web_server.h"

int main(void) {

    mostrarCabecalho();
    mostrarDescricao();
    mostrarMenu();

    // Coleta a opção do menu
    int opcaoDoMenu;
    scanf("%d", &opcaoDoMenu);

    // Coleta a opção de especificação geográfica
    mostrarSolicitacaoDeEspecificacoesGeograficas();

    int opcaoDeEspecificacoesGeograficas;

    t_posicao posicao = {0.0, 0.0}; // Uma posição inicial padrão. lat:0.0, long:0.0
    scanf("%d", &opcaoDeEspecificacoesGeograficas);

    switch (opcaoDeEspecificacoesGeograficas) {
        case 1:
            printf("Informe latitude minima, latitude maxima, longitude minima e longitude maxima: (longMin,longMax,latMin,latMax)");
            double latMin,latMax,longMin,longMax;
            scanf("%lf,%lf,%lf,%lf", &latMin, &latMax, &longMin, &longMax);
            posicao = gerarPosicaoAleatoria(longMin,longMax,latMin,latMax);
            break;

        case 2:
            printf("Informe a latitude e longitude de uma posicao especifica: (latitude,longitude)");
            double latitude, longitude;
            scanf("%lf,%lf", &latitude, &longitude);
            posicao.latitude = latitude,
            posicao.longitude = longitude;
            break;

        default:
            printf("\nOpcao invalida");
    }

    switch (opcaoDoMenu) {
            case 1:
                getchar();
                printf("Porta Serial (\\\\.\\SERIAL): ");
                char portaSerial[10];
                fgets(portaSerial, 10, stdin);
                printf("%s\n", portaSerial);
                printf("Baud Rate: ");
                uint32_t baudRate;
                scanf("%u", &baudRate);
                char sentencaNmeaQueSeraEnviadaViaPortaSerial[256];
                gerarSentencaGPGGA(posicao, sentencaNmeaQueSeraEnviadaViaPortaSerial, gerarQuantidadeSatelites(), gerarAltitude(), gerarSeparacaoGeoide());

                while(1) {
                    printf("%s\n", sentencaNmeaQueSeraEnviadaViaPortaSerial);

                    // Muda o comportamento do terminal
                    if(_kbhit()) {
                        char caracterPressionado = _getch();
                        if(caracterPressionado == '\r') {
                            break;
                        }
                    }

                    if(escreverNaPortaSerial(portaSerial, sentencaNmeaQueSeraEnviadaViaPortaSerial) < 0) {
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
            break;

            case 2:
                char enderecoDoServidor[256];
                int porta;
                getchar(); // Consome o \n que ficou do scanf anterior
                printf("Ip do servidor:");
                fgets(enderecoDoServidor, sizeof(enderecoDoServidor), stdin);
                remover_clrf(enderecoDoServidor);
                printf("Porta:");
                scanf("%d", &porta);
                getchar();
                printf("\nIniciando conexão com o servidor: %s e porta: %d\n", enderecoDoServidor, porta);

                // Inicia o socket
                inicializarWinsock();
                SOCKET clientSocket = conectarAoServidor(enderecoDoServidor, porta);
                char sentencaNmea[256];

                // gera sentença NMEA
                gerarSentencaGPGGA(posicao,sentencaNmea,gerarQuantidadeSatelites(),gerarAltitude(),gerarSeparacaoGeoide());
                enviarSentenca(clientSocket, sentencaNmea);

                // recebe dados do servidor
                char recebido[200];
                receberDadosDoServidor(clientSocket, recebido, 200);
                // encerra conexão
                encerrarConexao(clientSocket);
            break;

            case 3:
                getchar();
                printf("Porta:");
                scanf("%d", &porta);
                getchar();
                printf("\nIniciando servidor web");
                char sentenca[256];

                // gera sentença NMEA
                gerarSentencaGPGGA(posicao,sentenca,gerarQuantidadeSatelites(),gerarAltitude(),gerarSeparacaoGeoide());
                executarServidorWeb(porta,posicao,sentenca);
            break;

            case 4:
                printf("Encerrando...");
                break;
            default:
                printf("\nOpcao invalida");
    }

}