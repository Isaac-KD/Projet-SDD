#include "../include/Reseau.h"
#include <assert.h>

void test_creerReseau() {
    Reseau *res = creerReseau(5);
    assert(res != NULL);
    assert(res->nbNoeuds == 0);
    assert(res->gamma == 5);
    assert(res->noeuds == NULL);
    assert(res->commodites == NULL);
    liberer_reseau(res);
    printf("Test creerReseau passed.\n");
}

void test_creerNoeud() {
    Noeud *n = creerNoeud(1, 1.0, 2.0);
    assert(n != NULL);
    assert(n->num == 1);
    assert(n->x == 1.0);
    assert(n->y == 2.0);
    assert(n->voisins == NULL);
    liberer_noeud(n);
    printf("Test creerNoeud passed.\n");
}

void test_creerCellNoeud() {
    Noeud *n = creerNoeud(1, 1.0, 2.0);
    CellNoeud *cn = creerCellNoeud(n);
    assert(cn != NULL);
    assert(cn->nd == n);
    assert(cn->suiv == NULL);
    liberer_liste_CellNoeud(cn); // This also frees the Noeud
    printf("Test creerCellNoeud passed.\n");
}

void test_creerCellCommodite() {
    Noeud *a = creerNoeud(1, 1.0, 2.0);
    Noeud *b = creerNoeud(2, 3.0, 4.0);
    CellCommodite *cc = creerCellCommodite(a, b);
    assert(cc != NULL);
    assert(cc->extrA == a);
    assert(cc->extrB == b);
    assert(cc->suiv == NULL);
    liberer_liste_CellCommodite(cc);
    liberer_noeud(a);
    liberer_noeud(b);
    printf("Test creerCellCommodite passed.\n");
}

void test_rechercheCreeNoeudListe() {
    Reseau *R = creerReseau(3);
    Noeud *n1 = rechercheCreeNoeudListe(R, 1.0, 2.0);
    assert(n1 != NULL);
    assert(R->nbNoeuds == 1);
    assert(n1->x == 1.0 && n1->y == 2.0);

    // Test de recherche du même nœud
    Noeud *n2 = rechercheCreeNoeudListe(R, 1.00001, 2.00001);
    assert(n2 == n1);  // Doit retourner le même noeud, pas un nouveau
    assert(R->nbNoeuds == 1);  // Le nombre de noeuds ne doit pas augmenter

    liberer_reseau(R);
    printf("Test rechercheCreeNoeudListe passed.\n");
}

void test_insererReseau() {
    Reseau *R = creerReseau(3);
    Noeud *n = insererReseau(R, 3.0, 4.0);
    assert(n != NULL);
    assert(R->nbNoeuds == 1);
    assert(n->x == 3.0 && n->y == 4.0);
    assert(R->noeuds != NULL && R->noeuds->nd == n);

    liberer_reseau(R);
    printf("Test insererReseau passed.\n");
}

void test_reconstitueReseauListe() {
    FILE *f = fopen("00014_burma.cha","r");
    Chaines* C = lectureChaines(f);
    Reseau *R = reconstitueReseauListe(C);
    
    // Vérifier les détails du réseau créé
    assert(R != NULL);
    assert(R->nbNoeuds == 12);
    assert(R->gamma == 3);
    assert( nbCommodites(R)==8);
    assert(nbLiaisons(R));

    liberer_reseau(R);
    printf("Test reconstitueReseauListe passed.\n");
}

int main() {
    printf("Début des tests...\n");

    test_creerReseau();
    test_creerNoeud();
    test_creerCellNoeud();
    test_creerCellCommodite();
    test_rechercheCreeNoeudListe();
    test_insererReseau();
    test_reconstitueReseauListe(); //test aussin nbLiaisons et nbCommodites

    printf("Tous les tests sont passés avec succès.\n");

    return 0;
}

