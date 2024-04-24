#include "ArbreQuat.h"

void testInsererNoeudArbre(){
    ArbreQuat* arbre = creerArbreQuat(0.0, 0.0, 100.0, 100.0);
    Noeud* n1 = creerNoeud(1, -50, -50);
    Noeud* n2 = creerNoeud(2, 50, -50);
    Noeud* n3 = creerNoeud(3, -50, 50);
    Noeud* n4 = creerNoeud(4, 50, 50);
    Noeud* n5 = creerNoeud(5, -25, -25);
    Noeud* n6 = creerNoeud(6, 25, -25);
    Noeud* n7 = creerNoeud(7, -25, 25);
    Noeud* n8 = creerNoeud(8, 25, 25);
    Noeud* n9 = creerNoeud(9, 12.5, 12.5);
    Noeud* n10 = creerNoeud(9, -12.5, 12.5);
    Noeud* n11 = creerNoeud(9, 12.5,- 12.5);
    Noeud* n12 = creerNoeud(9, -12.5, -12.5);
 
    ArbreQuat * abr=arbre;
    insererNoeudArbre(n1, &abr, arbre);
    insererNoeudArbre(n2, &abr, arbre);
    /*
    insererNoeudArbre(n3, &arbre, arbre);
    insererNoeudArbre(n4, &arbre, arbre);
    insererNoeudArbre(n5, &arbre, arbre);
    insererNoeudArbre(n6, &arbre, arbre);
    insererNoeudArbre(n7, &arbre, arbre);
    insererNoeudArbre(n8, &arbre, arbre);
    insererNoeudArbre(n9, &arbre, arbre);
    insererNoeudArbre(n10, &arbre, arbre);
    insererNoeudArbre(n11, &arbre, arbre);
    insererNoeudArbre(n12, &arbre, arbre);
    insererNoeudArbre(n12, &arbre, arbre);
*/
    afficherArbre(arbre, 0);
}

void afficherNoeud(Noeud* n) {
    if (n != NULL) {
        printf("Noeud num: %d, X: %f, Y: %f\n", n->num, n->x, n->y);
    } else {
        printf("Noeud non trouvé.\n");
    }
}

void testerRechercheCreeNoeudArbre() {
    Reseau* R = creerReseau(10); // Assurez-vous que cette fonction initialise le réseau correctement.
    ArbreQuat* arbre = creerArbreQuat(0,0,100,100);
    ArbreQuat*abr = arbre;
    // Test 1: Insertion dans un arbre vide
    Noeud* n1 = rechercheCreeNoeudArbre(R, &abr, arbre, 50.0, 50.0);
    printf("Test 1 - Insertion dans un arbre vide:\n");
    afficherNoeud(n1);
    afficherArbre(arbre, 0);

    // Test 2: Insertion dans une feuille
    Noeud* n2 = rechercheCreeNoeudArbre(R, &abr, arbre, -30.0, -30.0);
    printf("Test 2 - Insertion à une feuille existante:\n");
    afficherNoeud(n2);
    afficherArbre(arbre, 0);

    // Test 3: Vérification de l'existence du noeud
    Noeud* n3 = rechercheCreeNoeudArbre(R, &abr, arbre, 50.0, 50.0);
    printf("Test 3 - Vérification de l'existence du noeud:\n");
    afficherNoeud(n3);
    afficherArbre(arbre, 0);

    // Test 4: Insertion dans une cellule interne
    printf("Test 4 - Insertion dans une cellule interne:\n");
    Noeud* n4 = rechercheCreeNoeudArbre(R, &abr, arbre, 45.0, 45.0);
    afficherNoeud(n4);
    afficherArbre(arbre, 0);
}

int main() {
    testInsererNoeudArbre();

    testerRechercheCreeNoeudArbre() ;
    return 0;
}

