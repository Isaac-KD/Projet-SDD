#include "Graphe.h"
#include "Chaine.h"
#include "Hachage.h"

int main(void){
    FILE* f = fopen("00014_burma.cha", "r");
    Chaines* C = lectureChaines(f);
    fclose(f);
    Reseau* R = reconstitueReseauHachage(C,10);
    printf("reseau  reconstituer \n");
    Graphe* g = creerGraphe(R);
    printf("graphe construit\n");
    printf(" Graphe est %p \n",g);
    return 0;
}