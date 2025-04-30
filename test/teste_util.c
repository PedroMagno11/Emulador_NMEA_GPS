//
// Created by pedro on 29/04/2025.
//

#include <minunit.h>
#include <util.h>

MU_TEST(test_remover_clrf) {
    char mensagem[] = "Mensagem\r\n";
    char mensagemTratada[] = "Mensagem";

    remover_clrf(mensagem);
    mu_assert_string_eq(mensagemTratada, mensagem);
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_remover_clrf);
}

int main() {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
