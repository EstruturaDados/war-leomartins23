#include <stdio.h>
#include <string.h>

/*
 * Programa: Construção dos territórios
 * Objetivo: armazenar e exibir dados de 5 territórios usando uma struct composta.
 * Autor: (Exemplo didático)
 * Observações:
 *  - Usa fgets para ler strings (permite espaços) e scanf para ler inteiros (tropas).
 */

#define TERR_COUNT 5
#define MAX_NOME 30
#define MAX_COR 10

/* Definição da struct Territorio
 * - nome: nome do território (até 29 caracteres + terminador) 
 * - cor: cor do exército associado (até 9 caracteres + terminador)
 * - tropas: quantidade de tropas (inteiro)
 */
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

int main(void) {
    Territorio territorios[TERR_COUNT];

    printf("=== Cadastro de Territórios ===\n");
    printf("Você deverá informar o nome, a cor do exército e o número de tropas de %d territórios.\n\n", TERR_COUNT);

    for (int i = 0; i < TERR_COUNT; i++) {
        printf("Território %d de %d:\n", i + 1, TERR_COUNT);

        // Leitura do nome com fgets para permitir espaços
        printf("  Nome: ");
        if (fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin) == NULL) {
            territorios[i].nome[0] = '\0';
        } else {
            size_t len = strlen(territorios[i].nome);
            if (len > 0 && territorios[i].nome[len - 1] == '\n') {
                territorios[i].nome[len - 1] = '\0';
            }
        }

        // Leitura da cor do exército com fgets
        printf("  Cor do exército: ");
        if (fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin) == NULL) {
            territorios[i].cor[0] = '\0';
        } else {
            size_t len = strlen(territorios[i].cor);
            if (len > 0 && territorios[i].cor[len - 1] == '\n') {
                territorios[i].cor[len - 1] = '\0';
            }
        }

        // Leitura do número de tropas usando scanf (requisito técnico)
        printf("  Número de tropas: ");
        while (scanf("%d", &territorios[i].tropas) != 1) {
            printf("    Entrada inválida. Digite um número inteiro para tropas: ");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { /* descartar */ }
        }
        int ch = getchar(); // consome o '\n' deixado pelo scanf

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("=== Territórios cadastrados ===\n");
    for (int i = 0; i < TERR_COUNT; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome[0] ? territorios[i].nome : "(não informado)");
        printf("  Cor do exército: %s\n", territorios[i].cor[0] ? territorios[i].cor : "(não informado)");
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("-------------------------------\n");
    }

    return 0;
}
