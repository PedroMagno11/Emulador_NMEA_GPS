/**
 * Breve explicação:
 * -> Uma sentença NMEA segue a seguinte estrutura:
 * $[Identificador],[Dados 1],[Dados 2],...[Dados N]*[Checksum]
 * $ -> Indica o ínicio da sentença.
 * Identificador -> Prefixo que identifica o tipo de mensagem (ex.: $GPGGA).
 * Dados -> Valores separados por vírgulas que contêm as informações.
 * Checksum -> Valor hexadecimal calculado a partir do XOR de todos os caracteres $ e *.
 *
 * Principais sentenças NMEA
 * - $GPGGA (Global Positioning System Fix Data)
 *   Proporciona os dados básicos de posição e qualidade do sinal.
 *
 *   Formato:
 *      $GPGGA,HHMMSS,DDMM.MMMM,N,DDDMM.MMMM,E,Q,NN,DOP,ALT,M,GEOID,M,*CS
 *
 *   Exemplo:
 *      $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
 *
 *   Significado dos campos:
 *     1 - HHMMSS: Hora UTC (12h35min19s).
 *     2 - DDMM.MMMM: Latitude (48°07.038').
 *     3 - N: Direção (Norte/Sul).
 *     4 - DDDMM.MMMM: Longitude (11°31.000').
 *     5 - E: Direção (Leste/Oeste).
 *     6 - Q: Qualidade do sinal (1 = GPS fix).
 *     7 - NN: Número de satélites usados.
 *     8 - DOP: Diluição da precisão (0.9 = boa precisão).
 *     9 - ALT: Altitude acima do nível do mar (545.4 m).
 *     10 - M: Unidade de altitude (metros).
 *     11 - GEOID: Separação entre o elipsóide e o geoide (46.9 m).
 *     12 - CS: Checksum (calculado como XOR dos caracteres entre $ e *).
 *
 * - $GPRMC (Recommended Minimum Specific GPS Data)
 *      Inclui informações mínimas como posição, velocidade e direção
 *
 *      Formato:
 *          $GPRMC,HHMMSS,A,DDMM.MMMM,N,DDDMM.MMMM,E,Speed,Course,DDMMYY,MagVar,E/W,*CS
 *
 *      Exemplo:
 *          $GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A
 *
 *      Significado dos Campos:
 *      1 - HHMMSS: Hora UTC.
 *      2 - A: Status (A = ativo, V = inválido).
 *      3 - DDMM.MMMM: Latitude.
 *      4 - N: Direção (Norte/Sul).
 *      5 - DDDMM.MMMM: Longitude.
 *      6 - E: Direção (Leste/Oeste).
 *      7 - Speed: Velocidade sobre o solo (nós).
 *      8 - Course: Direção sobre o solo (graus).
 *      9 - DDMMYY: Data (23 de março de 1994).
 *      10 - MagVar: Variação magnética.
 *      11 - E/W: Direção da variação magnética
 *      12 - CS: Checksum.
 *
 * - $GPVTG (Track Made Good and Ground Speed)
 *   Fornece velocidade e direção.
 *
 *   Formato:
 *       $GPVTG,Course,T,MagneticCourse,M,SpeedKnots,N,SpeedKmH,K,*CS
 *
 *   Exemplo:
 *       $GPVTG,054.7,T,034.4,M,005.5,N,010.2,K*48
 *
 *   Significado dos Campos:
 *       1 - Course: Direção verdadeira (graus).
 *       2 - T: Indica direção verdadeira.
 *       3 - MagneticCourse: Direção magnética (graus).
 *       4 - M: Indica direção magnética.
 *       5 - SpeedKnots: Velocidade em nós.
 *       6 - N: Unidade de velocidade (nós).
 *       7 - SpeedKmH: Velocidade em km/h.
 *       8 - K: Unidade de velocidade (km/h).
 *       9 - CS: Checksum.
 */

#ifndef GPS_H
#define GPS_H
#include <stdbool.h>

struct t_posicao {
    double latitude;
    double longitude;
} typedef t_posicao;

/**
 * @brief Gera uma posição aleatória dentro de limites geográficos especificados.
 *
 * Esta função calcula uma posição aleatória com base nos limites de longitude e latitude informados,
 * retornando um valor dentro da faixa definida.
 *
 * @param longMin Valor mínimo de longitude.
 * @param longMax Valor máximo de longitude.
 * @param latMin Valor mínimo de latitude.
 * @param latMax Valor máximo de latitude.
 * @return t_posicao Estrutura contendo a posição aleatória gerada.
 */
t_posicao gerarPosicaoAleatoria(double longMin, double longMax, double latMin, double latMax);

/**
 * @brief Calcula o valor de checksum para uma mensagem NMEA.
 *
 * Realiza o cálculo do checksum aplicando uma operação XOR byte a byte sobre os caracteres da mensagem fornecida.
 * O checksum é utilizado para verificar a integridade de mensagens no protocolo NMEA 0183.
 *
 * @param mensagem Ponteiro para a string da mensagem a ser verificada.
 * @return char Checksum resultante do processamento.
 */
char calcularChecksum(const char *mensagem);

/**
 * @brief Valida o checksum de uma mensagem NMEA.
 *
 * Verifica se o checksum calculado da mensagem corresponde ao valor de checksum informado na própria mensagem.
 *
 * @param mensagem Ponteiro para a string da mensagem NMEA (incluindo o '*').
 * @return true se o checksum for válido, false caso contrário.
 */
bool validarChecksum(const char *mensagem);

/**
 * @brief Gera uma sentença NMEA do tipo GPGGA.
 *
 * Cria uma sentença NMEA GPGGA formatada com os dados fornecidos, representando posição geográfica, número de satélites, altitude e separação do geoide.
 *
 * @param posicao Estrutura contendo a latitude e longitude.
 * @param nmeaBuffered Buffer onde a sentença NMEA gerada será armazenada.
 * @param satelites Número de satélites utilizados no cálculo da posição.
 * @param altitude Altitude acima do nível do mar em metros.
 * @param separacaoGeoide Separação entre o geoide e o elipsoide em metros.
 */
void gerarSentencaGPGGA(t_posicao posicao, char *nmeaBuffered, int satelites, double altitude, double separacaoGeoide);

/**
 * @brief Gera uma quantidade aleatória de satélites visíveis.
 *
 * Retorna um número aleatório entre 1 e 12 representando a quantidade de satélites utilizados no cálculo da posição GPS.
 *
 * @return int Quantidade aleatória de satélites.
 */
int gerarQuantidadeSatelites();

/**
 * @brief Gera uma altitude aleatória.
 *
 * Retorna um valor aleatório entre 0.0 metros e 50.0 metros de altitude acima do nível do mar para simulação de posição GPS.
 *
 * @return double Valor de altitude em metros.
 */
double gerarAltitude();

/**
 * @brief Gera uma separação aleatória entre o geoide e o elipsoide.
 *
 * Retorna um valor aleatório entre -50.0 metros e 50.0 metros representando a separação do geoide em relação ao elipsoide de referência.
 *
 * @return double Valor de separação em metros.
 */
double gerarSeparacaoGeoide();

#endif //GPS_H
