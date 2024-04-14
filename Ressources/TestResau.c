#include "Reseau.h"

int main() {
    // Initialisation du réseau
    Reseau* reseau = (Reseau*)malloc(sizeof(Reseau));
    if (reseau == NULL) {
        fprintf(stderr, "Erreur d'allocation memoire pour le reseau\n");
        return 1;
    }
    reseau->nbNoeuds = 0;
    reseau->noeuds = NULL;

    // Saisie du nombre de nœuds
    int nbNoeuds = 0;
    printf("Entrez le nombre de noeuds a ajouter: ");
    scanf("%d", &nbNoeuds);

    for (int i = 0; i < nbNoeuds; i++) {
        // Saisie des coordonnées du nœud
        double x, y;
        printf("Entrez les coordonnées x et y pour le noeud %d: ", i + 1);
        scanf("%lf %lf", &x, &y);

        // Création du nouveau nœud
        Noeud* noeud = rechercheCreeNoeudListe(reseau, x, y);

        // Lier le nouveau nœud avec tous les nœuds existants
        CellNoeud* current = reseau->noeuds;
        while (current != NULL) {
            if (current->nd != noeud) { // Éviter de se connecter à soi-même
                // Créer une cellule pour le nœud actuel dans la liste des voisins du nouveau nœud
                CellNoeud* newVoisin = (CellNoeud*)malloc(sizeof(CellNoeud));
                newVoisin->nd = current->nd;
                newVoisin->suiv = noeud->voisins;
                noeud->voisins = newVoisin;

                // Créer une cellule pour le nouveau nœud dans la liste des voisins du nœud actuel
                newVoisin = (CellNoeud*)malloc(sizeof(CellNoeud));
                newVoisin->nd = noeud;
                newVoisin->suiv = current->nd->voisins;
                current->nd->voisins = newVoisin;
            }
            current = current->suiv;
        }
    }

    // Affichage du réseau en SVG
    afficheReseauSVG(reseau, "test.svg");

    free(reseau);
    return 0;
}

/*
int main() {
    // Initialisation du réseau
    Reseau* reseau = (Reseau*)malloc(sizeof(Reseau));
    if (reseau == NULL) {
        fprintf(stderr, "Erreur d'allocation memoire pour le reseau\n");
        return 1;
    }
    reseau->nbNoeuds = 0;
    reseau->noeuds = NULL;

    // Saisie du nombre de nœuds
    int nbNoeuds = 0;
    printf("Entrez le nombre de noeuds a ajouter: ");
    scanf("%d", &nbNoeuds);

    for (int i = 0; i < nbNoeuds; i++) {
        // Saisie des coordonnées du nœud
        double x, y;
        printf("Entrez les coordonnées x et y pour le noeud %d: ", i + 1);
        scanf("%lf %lf", &x, &y);

        // Création du nouveau nœud
        Noeud* noeud = rechercheCreeNoeudListe(reseau, x, y);

        // Lier le nouveau nœud avec tous les nœuds existants
        CellNoeud* current = reseau->noeuds;
        while (current != NULL) {
            if (current->nd != noeud) { // Éviter de se connecter à soi-même
                // Créer une cellule pour le nœud actuel dans la liste des voisins du nouveau nœud
                CellNoeud* newVoisin = (CellNoeud*)malloc(sizeof(CellNoeud));
                newVoisin->nd = current->nd;
                newVoisin->suiv = noeud->voisins;
                noeud->voisins = newVoisin;

                // Créer une cellule pour le nouveau nœud dans la liste des voisins du nœud actuel
                newVoisin = (CellNoeud*)malloc(sizeof(CellNoeud));
                newVoisin->nd = noeud;
                newVoisin->suiv = current->nd->voisins;
                current->nd->voisins = newVoisin;
            }
            current = current->suiv;
        }
    }

    // Affichage du réseau en SVG
    afficheReseauSVG(reseau, "test.svg");

    free(reseau);
    return 0;
}
*/