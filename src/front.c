//
// Created by pedro on 29/04/2025.
//
#include "front.h"

#include <stdio.h>

void mostrarCabecalho() {
    const char *cabecalho[] = {"______                 _           _              _   _ __  __ ______",
                            "|  ____|               | |         | |            | \\ | |  \\/  |  ____|   /\\",
                            "| |__   _ __ ___  _   _| | __ _  __| | ___  _ __  |  \\| | \\  / | |__     /  \\",
                            "|  __| | '_ ` _ \\| | | | |/ _` |/ _` |/ _ \\| '__| | . ` | |\\/| |  __|   / /\\ \\",
                            "| |____| | | | | | |_| | | (_| | (_| | (_) | |    | |\\  | |  | | |____ / ____ \\",
                            "|______|_| |_| |_|\\__,_|_|\\__,_|\\__,_|\\___/|_|    |_| \\_|_|  |_|______/_/    \\_\\"
    };

    for(int i = 0; i < sizeof(cabecalho) / sizeof(cabecalho[0]); i++) {
        printf("%s\n", cabecalho[i]);
    }
}

void mostrarDescricao() {
    const char *informacoes[] = {
        "\n - Criado por Pedro Magno.",
        " - O Emulador NMEA é um script simples que emula um receptor GPS.",
        " - Os dados são enviados aos clientes no formato NMEA 0183.",
        " - Sentenças NMEA utilizadas: GGA, RMC, GSA, GSV, GLL, VTG e TXT.\n"
    };

    for(int i = 0; i < sizeof(informacoes) / sizeof(informacoes[0]); i++) {
        printf("%s\n", informacoes[i]);
    }
}


void mostrarMenu() {
    const char *opcoes[] = {
        "1 - NMEA via porta Serial",
        "2 - NMEA via Servidor TCP",
        "3 - NMEA via HTTP",
        "4 - NMEA via MQTT",
        "5 - Sair"
    };

    for (int i = 0; i < sizeof(opcoes) / sizeof(opcoes[0]); i++) {
        printf("%s\n", opcoes[i]);
    }
}

void mostrarSolicitacaoDeEspecificacoesGeograficas() {
    const char *opcoes[] = {
        "1 - Especificar os limites geográficos",
        "2 - Especificar uma determinada posição"
    };
    for (int i = 0; i < sizeof(opcoes) / sizeof(opcoes[0]); i++) {
        printf("%s\n", opcoes[i]);
    }
}