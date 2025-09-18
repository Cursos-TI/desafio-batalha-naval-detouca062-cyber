#include <stdio.h>
#include <stdlib.h>

#define TAB_SIZE 10
#define SHIP_SIZE 3
#define SKILL_SIZE 7

int posicaoLivre(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna) {
    return (tab[linha][coluna] == 0);
}

int posicionarHorizontal(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna) {
    if (linha < 0 || linha >= TAB_SIZE) return 0;
    if (coluna < 0 || coluna + SHIP_SIZE > TAB_SIZE) return 0;
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (!posicaoLivre(tab, linha, coluna + i)) return 0;
    }
    for (int i = 0; i < SHIP_SIZE; i++) tab[linha][coluna + i] = 3;
    return 1;
}

int posicionarVertical(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna) {
    if (coluna < 0 || coluna >= TAB_SIZE) return 0;
    if (linha < 0 || linha + SHIP_SIZE > TAB_SIZE) return 0;
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (!posicaoLivre(tab, linha + i, coluna)) return 0;
    }
    for (int i = 0; i < SHIP_SIZE; i++) tab[linha + i][coluna] = 3;
    return 1;
}

int posicionarDiagonalDireita(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna) {
    if (linha < 0 || coluna < 0) return 0;
    if (linha + SHIP_SIZE > TAB_SIZE || coluna + SHIP_SIZE > TAB_SIZE) return 0;
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (!posicaoLivre(tab, linha + i, coluna + i)) return 0;
    }
    for (int i = 0; i < SHIP_SIZE; i++) tab[linha + i][coluna + i] = 3;
    return 1;
}

int posicionarDiagonalEsquerda(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna) {
    if (linha < 0 || coluna < 0) return 0;
    if (linha + SHIP_SIZE > TAB_SIZE || coluna - (SHIP_SIZE - 1) < 0) return 0;
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (!posicaoLivre(tab, linha + i, coluna - i)) return 0;
    }
    for (int i = 0; i < SHIP_SIZE; i++) tab[linha + i][coluna - i] = 3;
    return 1;
}

void construirCone(int mat[SKILL_SIZE][SKILL_SIZE], int size) {
    int center = size / 2;
    for (int r = 0; r < size; r++) for (int c = 0; c < size; c++) mat[r][c] = 0;
    for (int r = 0; r < size; r++) {
        int left = center - r;
        int right = center + r;
        if (left < 0) left = 0;
        if (right >= size) right = size - 1;
        for (int c = left; c <= right; c++) mat[r][c] = 1;
    }
}

void construirCruz(int mat[SKILL_SIZE][SKILL_SIZE], int size) {
    int center = size / 2;
    for (int r = 0; r < size; r++) for (int c = 0; c < size; c++) mat[r][c] = 0;
    for (int c = 0; c < size; c++) mat[center][c] = 1;
    for (int r = 0; r < size; r++) mat[r][center] = 1;
}

void construirOctaedro(int mat[SKILL_SIZE][SKILL_SIZE], int size) {
    int center = size / 2;
    for (int r = 0; r < size; r++) for (int c = 0; c < size; c++) mat[r][c] = 0;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            int dist = abs(r - center) + abs(c - center);
            if (dist <= center) mat[r][c] = 1;
        }
    }
}

int aplicarHabilidade(int tab[TAB_SIZE][TAB_SIZE],
                      int skill[SKILL_SIZE][SKILL_SIZE],
                      int skillSize,
                      int pivotLocalRow, int pivotLocalCol,
                      int originRow, int originCol,
                      int skillValue) {
    int aplicada = 0;
    for (int i = 0; i < skillSize; i++) {
        for (int j = 0; j < skillSize; j++) {
            if (skill[i][j] != 1) continue;
            int br = originRow + (i - pivotLocalRow);
            int bc = originCol + (j - pivotLocalCol);
            if (br < 0 || br >= TAB_SIZE || bc < 0 || bc >= TAB_SIZE) continue;
            if (tab[br][bc] == 0) tab[br][bc] = skillValue;
            else tab[br][bc] = tab[br][bc] + skillValue;
            aplicada++;
        }
    }
    return aplicada;
}

void exibirTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    printf("\n===== TABULEIRO (0=Água, 3=Navio, 5=Área, 8=Navio+Área) =====\n\n");
    for (int r = 0; r < TAB_SIZE; r++) {
        for (int c = 0; c < TAB_SIZE; c++) {
            printf("%d ", tab[r][c]);
        }
        printf("\n");
    }
    printf("\nLegenda:\n  0 = Água\n  3 = Navio\n  5 = Área afetada (habilidade)\n  8 = Navio + Área afetada (sobreposição)\n\n");
}

int main() {
    int tab[TAB_SIZE][TAB_SIZE] = {0};

    if (!posicionarHorizontal(tab, 2, 1)) {
        printf("Falha ao posicionar navio horizontal em (2,1)\n");
    }
    if (!posicionarVertical(tab, 5, 4)) {
        printf("Falha ao posicionar navio vertical em (5,4)\n");
    }
    if (!posicionarDiagonalDireita(tab, 0, 6)) {
        printf("Falha ao posicionar navio diagonal direita em (0,6)\n");
    }
    if (!posicionarDiagonalEsquerda(tab, 3, 8)) {
        printf("Falha ao posicionar navio diagonal esquerda em (3,8)\n");
    }

    int cone[SKILL_SIZE][SKILL_SIZE];
    int cruz[SKILL_SIZE][SKILL_SIZE];
    int octaedro[SKILL_SIZE][SKILL_SIZE];

    construirCone(cone, SKILL_SIZE);
    construirCruz(cruz, SKILL_SIZE);
    construirOctaedro(octaedro, SKILL_SIZE);

    int originConeR = 1, originConeC = 3;
    int originCruzR = 6, originCruzC = 2;
    int originOctR  = 4, originOctC  = 7;

    int conePivotR = 0, conePivotC = SKILL_SIZE / 2;
    int centerPivot = SKILL_SIZE / 2;

    int aplicadasCone = aplicarHabilidade(tab, cone, SKILL_SIZE, conePivotR, conePivotC, originConeR, originConeC, 5);
    int aplicadasCruz = aplicarHabilidade(tab, cruz, SKILL_SIZE, centerPivot, centerPivot, originCruzR, originCruzC, 5);
    int aplicadasOct  = aplicarHabilidade(tab, octaedro, SKILL_SIZE, centerPivot, centerPivot, originOctR, originOctC, 5);

    printf("Habilidades aplicadas: Cone=%d, Cruz=%d, Octaedro=%d\n", aplicadasCone, aplicadasCruz, aplicadasOct);

    exibirTabuleiro(tab);

    return 0;
}
