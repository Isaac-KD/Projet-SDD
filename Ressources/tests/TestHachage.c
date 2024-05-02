#include "../include/Hachage.h"
#include <assert.h>

void test_rechercheCreeNoeudHachage() {
    Reseau* R = creerReseau(5);  
    TableHachage* H = (TableHachage*)malloc(sizeof(TableHachage));  
    int M= 20;
    H->tailleMax = M;
    H->nbElement = 0;
   // Allocation de mémoire pour le tableau de pointeurs
    H->T = malloc(M * sizeof(CellNoeud*));
    if (H->T == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le tableau de pointeurs.\n");
        return;
    }
    // Initialisation des éléments du tableau à NULL
    for (int i = 0; i < M; i++) {
        H->T[i] = NULL;
    }
    Noeud* n1 = rechercheCreeNoeudHachage(R, H, 1.0, 2.0);
    assert(n1 != NULL);  // Vérifie que le nœud a été créé

    Noeud* n2 = rechercheCreeNoeudHachage(R, H, 1.0, 2.0);
    assert(n1 == n2);  // Vérifie que le même nœud est retourné pour les mêmes coordonnées

    liberer_reseau(R);  // Nettoyage
    libererTableHachage(H);  // Nettoyage
}

void test_reconstitueReseauHachage() {
    FILE *f = fopen("00014_burma.cha","r");
    Chaines* C = lectureChaines(f);
    Reseau* R = reconstitueReseauHachage(C, 10);
    
    // Vérifier les détails du réseau créé
    assert(R != NULL);
    assert(R->nbNoeuds == 12);
    assert(R->gamma == 3);
    assert( nbCommodites(R)==8);
    assert(nbLiaisons(R));

    liberer_reseau(R);
    printf("Test reconstitueReseauListe passed.\n");
}

int main(){
    test_rechercheCreeNoeudHachage();
    test_reconstitueReseauHachage();
    printf("Tous les tests sont passés avec succès.\n");
    return 0;
}