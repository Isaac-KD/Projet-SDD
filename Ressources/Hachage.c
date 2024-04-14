#include "Hachage.h"

int h( int k,int M){
    double A=(sqrt(5)-1)/2.0;
    return (int)(fabs(M*(k*A-fabs(k*A))));// le cast en int n'est pas nécessaire 
}

int f( int x, int y ){ // oui cette fonction est appropier elle repartide maniere asser uniformement les valeurs.
    return (int)((y+(x+y)*(x+y+1))/2);
}

void ajoute_NoeudtableHachage( TableHachage *H, Noeud * n,int clée){
    CellNoeud *liste = H->T[clée];
    CellNoeud *prec = NULL;
    CellNoeud *nouveau;
    int x = n->x; int y = n->y;

    // Parcourir la liste à la recherche du point ou pour s'assurer de l'unicité
    while (liste) {
        if (liste->nd->x == x && liste->nd->y == y) {
            return;  // Noeud déjà présent, on ne l'ajoute pas
        }
        prec = liste;
        liste = liste->suiv;
    }

    // Création du nouveau CellNoeud
    nouveau = malloc(sizeof(CellNoeud));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour un nouveau CellNoeud\n");
        return;
    }
    nouveau->nd = n;
    nouveau->suiv = NULL;

    // Insertion du nouveau CellNoeud dans la liste
    if (prec == NULL) {
        H->T[clée] = nouveau;  // Insertion en tête de liste
    } else {
        prec->suiv = nouveau;  // Insertion après le précédent
    }
    H->nbElement++;
}


Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage*H, double x, double y){
    int M= H->tailleMax;
    int K = f(x,y);
    int clée = h(K,M);
    Noeud * noeud=rechercheCreeNoeudListe(R, x, y);
    ajoute_NoeudtableHachage(H,noeud,clée);
    return noeud;
}

Reseau* reconstitueReseauHachage(Chaines *C, int M){
    // creation de la table de hashage
    TableHachage *H = (TableHachage *)malloc(sizeof(TableHachage));
    H->tailleMax = M;
    H->nbElement = 0;
    H->T = NULL;

    //A optimiser avec reconstitueReseauListe
    Reseau * R = reconstitueReseauListe(C);
    CellChaine* pch = C->chaines;
    while(pch){
        CellPoint * pcn = pch->points;
        while(pcn){
            rechercheCreeNoeudHachage(R,H,pcn->x,pcn->y); 
            pcn=pcn->suiv;
        }
        pch=pch->suiv;  
    }
    return R;
}
