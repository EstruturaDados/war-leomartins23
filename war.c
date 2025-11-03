#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Programa: WAR Estruturado - Simulação de Ataques entre Territórios
 * Objetivo: implementar um sistema dinâmico de territórios com funcionalidade de ataque.
 * Autor: (Exemplo didático)
 * Observações:
 *  - Usa alocação dinâmica de memória para os territórios.
 *  - Utiliza ponteiros para manipulação direta dos dados.
 *  - Simula o ataque com base em valores aleatórios (1 a 6).
 */

#define MAX_NOME 30
#define MAX_COR 10

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // consome o '\n'
    }
}

// Função para exibir territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== Territórios Atuais ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nVocê não pode atacar um território do mesmo exército!\n");
        return;
    }

    printf("\n%s (Cor: %s) está atacando %s (Cor: %s)!\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante: %d | Dado do defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: %s venceu o ataque!\n", atacante->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf("Resultado: %s defendeu com sucesso!\n", defensor->nome);
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main(void) {
    srand(time(NULL)); // inicializa o gerador de números aleatórios

    int n;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);
    getchar(); // consome o '\n'

    Territorio* mapa = (Territorio*)calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    int opcao;
    do {
        exibirTerritorios(mapa, n);
        printf("\nEscolha um território atacante (1-%d): ", n);
        int iAtacante, iDefensor;
        scanf("%d", &iAtacante);
        getchar();

        printf("Escolha um território defensor (1-%d): ", n);
        scanf("%d", &iDefensor);
        getchar();

        if (iAtacante >= 1 && iAtacante <= n && iDefensor >= 1 && iDefensor <= n) {
            atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
        } else {
            printf("\nEscolha inválida!\n");
        }

        printf("\nDeseja realizar outro ataque? (1 = sim / 0 = não): ");
        scanf("%d", &opcao);
        getchar();

    } while (opcao == 1);

    exibirTerritorios(mapa, n);

    liberarMemoria(mapa);
    printf("\nMemória liberada. Encerrando o programa...\n");

    return 0;
}
