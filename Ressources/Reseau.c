#include "Reseau.h"


Reseau * creerReseau(int nbNoeuds ,int gamma){
    Reseau * new = (Reseau *) malloc(sizeof(Reseau));
    if (new == NULL) {
        fprintf(stderr, "Erreur d'allocation memoire pour le reseau\n");
    }
    new->nbNoeuds = nbNoeuds;
    new->gamma = gamma;
    new->noeuds = NULL ;
    new->commodites = NULL;
    return new;
}

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

int nbCommodites(Reseau *R) {
    int nbCommodites = 0;
    CellCommodite *commodite = R->commodites;
    while (commodite != NULL) {
        nbCommodites++;
        commodite = commodite->suiv;
    }
    return nbCommodites;
}

int nbLiaisons(Reseau *R) {
    // Parcourir la liste des noeuds et compter le nombre de voisins de chaque noeud
    int nbLiaisons = 0;
    // Supposons que chaque noeud a une liste de voisins dans la structure Reseau
    // Nous parcourons cette liste et comptons les voisins
    // Ici,  on utilise un compteur pour illustrer le principe
    CellNoeud *noeud = R->noeuds;
    while (noeud != NULL) {
        // Parcourir la liste des voisins du noeud actuel et incrémenter le compteur
        int voisins = 0;
        CellNoeud *voisin = noeud->nd->voisins;
        while (voisin != NULL) {
            voisins++;
            voisin = voisin->suiv;
        }
        // Chaque liaison est comptée deux fois, une fois pour chaque noeud voisin
        nbLiaisons += voisins / 2;
        noeud = noeud->suiv;
    }
    return nbLiaisons;
}

void ecrireReseau(Reseau *R, FILE *f) {
    if (R == NULL || f == NULL) {
        fprintf(stderr, "Erreur : Réseau ou fichier non valide\n");
        return;
    }
    fprintf(f, "NbNoeuds : %d\n NbLiaisons : %d\n NbCommodites : %d\n Gamma : %d\n", R->nbNoeuds, nbLiaisons(R), nbCommodites(R), R->gamma);
    CellNoeud *noeud = R->noeuds;
    while (noeud != NULL) {
        fprintf(f, "v %d %.6f %.6f\n", noeud->nd->num, noeud->nd->x, noeud->nd->y);
        noeud = noeud->suiv;
    }
    noeud = R->noeuds;
    while (noeud != NULL) {
        CellNoeud *voisin = noeud->nd->voisins;
        while (voisin != NULL) {
            if (noeud->nd->num < voisin->nd->num) {
                fprintf(f, "l %d %d\n", noeud->nd->num, voisin->nd->num);
            }
            voisin = voisin->suiv;
        }
        noeud = noeud->suiv;
    }
    CellCommodite *commodite = R->commodites;
    while (commodite != NULL) {
        fprintf(f, "k %d %d\n", commodite->extrA->num, commodite->extrB->num);
        commodite = commodite->suiv;
    }
}

void afficheReseauSVG(Reseau *R, char* nomInstance) {
    if (R == NULL || nomInstance == NULL) {
        fprintf(stderr, "Erreur : Réseau ou nom d'instance non valide\n");
        return;
    }

    // Création du fichier SVG
    FILE *svgFile = fopen(nomInstance, "w");
    if (svgFile == NULL) {
        fprintf(stderr, "Erreur : Impossible de créer le fichier SVG\n");
        return;
    }

    // Écriture de l'en-tête du fichier SVG
    fprintf(svgFile, "<html><body><svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\"");
    fprintf(svgFile, " width=\"100%%\" height=\"100%%\"");
    fprintf(svgFile, " viewBox=\"%d %d %d %d\"", -2, -2, 500, 500);
    fprintf(svgFile, " preserveAspectRatio=\"yes\">\n");
    fprintf(svgFile, "<g >\n\n");

    // Dessiner les liaisons entre les nœuds
    CellNoeud *noeud = R->noeuds;
    while (noeud != NULL) {
        CellNoeud *voisin = noeud->nd->voisins;
        while (voisin != NULL) {
            // Dessiner la liaison entre le nœud courant et son voisin
            fprintf(svgFile, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:black;stroke-width:2\"/>\n",
                    noeud->nd->x, noeud->nd->y, voisin->nd->x, voisin->nd->y);
            voisin = voisin->suiv;
        }
        noeud = noeud->suiv;
    }

    // Dessiner les nœuds du réseau
    noeud = R->noeuds;
    while (noeud != NULL) {
        fprintf(svgFile, "<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" stroke=\"black\" stroke-width=\"1\" fill=\"green\" />\n",
                noeud->nd->x, noeud->nd->y);
        noeud = noeud->suiv;
    }

    // Écriture de la fin du fichier SVG
    fprintf(svgFile, "\n\n</g></svg></body></html>\n");

    // Fermeture du fichier SVG
    fclose(svgFile);
}

