#include <stdio.h>
#include "front.h"
#include "gps.h"
#include "modo_comunicacao_mqtt.h"
#include "modo_comunicacao_serial.h"
#include "modo_comunicacao_web.h"

void iniciarFrontEnd();

int main(void) {
    iniciarFrontEnd();

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
                executar_modo_comunicacao_serial(posicao);
            break;

            case 2:
                executar_modo_comunicacao_web(posicao);
            break;

            case 3:
                executar_modo_comunicacao_web(posicao);
            break;

            case 4:
                executar_modo_comunicacao_mqtt(posicao);
                break;

            case 5:
                printf("Encerrando...");
                break;
            default:
                printf("\nOpcao invalida");
    }

}

void iniciarFrontEnd() {
    mostrarCabecalho();
    mostrarDescricao();
    mostrarMenu();
}