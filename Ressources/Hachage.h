#ifndef __HACHAGE_H__
#define __HACHAGE_H__	

#include <stdlib.h>
#include <math.h>
#include "Reseau.h"

typedef struct {
    int nbElement; //pas necessaire ici
    int tailleMax;
    CellNoeud** T;
} TableHachage;

int h( int k,int M);
int f( int x, int y );

//void ajoute_NoeudtableHachage(TableHachage *H,Noeud *n);
void ajoute_NoeudtableHachage( TableHachage *H, Noeud * n,int clée); // utlisée dans rechercheCreeNoeudHachage
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y);
Reseau* reconstitueReseauHachage(Chaines *C, int M);
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage*H, double x, double y);

#endif