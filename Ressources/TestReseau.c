#include <assert.h>
#include <stdio.h>
#include "Reseau.h"

void test_creerReseauValidGamma() {
    Reseau* R = creerReseau(5);
    assert(R != NULL);
    assert(R->gamma == 5);
    assert(R->nbNoeuds == 0);
    assert(R->noeuds == NULL);
    assert(R->commodites == NULL);
    free(R);
    printf("test_creerReseauValidGamma passed\n");
}

void test_creerReseauNegativeGamma() {
    Reseau* R = creerReseau(-1);
    assert(R != NULL);
    assert(R->gamma == -1);
    free(R);
    printf("test_creerReseauNegativeGamma passed\n");
}

void test_creerReseauZeroGamma() {
    Reseau* R = creerReseau(0);
    assert(R != NULL);
    assert(R->gamma == 0);
    free(R);
    printf("test_creerReseauZeroGamma passed\n");
}

void test_creerNoeudValidInput() {
    Noeud* n = creerNoeud(1, 100.0, 200.0);
    assert(n != NULL);
    assert(n->num == 1);
    assert(n->x == 100.0);
    assert(n->y == 200.0);
    assert(n->voisins == NULL);
    free(n);
    printf("test_creerNoeudValidInput passed\n");
}

void test_creerNoeudCheckInitialVoisinsNull() {
    Noeud* n = creerNoeud(2, 50.0, 50.0);
    assert(n->voisins == NULL);
    free(n);
    printf("test_creerNoeudCheckInitialVoisinsNull passed\n");
}

void test_insererVoisinsBothNonNull() {
    Noeud* n1 = creerNoeud(1, 0.0, 0.0);
    Noeud* n2 = creerNoeud(2, 1.0, 1.0);
    insererVoisins(n1, n2);
    assert(n1->voisins != NULL);
    assert(n2->voisins != NULL);
    assert(n1->voisins->nd == n2);
    assert(n2->voisins->nd == n1);
    free(n1);
    free(n2);
    printf("test_insererVoisinsBothNonNull passed\n");
}

void test_insererVoisinsFirstNodeNull() {
    Noeud* n2 = creerNoeud(2, 1.0, 1.0);
    insererVoisins(NULL, n2);
    assert(n2->voisins == NULL);
    free(n2);
    printf("test_insererVoisinsFirstNodeNull passed\n");
}

void test_insererVoisinsSecondNodeNull() {
    Noeud* n1 = creerNoeud(1, 0.0, 0.0);
    insererVoisins(n1, NULL);
    assert(n1->voisins == NULL);
    free(n1);
    printf("test_insererVoisinsSecondNodeNull passed\n");
}


void test_creerCellNoeudValidInput() {
    Noeud* n = creerNoeud(1, 100.0, 200.0);
    CellNoeud* cn = creerCellNoeud(n);
    assert(cn != NULL);
    assert(cn->nd == n);
    assert(cn->suiv == NULL);
    free(n);
    free(cn);
    printf("test_creerCellNoeudValidInput passed\n");
}

void test_creerCellCommoditeValidInput() {
    Noeud* a = creerNoeud(1, 0.0, 0.0);
    Noeud* b = creerNoeud(2, 1.0, 1.0);
    CellCommodite* cc = creerCellCommodite(a, b);
    assert(cc != NULL);
    assert(cc->extrA == a);
    assert(cc->extrB == b);
    assert(cc->suiv == NULL);
    free(a);
    free(b);
    free(cc);
    printf("test_creerCellCommoditeValidInput passed\n");
}
int main() {
    test_creerReseauValidGamma();
    test_creerReseauNegativeGamma();
    test_creerReseauZeroGamma();
    test_creerNoeudValidInput();
    test_creerNoeudCheckInitialVoisinsNull();
    test_insererVoisinsBothNonNull();
    test_insererVoisinsFirstNodeNull();
    test_insererVoisinsSecondNodeNull();
    test_creerCellNoeudValidInput();
    test_creerCellCommoditeValidInput();
    return 0;
}
