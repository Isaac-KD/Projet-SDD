#include <stdlib.h>
#include <math.h>
#include "Hachage.h"
#include "Reseau.h"
#include <random.h>

int h( int k,int M){
    double A=(sqrt(5)-1)/2.0 
    return int(abs(M*(k*A-abs(k*A))));// le cast en int n'est pas nécessaire 
}

int f( int x, int y ){ // oui cette fonction est appropier elle repartide maniere asser uniformement les valeurs.
    return (int)((y+(x+y)*(x+y+1))/2);
}

void ajoute_NoeudtableHachage( TableHachage *H, Noeud * n,int clée){
    H->T[clée] = liste;
    Noeud * prec = NULL;
    while(liste){
        prec = liste
        if (liste->nd->x == x) && (liste->nd->y == y) ; return;
        liste = liste->suiv;
    }
    prec->suiv = n;
    H->nbElement++;
}

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage*H, double x, double y){
    int M= H->tailleMax;
    int K = f(x,y);
    int clée = h(K,M);
    Noeud * noeud=rechercheCreeNoeudListe(R, x, y);
    ajoute_NoeuxTableHachage(H,noeud,clée);
    return noeud;
}

Reseau* reconstitueReseauHachage(Chaines *C, int M){
    // creation de la table de hashage
    TableHachage *H = (TableHachage *)malloc(sizeof(TableHachage));
    H->tailleMax = M;
    H->nbElement = 0;
    H->T = NULL

    //A optimiser avec reconstitueReseauListe
    Reseau * R = reconstitueReseauListe(C);
    pch = C->chanes;
    while(pch){
        pcn = pch->points;
        while(pcn){
            rechercheCreeNoeudHachage(R,H,pcn->x,pcn->y); 
            pcn=pcn->suiv
        }
        pch=pch->suiv
}

}
int main(){
    return 0;
}