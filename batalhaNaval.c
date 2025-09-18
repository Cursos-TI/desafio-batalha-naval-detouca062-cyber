#include <stdio.h>
#define TAM 10
#define H 5

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0) printf("~ ");
            else if (tabuleiro[i][j] == 3) printf("N ");
            else if (tabuleiro[i][j] == 5) printf("* ");
        }
        printf("\n");
    }
    printf("\n");
}

void criarCone(int habilidade[H][H]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (j >= H / 2 - i && j <= H / 2 + i) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

void criarCruz(int habilidade[H][H]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (i == H / 2 || j == H / 2) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

void criarOctaedro(int habilidade[H][H]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            if (abs(i - H / 2) + abs(j - H / 2) <= H / 2) habilidade[i][j] = 1;
            else habilidade[i][j] = 0;
        }
    }
}

void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[H][H], int origemX, int origemY) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < H; j++) {
            int x = origemX - H / 2 + i;
            int y = origemY - H / 2 + j;
            if (x >= 0 && x < TAM && y >= 0 && y < TAM) {
                if (habilidade[i][j] == 1) tabuleiro[x][y] = 5;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int cone[H][H], cruz[H][H], octaedro[H][H];

    inicializarTabuleiro(tabuleiro);
    tabuleiro[2][2] = 3;
    tabuleiro[5][5] = 3;
    tabuleiro[8][8] = 3;

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    aplicarHabilidade(tabuleiro, cone, 2, 5);
    aplicarHabilidade(tabuleiro, cruz, 5, 5);
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);

    exibirTabuleiro(tabuleiro);
    return 0;
}
