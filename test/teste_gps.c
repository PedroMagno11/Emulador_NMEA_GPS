//
// Created by Pedro Magno on 29/04/2025.
//
#include "minunit.h"
#include "gps.h"

MU_TEST(test_gerar_posicao_aleatoria) {
    t_posicao posicao = gerarPosicaoAleatoria(-23.5505, -22.555, -43.1231, -42.032);
    mu_check(posicao.longitude >= -23.5505 && posicao.longitude <= -22.555);
}

MU_TEST(test_calcular_checksum) {
    // Sentença usada para o teste
    // "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";

    // sentenca sem o * e o checksum
    char sentenca[] = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,";

    // Calcula o checksum
    unsigned char checksumCalculado = (unsigned char) calcularChecksum(sentenca);

    // Buffer para guardar o checksum em string hexadecimal (2 dígitos + \0)
    char checksumHex[3];
    sprintf(checksumHex, "%02x",checksumCalculado);

    mu_assert_string_eq("47", checksumHex);
}

MU_TEST(test_validar_checksum) {
    char sentenca[] = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";
    mu_check(validarChecksum(sentenca));
}

MU_TEST(test_validar_checksum_invalid) {
    char sentenca[] = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*27";
    mu_check(!validarChecksum(sentenca));
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_gerar_posicao_aleatoria);
    MU_RUN_TEST(test_validar_checksum);
    MU_RUN_TEST(test_calcular_checksum);
    MU_RUN_TEST(test_validar_checksum_invalid);
}

int main() {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}