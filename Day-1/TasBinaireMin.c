#include "TasBinaireMin.h"
#include <stdio.h>
#include <stdlib.h>

TasMin* creerTas(int longueur) {
    TasMin *tas = (TasMin*)malloc(sizeof(TasMin));
    tas->tab = (int*)malloc(longueur * sizeof(int));
    tas->longueur = longueur;
    tas->taille = 0;
    return tas;
}

int parent(int i) { return (i - 1) / 2; }

int filsGauche(int i) { return 2 * i + 1; }

int filsDroit(int i) { return 2 * i + 2; }

void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void retablirTasMin(TasMin *tas, int i) {
    int gauche = filsGauche(i);
    int droit = filsDroit(i);
    int plus_petit = i;

    if (gauche < tas->taille && tas->tab[gauche] < tas->tab[plus_petit]) {
        plus_petit = gauche;
    }
    if (droit < tas->taille && tas->tab[droit] < tas->tab[plus_petit]) {
        plus_petit = droit;
    }

    if (plus_petit != i) {
        echanger(&tas->tab[i], &tas->tab[plus_petit]);
        retablirTasMin(tas, plus_petit);
    }
}

void inserer(TasMin *tas, int value) {
    if (tas->taille == tas->longueur) {
        printf("Le tas est plein, impossible d'insérer.\n");
        return;
    }

    // Ajouter l'élément à la fin du tableau
    tas->taille++;
    int i = tas->taille - 1;
    tas->tab[i] = value;

    // Remonter l'élément jusqu'à la position correcte
    while (i != 0 && tas->tab[parent(i)] > tas->tab[i]) {
        echanger(&tas->tab[i], &tas->tab[parent(i)]);
        i = parent(i);
    }
}

int extraireMin(TasMin *tas) {
    if (tas->taille <= 0) {
        printf("Le tas est vide.\n");
        return -1; // Erreur
    }
    if (tas->taille == 1) {
        tas->taille--;
        return tas->tab[0];
    }

    // Sauvegarder la racine, remplacer la racine par le dernier élément du tas
    int root = tas->tab[0];
    tas->tab[0] = tas->tab[tas->taille - 1];
    tas->taille--;

    retablirTasMin(tas, 0);

    return root;
}

// Fonction pour afficher le tas
void afficherTas(TasMin *tas) {
    for (int i = 0; i < tas->taille; i++) {
        printf("%d ", tas->tab[i]);
    }
    printf("\n");
}

void liberer_TasMin(TasMin* tas) {
    free(tas->tab);
    free(tas);
}