//
// Created by pedro on 30/04/2025.
//

#ifndef COMUNICACAO_SERIAL_H
#define COMUNICACAO_SERIAL_H
#include <bemapiset.h>
#include <stdint.h>

void printErro(const char *msg);
HANDLE abrirPortaSerial(const char *dispositivo, uint32_t baud_rate);
int escreverNaPortaSerial(HANDLE porta, const char *mensagem);
int lerNaPortaSerial(HANDLE porta, char *buffer, size_t size);
#endif //COMUNICACAO_SERIAL_H
