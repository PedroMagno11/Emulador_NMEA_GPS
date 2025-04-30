//
// Created by pedro on 29/04/2025.
//
#include "gps.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

t_posicao gerarPosicaoAleatoria(double longMin, double longMax, double latMin, double latMax) {
    double latitude = latMin + ((double) rand()/(double)RAND_MAX) * (latMax - latMin);
    double longitude = longMin + ((double) rand()/(double)RAND_MAX) * (longMax - longMin);
    t_posicao posicao = {latitude, longitude};
    return posicao;
}

char calcularChecksum(const char *mensagem) {
    char checksum = 0;

    // Percorre os caracters entre '$' e '*'
    for (const char *i = mensagem + 1 ; *i != '*' && *i != '\0'; i++) {
        checksum ^= *i;
    }
    return checksum;
}

bool validarChecksum(const char *mensagem) {// procuro a existencia do asteristico
    const char *asteristico = strchr(mensagem, '*');
    // Se não encontrar o asteristico , o checksum não é válido
    if (asteristico == NULL) {
        return false;
    }
    // checksum da mensagem recebida
    const char *checksumDaMensagem = asteristico + 1;

    // Variável auxialiar que vai armazenar o checksum da mensagem recebida já tratado
    char checksumDaMensagem_aux[3];
    // Copia o checksum da mensagem recebida para a variável auxiliar
    strncpy(checksumDaMensagem_aux, checksumDaMensagem,2);
    // Garante que a terminação seja nula para a variável auxiliar
    checksumDaMensagem_aux[2] = '\0';
    // Trata o checksum da mensagem
    remover_clrf(checksumDaMensagem_aux);
    // Calcula do checksum com base na mensagem recebida
    char checksumCalculado = calcularChecksum(mensagem);
    // variavel auxiliar que vai armazenar uma "copia" do checksum calculado com um char* e não um unsigned int
    char checksumCalculado_aux[3];
    // copia o valor do checksumCalculado para a variavel checksumCalculado_aux
    sprintf(checksumCalculado_aux, "%02X", (unsigned char)checksumCalculado);

    return strcmp(checksumCalculado_aux, checksumDaMensagem_aux) == 0;
}

void gerarSentencaGPGGA(t_posicao posicao, char *nmeaBuffered, int satelites, double altitude, double separacaoGeoide){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    char direcao_lat = (posicao.latitude >= 0.0) ? 'N' : 'S';
    char direcao_long = (posicao.longitude >= 0.0) ? 'E' : 'W';

    int graus_lat = (int)fabs(posicao.latitude);
    double lat_min = (fabs(posicao.latitude) - graus_lat) * 60;

    int graus_long = (int)fabs(posicao.longitude);
    double long_min = (fabs(posicao.longitude) - graus_long) * 60;

    // Monta a sentença sem o checksum
    sprintf(nmeaBuffered, "$GPGGA,%02d%02d%02d,%02d%07.4f,%c,%03d%07.4f,%c,1,%02d,1.0,%.1f,M,%.1f,M,,",
        tm->tm_hour , tm->tm_min, tm->tm_sec, graus_lat, lat_min, direcao_lat, graus_long, long_min, direcao_long, satelites, altitude, separacaoGeoide);

    // Calcula e adiciona o checksum
    char checksum = calcularChecksum(nmeaBuffered);
    sprintf(nmeaBuffered, "%s*%02X\r\n", nmeaBuffered, checksum);
}

int gerarQuantidadeSatelites() {
    return rand()%12 + 1; // Número de satélites (1 a 12)
}

double gerarAltitude() {
    return ((double)rand() / (double)RAND_MAX) * 50.0; // Altitude (0.0 m a 50.0 m)
}

double gerarSeparacaoGeoide() {
    return ((double)rand() / (double)RAND_MAX) * 100.0 - 50.0; // Separação do geoide (-25.0 m a 25.0 m)
}

