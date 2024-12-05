#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.c"

#define NB_LINES 1000

int isSafe(Liste head) {
    int croissant = 1;
    int decroissant = 1;

    while (head->next != NULL) {
        int diff = abs(head->val - head->next->val);

        if (diff < 1 || diff > 3) {
            return 0;
        }

        if (head->val > head->next->val) {
            croissant = 0;
        } else if (head->val < head->next->val) {
            decroissant = 0;
        }

        head = head->next;
    }

    return croissant || decroissant;
}

int NbOfSafeReport(Liste* tabSuite) {
    int safeCounter = 0;

    for (size_t i = 0; i < NB_LINES; i++) {
        Liste current = tabSuite[i];
        if(isSafe(current)) {
            safeCounter++;
        }
    }

    return safeCounter;
}

int NbOfSafeReportPart2(Liste* tabSuite) {
    int safeCounter = 0;

    for (size_t i = 0; i < NB_LINES; i++) {
        Liste current = tabSuite[i];

        if (isSafe(current)) {
            safeCounter++;
        } else {
            int variantSafe = 0;

            for (size_t j = 0; current != NULL && j < nbElements(current); j++) {
                Liste temp = copierListe(current);
                temp = supprimerCelluleAIndex(temp, j);

                if (isSafe(temp)) {
                    variantSafe = 1;
                    libererListe(temp);
                    break;
                }
                libererListe(temp);
            }

            if (variantSafe) {
                safeCounter++;
            }
        }
    }

    return safeCounter;
}

void initTabSuite(Liste* tabSuite) {
    FILE* file = fopen("input.txt", "r");
    if(file == NULL){
        printf("File not found\n");
        return;
    }

    int i = 0;
    char buffer[256];

    for (int i = 0; i < NB_LINES; i++) {
        tabSuite[i] = NULL;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL && i < NB_LINES) {
        int values[8];
        int count = 0;

        char* token = strtok(buffer, " \n");
        while (token != NULL) {
            values[count++] = atoi(token);
            token = strtok(NULL, " \n");
        }

        for (int j = 0; j < count; j++) {
            insererFin(&tabSuite[i], values[j]);
        }

        i++;
    }

    fclose(file);
}

void afficherTabSuite(Liste* tabSuite) {
    for (int i = 0; i < NB_LINES; i++) {
        printf("Ligne %d: ", i);
        afficherListe(tabSuite[i]);
    }
}

int main(void) {
    Liste* tabSuite = (Liste*)malloc(NB_LINES * sizeof(Liste));
    initTabSuite(tabSuite);

    // afficherTabSuite(tabSuite);

    int safeCounter = NbOfSafeReport(tabSuite);
    printf("Safe counter 1: %d\n", safeCounter);

    safeCounter = NbOfSafeReportPart2(tabSuite);
    printf("Safe counter 2: %d\n", safeCounter);


    for (int i = 0; i < NB_LINES; i++) {
        libererListe(tabSuite[i]);
    }

    free(tabSuite);

    return EXIT_SUCCESS;
}
