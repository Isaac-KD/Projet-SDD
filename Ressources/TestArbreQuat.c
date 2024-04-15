#include "ArbreQuat.h"

int main() {
    // Création d'un arbre quaternaire initial, centré en (50, 50) avec une taille de 100x100
    ArbreQuat* arbre = creerArbreQuat(50, 50, 100, 100);

    // Création et insertion de nœuds à différentes positions
    Noeud* n1 = malloc(sizeof(Noeud)); n1->x = 25; n1->y = 25; n1->voisins = NULL; // Sud-ouest
    Noeud* n2 = malloc(sizeof(Noeud)); n2->x = 75; n2->y = 25; n2->voisins = NULL; // Sud-est
    Noeud* n3 = malloc(sizeof(Noeud)); n3->x = 25; n3->y = 75; n3->voisins = NULL; // Nord-ouest
    Noeud* n4 = malloc(sizeof(Noeud)); n4->x = 75; n4->y = 75; n4->voisins = NULL; // Nord-est
    Noeud* n5 = malloc(sizeof(Noeud)); n5->x = 0;  n5->y = 0;  n5->voisins = NULL;  // Extrême Sud-ouest
    Noeud* n6 = malloc(sizeof(Noeud)); n6->x = 50; n6->y = 50; n6->voisins = NULL; // Centre exact

    // Insertion des nœuds
    insererNoeudArbre(n1, &arbre, arbre);
    insererNoeudArbre(n2, &arbre, arbre);
    insererNoeudArbre(n3, &arbre, arbre);
    insererNoeudArbre(n4, &arbre, arbre);
    insererNoeudArbre(n5, &arbre, arbre);
    insererNoeudArbre(n6, &arbre, arbre);

    // Affichage pour vérifier la structure de l'arbre
    printf("Structure de l'arbre après insertion:\n");
    afficherArbre(arbre, 0);

    // Nettoyage de la mémoire
    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);
    free(n6);
    // Ajouter ici la libération des autres sous-arbres si nécessaire
    free(arbre);

    return 0;
}

