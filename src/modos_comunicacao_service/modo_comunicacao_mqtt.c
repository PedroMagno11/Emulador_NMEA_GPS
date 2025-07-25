#include <stdio.h>

#include "comunicacao_mqtt.h"
#include "modo_comunicacao_mqtt.h"
#include <conio.h>
#include "comunicacao_tcp.h"
#include "gps.h"
#include "util.h"

void executar_modo_comunicacao_mqtt(t_posicao posicao) {
    char endereco[256];
    int porta;
    char topico[256];

    getchar();
    printf("Endereço do broker: ");
    fgets(endereco, sizeof(endereco), stdin);
    remover_clrf(endereco);

    printf("Porta: ");
    scanf("%d", &porta);
    getchar();

    printf("Publicar no tópico: ");
    fgets(topico, sizeof(topico), stdin);
    remover_clrf(topico);

    if (mqtt_connect(endereco, porta, "MeuNotebook") != 0) {
        printf("Erro na conexão MQTT.\n");
        return;
    }

    char sentenca[256];
    gerarSentencaGPGGA(posicao, sentenca, gerarQuantidadeSatelites(), gerarAltitude(), gerarSeparacaoGeoide());

    while(1) {
        // Muda o comportamento do terminal
        if(_kbhit()) {
            char caracterPressionado = _getch();
            if(caracterPressionado == '\r') {
                break;
            }
        }
        publish(topico, sentenca);


        Sleep(1000);
    }

    mqtt_disconnect();
}
