#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Chaine.h"
#include "../include/ArbreQuat.h"
#include "../include/Hachage.h"
#include "../include/Chaine.h"
#include "../include/Reseau.h"

void utiliserListe(char* filename) {
    printf("Utilisation d'une liste pour le fichier %s\n", filename);
    FILE* f = fopen(filename, "r");
    Chaines* C = lectureChaines(f);
    affiche_CellChaine(C->chaines,NULL);
    Reseau* R = reconstitueReseauListe(C);
    afficheReseauSVG(R,"reconstitueReseauListe.html");
}

void utiliserTableHachage(char* filename) {
    printf("Utilisation d'une table de hachage pour le fichier %s\n", filename);
    FILE* f = fopen("00014_burma.cha", "r");
    Chaines* C = lectureChaines(f);
    affiche_CellChaine(C->chaines,NULL);
    Reseau* R =reconstitueReseauHachage(C,100);
    afficheReseauSVG(R,"reconstitueReseauHachage.html");
}

void utiliserArbre(char* filename) {
    printf("Utilisation d'un arbre pour le fichier %s\n", filename);
    FILE* f = fopen(filename, "r");
    Chaines* C = lectureChaines(f);
    Reseau* R =reconstitueReseauArbre(C);
    afficheReseauSVG(R,"reconstitueReseauArbre.html");
}

int main() {

    char filename[256];
    printf("Fichier source pour la reconstitution : ");
    scanf("%s", filename);
    int choix;

    printf("Choisissez la méthode de gestion des données :\n");
    printf("1. Liste\n");
    printf("2. Table de hachage\n");
    printf("3. Arbre\n");
    printf("Entrez votre choix (1, 2 ou 3) : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            utiliserListe(filename);
            break;
        case 2:
            utiliserTableHachage(filename);
            break;
        case 3:
            utiliserArbre(filename);
            break;
        default:
            fprintf(stderr, "Choix non valide. Veuillez entrer 1, 2 ou 3.\n");
            return 2;
    }

    return 0;
}

