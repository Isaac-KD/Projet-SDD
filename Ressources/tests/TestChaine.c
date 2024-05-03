#include "../include/Chaine.h"
#include <assert.h>

void test_creer_Cellpoint() {
    CellPoint* point = creer_Cellpoint(1.0, 2.0);
    assert(point != NULL);
    assert(fabs(point->x - 1.0) < 1e-6);
    assert(fabs(point->y - 2.0) < 1e-6);
    assert(point->suiv == NULL);
    libereCellPoint(point);
    printf("test_creer_Cellpoint passed.\n");
}

void test_creer_Cellchaine() {
    CellPoint* point = creer_Cellpoint(3.0, 4.0);
    CellChaine* chaine = creer_Cellchaine(1, point);
    assert(chaine != NULL);
    assert(chaine->numero == 1);
    assert(chaine->points == point);
    assert(chaine->suiv == NULL);
    libereCellChaine(chaine);
    printf("test_creer_Cellchaine passed.\n");
}

void test_creer_Chaines() {
    CellChaine* chaine = creer_Cellchaine(5, NULL);
    Chaines* chaines = creer_Chaines(10, 1, chaine);
    assert(chaines != NULL);
    assert(chaines->gamma == 10);
    assert(chaines->nbChaines == 1);
    assert(chaines->chaines == chaine);
    libereChaines(chaines);
    printf("test_creer_Chaines passed.\n");
}

void test_ajoute_point_cellpoint() {
    CellPoint* start = NULL;
    ajoute_point_cellpoint(&start, 5.0, 6.0);
    assert(start != NULL);
    assert(fabs(start->x - 5.0) < 1e-6);
    assert(fabs(start->y - 6.0) < 1e-6);
    ajoute_point_cellpoint(&start, 7.0, 8.0);
    assert(start->suiv != NULL);
    assert(fabs(start->suiv->x - 5.0) < 1e-6);
    assert(fabs(start->suiv->y - 6.0) < 1e-6);
    libereCellPoint(start);
    printf("test_ajoute_point_cellpoint passed.\n");
}

void test_ajoute_cellpoint_cellchaine() {
    CellChaine* listeChaine = NULL;
    CellPoint* point = creer_Cellpoint(10.0, 20.0);

    // Test adding first CellChaine
    ajoute_cellpoint_cellchaine(&listeChaine, 1, point);
    assert(listeChaine != NULL);
    assert(listeChaine->numero == 1);
    assert(listeChaine->points == point);
    assert(listeChaine->suiv == NULL);

    // Test adding second CellChaine
    CellPoint* anotherPoint = creer_Cellpoint(30.0, 40.0);
    ajoute_cellpoint_cellchaine(&listeChaine, 2, anotherPoint);
    assert(listeChaine->numero== 2);
    assert(listeChaine->suiv->numero == 1);
    assert(listeChaine->suiv->points == point);
    assert(listeChaine->suiv->suiv == NULL);

    // Clean
    libereCellChaine(listeChaine);

    printf("test_ajoute_cellpoint_cellchaine passed.\n");
}

void test_ajoute_cellchaine_cellchaine() {
    CellChaine* root = NULL;
    CellChaine* firstChaine = creer_Cellchaine(1, NULL);
    CellChaine* secondChaine = creer_Cellchaine(2, NULL);

    // Test adding first CellChaine
    ajoute_cellchaine_cellchaine(&root, firstChaine);
    assert(root == firstChaine);
    assert(root->numero == 1);
    assert(root->suiv == NULL);

    // Test adding second CellChaine
    ajoute_cellchaine_cellchaine(&root, secondChaine);
    assert(root->suiv == firstChaine);
    assert(root->suiv->numero == 1);
    assert(root->suiv->suiv == NULL);

    // Cleanup
    libereCellChaine(root);

    printf("test_ajoute_cellchaine_cellchaine passed.\n");
}

void test_taille_CellPoint() {
    CellPoint* start = NULL;
    ajoute_point_cellpoint(&start, 9.0, 10.0);
    ajoute_point_cellpoint(&start, 11.0, 12.0);
    int size = taille_CellPoint(start);
    assert(size == 2);
    
    libereCellPoint(start);
    printf("test_taille_CellPoint passed.\n");
}

Chaines* create_sample_chaine() {
    CellPoint* point1 = creer_Cellpoint(1.0, 2.0);
    ajoute_point_cellpoint(&point1, 3.0, 4.0);  // Ajout d'un deuxième point
    ajoute_point_cellpoint(&point1, 4.0, 9.2); 
    CellChaine* chaine = creer_Cellchaine(1, point1);
    Chaines* chaines = creer_Chaines(10, 1, chaine);
    return chaines;
}

void test_longueurChaine() {
    CellPoint *p1 = creer_Cellpoint(0, 0);
    ajoute_point_cellpoint(&p1, 3, 4);  // Ajoute le point (3,4) pour former une ligne droite

    CellChaine *chaine = creer_Cellchaine(1, p1);
    double length = longueurChaine(chaine);
    assert(fabs(length - 5.0) < 1e-6);  // Distance de Pythagore: sqrt((3-0)^2 + (4-0)^2) = 5
    printf("test_longueurChaine passed.\n");

    // Nettoyage
    libereCellChaine(chaine);
}

void test_longueurTotale() {
    CellPoint *p1 = creer_Cellpoint(0, 0);
    ajoute_point_cellpoint(&p1, 3, 4);
    CellChaine *chaine = creer_Cellchaine(1, p1);

    Chaines *C = creer_Chaines(1, 1, chaine);  
    double totalLength = longueurTotale(C);
    assert(fabs(totalLength - 5.0) < 1e-6);
    printf("test_longueurTotale passed.\n");

    libereChaines(C);
}

void test_comptePointsTotal() {
    CellPoint *p1 = creer_Cellpoint(0, 0);
    ajoute_point_cellpoint(&p1, 1, 1);
    ajoute_point_cellpoint(&p1, 2, 2);

    CellChaine *chaine = creer_Cellchaine(1, p1);
    Chaines *C = creer_Chaines(1, 1, chaine);
    int totalPoints = comptePointsTotal(C);
    assert(totalPoints == 3);
    printf("test_comptePointsTotal passed.\n");

    libereChaines(C);
}

void test_changeMinMax() {
    double xmin = 1000, ymin = 1000, xmax = 0, ymax = 0;
    changeMinMax(2000, 2000, &xmin, &ymin, &xmax, &ymax);
    assert(xmax ==2000 && ymax == 2000 && xmin == 1000 && ymin == 1000);  // Initial min should not change
    changeMinMax(-1, -1, &xmin, &ymin, &xmax, &ymax);
    assert(xmin == -1 && ymin == -1);  // New min values
    printf("test_changeMinMax passed.\n");
}

void test_chaineCoordMinMax() {
    CellPoint *p1 = creer_Cellpoint(0, 0);
    ajoute_point_cellpoint(&p1, -10, -10);
    ajoute_point_cellpoint(&p1, 10, 10);

    CellChaine *chaine = creer_Cellchaine(1, p1);
    Chaines *C = creer_Chaines(1, 1, chaine);
    double xmin = 0, ymin = 0, xmax = 0, ymax = 0;
    chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
    assert(xmin == -10 && ymin == -10 && xmax == 10 && ymax == 10);
    printf("test_chaineCoordMinMax passed.\n");

    libereChaines(C);
}

void test_generationAleatoire() {
    int nbChaines = 5;
    int nbPointsChaine = 10;
    int xmax = 100;
    int ymax = 100;

    // Appel de la fonction à tester
    Chaines *result = generationAleatoire(nbChaines, nbPointsChaine, xmax, ymax);

    // Test de l'intégrité des chaînes générées
    assert(result != NULL);
    assert(result->nbChaines == nbChaines);
    assert(result->gamma >= 1 && result->gamma <= 20);

    // Itération sur chaque chaîne
    CellChaine *chaineCourante = result->chaines;
    for (int i = 0; i < nbChaines; i++) {
        assert(chaineCourante != NULL);
        CellPoint *pointCourant = chaineCourante->points;
        
        // Itération sur chaque point de la chaîne
        for (int j = 0; j < nbPointsChaine; j++) {
            assert(pointCourant != NULL);
            assert(pointCourant->x >= 0 && pointCourant->x <= xmax);
            assert(pointCourant->y >= 0 && pointCourant->y <= ymax);
            pointCourant = pointCourant->suiv;
        }
        chaineCourante = chaineCourante->suiv;
    }
    libereChaines(result);
}

int main() {
    test_creer_Cellpoint();
    test_creer_Cellchaine();
    test_creer_Chaines();
    test_ajoute_point_cellpoint();
    test_ajoute_cellpoint_cellchaine();
    test_ajoute_cellchaine_cellchaine();
    test_taille_CellPoint();
    test_longueurChaine();
    test_longueurTotale();
    test_comptePointsTotal();
    test_changeMinMax();
    test_chaineCoordMinMax();
    test_generationAleatoire();
    FILE *f = fopen("00014_burma.cha","r");
    Chaines * c = lectureChaines(f);
    ecrireChaines(c,f); 
    fclose(f);
    FILE *g = fopen("tmp","w");
    ecrireChaines(c,g);
    fclose(g);
    //libereChaines(c);
    printf("Tous les tests sont passés avec succès.\n");
    return 0;

}
