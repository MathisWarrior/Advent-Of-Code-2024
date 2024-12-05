typedef struct {
    int *tab;
    int taille;
    int longueur;
} TasMin;

// Créer un tas binaires min
TasMin* creerTas(int);

// obtenir l'index du parent
int parent(int);

// obtenir l'index du fils gauche
int filsGauche(int);

// obtenir l'index du fils droit
int fislDroit(int);

// rétablir l'ordre du tas après un retrait ou insertion
void RetablirTasMin(TasMin*, int);

// insérer un élément dans le tas
void inserer(TasMin*, int);

// extraire le minimum du tas
int extraireMin(TasMin*);

// afficher le tas
void afficherTas(TasMin*);

// libérer la mémoire allouée pour le tas
void liberer_TasMin(TasMin*);