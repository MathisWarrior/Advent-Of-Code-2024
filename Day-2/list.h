typedef struct Cellule {
    int val;
    struct Cellule* next;
} Cellule;

typedef Cellule* Liste;

void libererListe(Cellule*);

void afficherListe(Cellule*);

void supprimerCellule(Cellule**, int);

void insererFin(Cellule**, int);

Cellule* creerCellule(int);

Liste copyList(Liste);