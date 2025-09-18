#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Função para verificar se a posição está livre no tabuleiro
int posicaoLivre(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    return (tabuleiro[linha][coluna] == 0);
}

// Função auxiliar para posicionar navio horizontal
int posicionarHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (coluna + TAM_NAVIO > TAM_TABULEIRO) return 0; // Fora do limite
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha, coluna + i)) return 0; // Sobreposição
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 3;
    }
    return 1;
}

// Função auxiliar para posicionar navio vertical
int posicionarVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha + TAM_NAVIO > TAM_TABULEIRO) return 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha + i, coluna)) return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 3;
    }
    return 1;
}

// Função auxiliar para posicionar navio diagonal (↘)
int posicionarDiagonalDireita(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna + TAM_NAVIO > TAM_TABULEIRO) return 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha + i, coluna + i)) return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = 3;
    }
    return 1;
}

// Função auxiliar para posicionar navio diagonal (↙)
int posicionarDiagonalEsquerda(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna - (TAM_NAVIO - 1) < 0) return 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, linha + i, coluna - i)) return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = 3;
    }
    return 1;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n===== TABULEIRO DE BATALHA NAVAL =====\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inicializando o tabuleiro com 0 (água)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Tentando posicionar 4 navios: 2 normais (horizontal/vertical) + 2 diagonais
    if (!posicionarHorizontal(tabuleiro, 2, 1))
        printf("Erro ao posicionar navio horizontal!\n");

    if (!posicionarVertical(tabuleiro, 5, 4))
        printf("Erro ao posicionar navio vertical!\n");

    if (!posicionarDiagonalDireita(tabuleiro, 0, 6))
        printf("Erro ao posicionar navio diagonal direita!\n");

    if (!posicionarDiagonalEsquerda(tabuleiro, 3, 8))
        printf("Erro ao posicionar navio diagonal esquerda!\n");

    // Exibindo o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
