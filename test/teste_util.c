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

MU_TEST(test_from_int_to_string) {
    int number = 10;

    char *numberString = from_int_to_string(number);

    mu_assert_string_eq(numberString, "10");
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_remover_clrf);
    MU_RUN_TEST(test_from_int_to_string);
}

int main() {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
