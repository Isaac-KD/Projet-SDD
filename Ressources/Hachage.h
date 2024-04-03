#include "Reseau.h"

typedef struct {
    int nbElement; //pas necessaire ici
    int tailleMax;
    CellNoeud** T;
} TableHachage;

double h( int k,int M);
int f( int x, int y );

void ajoute_NoeudtableHachage(TableHachage *H,Noeud *n);
void ajoute_NoeudtableHachage( TableHachage *H, Noeud * n,int clée); // utlisée dans rechercheCreeNoeudHachage
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);
