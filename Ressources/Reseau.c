#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Reseau.h"

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud *noeud = R->noeuds;
    while(noeud != NULL){
        if(noeud->nd->x == x && noeud->nd->y == y){
            return noeud->nd;
        }
        noeud = noeud->suiv;
    }
    Noeud* noeud2 = (Noeud*)malloc(sizeof(Noeud));
    if(noeud2 == NULL){
        fprintf(stderr, "Erreur d'allocation mémoire du noeud");
        exit(EXIT_FAILURE);
    }
    noeud2->num = R->nbNoeuds;
    R->nbNoeuds++;

    noeud2->x = x;
    noeud2->y = y;
    noeud2->voisins = NULL;

    CellNoeud* cellnoeud = (CellNoeud*)malloc(sizeof(CellNoeud));
    if(cellnoeud == NULL){
        fprintf(stderr, "Erreur d'allocation mémoire de cellnoeud");
        exit(EXIT_FAILURE);
    }
    cellnoeud->nd = noeud2;
    cellnoeud->suiv = R->noeuds;
    R->noeuds = cellnoeud;

    return noeud2;
}


Reseau* reconstitueReseauListe(Chaines *C) {
    // Création d'un nouveau réseau
    Reseau *R = (Reseau*)malloc(sizeof(Reseau));
    if (R == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le réseau\n");
        exit(EXIT_FAILURE);
    }
    R->noeuds = NULL;
    R->commodites = NULL;
    R->gamma = C->gamma;
    R->nbNoeuds = 0; // Initialiser le nombre de nœuds à zéro

    // Parcourir chaque chaîne dans la liste des chaînes
    for (int i = 0; i < C->nbChaines; i++) {
        CellChaine *chaine = &(C->chaines[i]);
        CellPoint *point = chaine->points;
        Noeud *prevNoeud = NULL;

        // Parcourir chaque point de la chaîne
        while (point != NULL) {
            // Rechercher ou créer un nœud correspondant au point actuel
            Noeud *noeud = rechercheCreeNoeudListe(R, point->x, point->y);

            // Ajouter le nœud à la liste des nœuds du réseau
            if (prevNoeud != NULL) {
                // Ajouter une liaison entre le nœud précédent et le nœud actuel
                CellNoeud *celluleVoisin = (CellNoeud*)malloc(sizeof(CellNoeud));
                if (celluleVoisin == NULL) {
                    fprintf(stderr, "Erreur d'allocation mémoire pour une nouvelle cellule de nœud\n");
                    exit(EXIT_FAILURE);
                }
                celluleVoisin->nd = noeud;
                celluleVoisin->suiv = prevNoeud->voisins;
                prevNoeud->voisins = celluleVoisin;

                // Ajouter une liaison dans l'autre sens
                celluleVoisin = (CellNoeud*)malloc(sizeof(CellNoeud));
                if (celluleVoisin == NULL) {
                    fprintf(stderr, "Erreur d'allocation mémoire pour une nouvelle cellule de nœud\n");
                    exit(EXIT_FAILURE);
                }
                celluleVoisin->nd = prevNoeud;
                celluleVoisin->suiv = noeud->voisins;
                noeud->voisins = celluleVoisin;
            }

            prevNoeud = noeud;
            point = point->suiv;
        }
    }

    return R;
}

int main(){
	return 0;
}