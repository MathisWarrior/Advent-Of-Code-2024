#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SQUARE_SIZE 140

char XMAS[SQUARE_SIZE][SQUARE_SIZE + 1]; // pour \0

int estXMAS(int i, int j) {
    if (j <= SQUARE_SIZE - 4 && strncmp(&XMAS[i][j], "XMAS", 4) == 0) return 1;
    return 0;
}

int estXMASInverse(int i, int j) {
    if (j <= SQUARE_SIZE - 4 && strncmp(&XMAS[i][j], "SAMX", 4) == 0) return 1;
    return 0;
}

int EstXMASBas(int i, int j) {
    if (i <= SQUARE_SIZE - 4 && XMAS[i][j] == 'X' && XMAS[i + 1][j] == 'M' && XMAS[i + 2][j] == 'A' && XMAS[i + 3][j] == 'S') return 1;
    return 0;
}

int EstXMASHaut(int i, int j) {
    if (i >= 3 && XMAS[i][j] == 'X' && XMAS[i - 1][j] == 'M' && XMAS[i - 2][j] == 'A' && XMAS[i - 3][j] == 'S') return 1;
    return 0;
}

int EstXMASDiagBasDroite(int i, int j) {
    if (i <= SQUARE_SIZE - 4 && j <= SQUARE_SIZE - 4 && XMAS[i][j] == 'X' && XMAS[i + 1][j + 1] == 'M' && XMAS[i + 2][j + 2] == 'A' && XMAS[i + 3][j + 3] == 'S') return 1;
    return 0;
}

int EstXMASDiagBasGauche(int i, int j) {
    if (i <= SQUARE_SIZE - 4 && j >= 3 && XMAS[i][j] == 'X' && XMAS[i + 1][j - 1] == 'M' && XMAS[i + 2][j - 2] == 'A' && XMAS[i + 3][j - 3] == 'S') return 1;
    return 0;
}

int EstXMASDiagHautDroite(int i, int j) {
    if (i >= 3 && j <= SQUARE_SIZE - 4 && XMAS[i][j] == 'X' && XMAS[i - 1][j + 1] == 'M' && XMAS[i - 2][j + 2] == 'A' && XMAS[i - 3][j + 3] == 'S') return 1;
    return 0;
}

int EstXMASDiagHautGauche(int i, int j) {
    if (i >= 3 && j >= 3 && XMAS[i][j] == 'X' && XMAS[i - 1][j - 1] == 'M' && XMAS[i - 2][j - 2] == 'A' && XMAS[i - 3][j - 3] == 'S') return 1;
    return 0;
}

int CompterNbXMASForGivenLetter(int i, int j) {
    int nbXMAS = 0;

    if (estXMAS(i, j)) nbXMAS++;
    if (estXMASInverse(i, j)) nbXMAS++;
    if (EstXMASBas(i, j)) nbXMAS++;
    if (EstXMASHaut(i, j)) nbXMAS++;
    if (EstXMASDiagHautGauche(i, j)) nbXMAS++;
    if (EstXMASDiagHautDroite(i, j)) nbXMAS++;
    if (EstXMASDiagBasGauche(i, j)) nbXMAS++;
    if (EstXMASDiagBasDroite(i, j)) nbXMAS++;

    return nbXMAS;
}

// M . S        S . M        M . M        S . S
// . A .   ou   . A .   ou   . A .   ou   . A .
// M . S        S . M        S . S        M . M
int checkForXMAS(int i, int j) {
    if (
        (XMAS[i][j]     == 'M' &&
        XMAS[i][j+2]    == 'S' &&
        XMAS[i+1][j+1]  == 'A' &&
        XMAS[i+2][j]    == 'M' &&
        XMAS[i+2][j+2]  == 'S')
        ||
        (XMAS[i][j]     == 'S' &&
        XMAS[i][j+2]    == 'M' &&
        XMAS[i+1][j+1]  == 'A' &&
        XMAS[i+2][j]    == 'S' &&
        XMAS[i+2][j+2]  == 'M')
        ||
        (XMAS[i][j]     == 'M' &&
        XMAS[i][j+2]    == 'M' &&
        XMAS[i+1][j+1]  == 'A' &&
        XMAS[i+2][j]    == 'S' &&
        XMAS[i+2][j+2]  == 'S')
        ||
        (XMAS[i][j]     == 'S' &&
        XMAS[i][j+2]    == 'S' &&
        XMAS[i+1][j+1]  == 'A' &&
        XMAS[i+2][j]    == 'M' &&
        XMAS[i+2][j+2]  == 'M')
    ) return 1;
    return 0;
}


void initTabXMAS() {
    FILE* file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("File not found\n");
        return;
    }

    char ligne[256];

    int i = 0;
    while (fgets(ligne, sizeof(ligne), file)) {
        ligne[strcspn(ligne, "\n")] = '\0';
        strcpy(XMAS[i], ligne);
        i++;
    }

    fclose(file);
}

void afficherTab() {
    for (size_t i = 0; i < SQUARE_SIZE; i++) {
        printf("Ligne %zu : %s\n", i, XMAS[i]);
    }
}

int main(void) {

    initTabXMAS();
    afficherTab();

    int TotalXMAS = 0;
    int TotalX_MAS = 0;

    for (size_t i = 0; i < SQUARE_SIZE; i++) {
        for (size_t j = 0; j < SQUARE_SIZE; j++){
            TotalXMAS += CompterNbXMASForGivenLetter(i, j);
            TotalX_MAS += checkForXMAS(i, j);
        }
    }

    printf("Total XMAS : %d\n", TotalXMAS);
    printf("Total X_MAS : %d\n", TotalX_MAS);

    return EXIT_SUCCESS;
}