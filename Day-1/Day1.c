/**
 * Résumé du problème 1 :
 *      calculer la somme des différences absolues entre les paires d'ID
 *
 * Résumé du problème 2 :
 *      multiplier chaque élément de la première liste par le nombre de fois qu'il apparaît
 *      dans la deuxième liste, puis aditionner tous les résultats obtenus.
 */

#include <stdio.h>
#include <stdlib.h>
#include "TasBinaireMin.h"

#define TAB_SIZE 1000

void fillTasMin(TasMin** leftSide, TasMin** rightSide) {

    FILE* file = fopen("input.txt", "r");
    if(file == NULL){
        printf("File not found\n");
        return;
    }

    int tempval[2];
    char buffer[256];

    int i = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        sscanf(buffer, "%d %d", &tempval[0], &tempval[1]);
        inserer(*leftSide, tempval[0]);
        inserer(*rightSide, tempval[1]);
        i++;
    }

    fclose(file);
}

void initTasMin(TasMin** leftSide, TasMin** rightSide) {
    *leftSide = creerTas(TAB_SIZE);
    *rightSide = creerTas(TAB_SIZE);
}

int getSumOfDiffFromAllLowest(TasMin* leftSide, TasMin* rightSide) {
    int sumAllDiff = 0;

    while (leftSide != NULL && leftSide->taille > 0) {
        sumAllDiff += abs(extraireMin(leftSide) - extraireMin(rightSide));
    }

    return sumAllDiff;
}

int getSimilarityScore(TasMin* leftSide, TasMin* rightSide) {
    int compteur = 0;
    int similarity_score = 0;

    for (int i = 0; i < leftSide->longueur; i++) {
        int compare = leftSide->tab[i];

        for (int j = 0; j < rightSide->longueur; j++) {
            if (compare == rightSide->tab[j]) compteur++;
        }

        similarity_score += compare * compteur;
        compteur = 0;
    }

    return similarity_score;
}

int main(void){

    TasMin* leftSide;
    TasMin* rightSide;

    initTasMin(&leftSide, &rightSide);
    fillTasMin(&leftSide, &rightSide);

    int similarity_score = getSimilarityScore(leftSide, rightSide);

    printf("Similarity score: %d\n", similarity_score);

    int sumOfDiffFromAllLowest = getSumOfDiffFromAllLowest(leftSide, rightSide);

    printf("Sum of all differences: %d\n", sumOfDiffFromAllLowest);

    liberer_TasMin(leftSide);
    liberer_TasMin(rightSide);

    return EXIT_SUCCESS;
}