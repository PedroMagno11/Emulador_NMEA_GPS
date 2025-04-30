//
// Created by pedro on 30/04/2025.
//
#include "comunicacao_serial.h"

#include <stdio.h>

#include "comunicacao_tcp.h"

void printErro(const char *msg) {
    DWORD error_code = GetLastError();
    char buffer[256];
    DWORD size = FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK,
        NULL, error_code, MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN),
        buffer, sizeof(buffer), NULL);
    if (size == 0) {
        buffer[0] = 0;
    }
    fprintf(stderr, "%s: %s\n", msg, buffer);
}

HANDLE abrirPortaSerial(const char *dispositivo, uint32_t baud_rate) {
    HANDLE porta = CreateFileA(dispositivo, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if(porta == INVALID_HANDLE_VALUE) {
        printErro(dispositivo);
        return INVALID_HANDLE_VALUE;
    }

    // Configurações do Timeout
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(porta, &timeouts)) {
        printErro("Failed to set serial timeouts");
        CloseHandle(porta);
        return INVALID_HANDLE_VALUE;
    }

    // Configurações da comunicação
    DCB state = {0};
    state.DCBlength = sizeof(DCB);
    state.BaudRate = baud_rate;
    state.ByteSize = 8;
    state.Parity = NOPARITY;
    state.StopBits = ONESTOPBIT;

    if(!SetCommState(porta, &state)) {
        printErro("Failed to set serial settings");
        CloseHandle(porta);
        return INVALID_HANDLE_VALUE;
    }

    return porta;
}

int escreverNaPortaSerial(HANDLE porta, const char *mensagem) {
    DWORD escritor;
    BOOL sucesso = WriteFile(porta, mensagem, strlen(mensagem), &escritor, NULL);
    if(!sucesso || escritor != strlen(mensagem)) {
        printErro("Falha ao escrever na porta");
        return -1;
    }
    return 0;
}

int lerNaPortaSerial(HANDLE porta, char *buffer, size_t size) {
    DWORD leitor;
    BOOL sucesso = ReadFile(porta, buffer, size, &leitor, NULL);
    if(!sucesso) {
        printErro("Falha ao ler na porta");
        return -1;
    }

    buffer[leitor] = '\0';
    return leitor;
}


