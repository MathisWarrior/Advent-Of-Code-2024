/**
 * Résumé du problème 1 :
 *      additionner les contenus de chaque multiplication résultante de mul(%d,%d) trouvé dans un fichier
 *
 * Résumé du problème 2 :
 *      des do() et don't() sont présent, ne pas prendre en compte les mul si après un don't()
 */


#include <stdio.h>
#include <string.h>

char ligne[1 << 20], *curseur, *finNombre;
long long sommeTotale = 0, sommeActive = 0, facteurA, facteurB;
int etat = 1;

int estChiffre(int caractere) {
    return caractere >= '0' && caractere <= '9';
}

void traiterMultiplication()
{
    curseur += 4; // passage de "mul("

    if (!estChiffre(*curseur)) return;

    finNombre = curseur;
    while (estChiffre(*finNombre)) ++finNombre;

    if (*finNombre != ',') {
        curseur = finNombre;
        return;
    }

    *finNombre = 0;
    sscanf(curseur, "%lld", &facteurA);
    curseur = finNombre + 1; // on passe la virgule

    if (!estChiffre(*curseur)) return;

    finNombre = curseur;
    while (estChiffre(*finNombre)) ++finNombre;

    if (*finNombre != ')') {
        curseur = finNombre;
        return;
    }

    *finNombre = 0;
    sscanf(curseur, "%lld", &facteurB);
    curseur = finNombre + 1;

    sommeTotale += facteurA * facteurB;
    if (etat) sommeActive += facteurA * facteurB;
}

void changerEtat()
{
    if (memcmp("don't()", curseur, 7) == 0) {
        curseur += 7;
        etat = 0;
    } else if (memcmp("do()", curseur, 4) == 0) {
        curseur += 4;
        etat = 1;
    }
}

void traiterLigne()
{
    while (*curseur) {
        if (memcmp("don't()", curseur, 7)  == 0 || memcmp("do()", curseur, 4) == 0) {
            changerEtat();
        } else if (*curseur == 'm' && memcmp("mul(", curseur, 4) == 0) {
            traiterMultiplication();
        } else {
            ++curseur;
        }
    }
}

int main()
{
    FILE *fichier = fopen("input.txt", "r");

    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier input.txt\n");
        return 1;
    }

    while (fgets(ligne, sizeof ligne, fichier)) {
        curseur = ligne;
        traiterLigne();
    }

    fclose(fichier);
    printf("%lld\n%lld\n", sommeTotale, sommeActive);
    return 0;
}
