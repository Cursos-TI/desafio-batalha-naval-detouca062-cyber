#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

int main() {
    // Matriz 10x10 representando o tabuleiro (0 = água, 3 = navio)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Vetores para representar os navios (3 posições cada)
    int navioHorizontal[TAM_NAVIO] = {3, 3, 3};
    int navioVertical[TAM_NAVIO] = {3, 3, 3};

    // Coordenadas iniciais escolhidas no código
    // (linha, coluna)
    int linhaHorizontal = 2, colunaHorizontal = 4; // navio horizontal
    int linhaVertical = 5, colunaVertical = 7;     // navio vertical

    // ===== Validação do Navio Horizontal =====
    if (colunaHorizontal + TAM_NAVIO <= TAM_TABULEIRO) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            // Verifica sobreposição
            if (tabuleiro[linhaHorizontal][colunaHorizontal + i] != 0) {
                printf("Erro: Sobreposição detectada no navio horizontal!\n");
                return 1;
            }
            tabuleiro[linhaHorizontal][colunaHorizontal + i] = navioHorizontal[i];
        }
    } else {
        printf("Erro: Navio horizontal fora dos limites do tabuleiro!\n");
        return 1;
    }

    // ===== Validação do Navio Vertical =====
    if (linhaVertical + TAM_NAVIO <= TAM_TABULEIRO) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            // Verifica sobreposição
            if (tabuleiro[linhaVertical + i][colunaVertical] != 0) {
                printf("Erro: Sobreposição detectada no navio vertical!\n");
                return 1;
            }
            tabuleiro[linhaVertical + i][colunaVertical] = navioVertical[i];
        }
    } else {
        printf("Erro: Navio vertical fora dos limites do tabuleiro!\n");
        return 1;
    }

    // ===== Exibindo o tabuleiro =====
    printf("\n===== TABULEIRO DE BATALHA NAVAL =====\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
