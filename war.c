#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função que exibe os territórios no mapa
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n--- MAPA ATUAL ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("-------------------\n");
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n%s (Cor: %s) ataca %s (Cor: %s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("O defensor resistiu! O atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// Função que atribui uma missão aleatória
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Função que exibe a missão do jogador
void exibirMissao(char* missao) {
    printf("\nSua missão: %s\n", missao);
}

// Função simples para verificar se a missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo de missão simples: "Conquistar 3 territórios da cor vermelha"
    if (strstr(missao, "3 territorios vermelhos") != NULL) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0) count++;
        }
        return (count >= 3);
    }
    // Outra missão: "Eliminar todas as tropas azuis"
    if (strstr(missao, "Eliminar tropas azuis") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

// Função para liberar memória alocada
void liberarMemoria(Territorio* mapa, char* missaoJog1, char* missaoJog2) {
    free(mapa);
    free(missaoJog1);
    free(missaoJog2);
}

int main() {
    srand(time(NULL));
    int qtdTerritorios;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtdTerritorios);
    getchar(); // limpa buffer

    // Alocação dinâmica dos territórios
    Territorio* mapa = (Territorio*)malloc(qtdTerritorios * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < qtdTerritorios; i++) {
        printf("\n--- Cadastro do territorio %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);
        getchar();
        printf("Cor (ex: vermelho, azul): ");
        scanf(" %9[^\n]", mapa[i].cor);
        getchar();
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }

    // Criação das missões
    char* missoes[] = {
        "Conquistar 3 territorios vermelhos",
        "Eliminar tropas azuis",
        "Controlar 2 territorios seguidos",
        "Ter mais de 20 tropas no total",
        "Eliminar um inimigo completamente"
    };
    int totalMissoes = 5;

    // Missões dinâmicas dos jogadores
    char* missaoJog1 = (char*)malloc(100 * sizeof(char));
    char* missaoJog2 = (char*)malloc(100 * sizeof(char));

    atribuirMissao(missaoJog1, missoes, totalMissoes);
    atribuirMissao(missaoJog2, missoes, totalMissoes);

    printf("\n--- JOGADOR 1 ---");
    exibirMissao(missaoJog1);
    printf("\n--- JOGADOR 2 ---");
    exibirMissao(missaoJog2);

    // Loop de turnos
    char corJog1[10], corJog2[10];
    printf("\nDigite a cor do Jogador 1: ");
    scanf(" %9[^\n]", corJog1);
    getchar();
    printf("Digite a cor do Jogador 2: ");
    scanf(" %9[^\n]", corJog2);
    getchar();

    int opcao, atacante, defensor;
    while (1) {
        exibirMapa(mapa, qtdTerritorios);
        printf("\nEscolha uma opcao:\n1 - Atacar\n2 - Sair\n> ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 2) break;

        printf("\nEscolha o territorio atacante (1 a %d): ", qtdTerritorios);
        scanf("%d", &atacante);
        getchar();
        printf("Escolha o territorio defensor (1 a %d): ", qtdTerritorios);
        scanf("%d", &defensor);
        getchar();

        atacante--; defensor--;

        if (atacante == defensor) {
            printf("Um territorio nao pode atacar ele mesmo!\n");
            continue;
        }

        if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
            printf("Voce nao pode atacar um territorio da mesma cor!\n");
            continue;
        }

        atacar(&mapa[atacante], &mapa[defensor]);

        // Verifica se alguém venceu
        if (verificarMissao(missaoJog1, mapa, qtdTerritorios)) {
            printf("\n🎯 Jogador 1 venceu! Cumpriu sua missão!\n");
            break;
        }
        if (verificarMissao(missaoJog2, mapa, qtdTerritorios)) {
            printf("\n🎯 Jogador 2 venceu! Cumpriu sua missão!\n");
            break;
        }
    }

    liberarMemoria(mapa, missaoJog1, missaoJog2);
    printf("\nJogo finalizado. Memória liberada com sucesso!\n");
    return 0;
}
