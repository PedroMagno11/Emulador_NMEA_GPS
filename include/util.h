//
// Created by pedro on 29/04/2025.
//

#ifndef UTIL_H
#define UTIL_H

/**
 * @brief Remove a sequência de fim de linha (CRLF) de uma string.
 *
 * Esta função percorre a string fornecida e remove a sequência de caracteres
 * que representa o final de linha em sistemas Windows, composta por
 * "Carriage Return" (CR - 0x0D) seguido de "Line Feed" (LF - 0x0A).
 *
 * @param str Ponteiro para a string da qual o CRLF deve ser removido.
 */
void remover_clrf(char *str);

char * from_int_to_string(int number);

#endif //UTIL_H
