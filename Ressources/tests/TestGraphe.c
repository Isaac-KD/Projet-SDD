#include "../include/Graphe.h"
#include "../include/Chaine.h"
#include "../include/ArbreQuat.h"
#include <assert.h>
void test_retrouverChemin(){
    FILE* f = fopen("05000_USA-road-d-NY.cha", "r");
    Chaines* C = lectureChaines(f);
    fclose(f);
    Reseau* R = reconstitueReseauArbre(C);

    Graphe* g = creerGraphe(R);
    //assert(retrouverChemin(g,6,12) == retrouverChemin(g,12,6));
}

int main(void){
    FILE* f = fopen("00014_burma.cha", "r");
    Chaines* C = lectureChaines(f);
    fclose(f);
    Reseau* R = reconstitueReseauArbre(C);

    Graphe* g = creerGraphe(R);
    assert( cheminPlusCourt(g,12,6) == cheminPlusCourt(g,6,12));
    Liste*l = retrouverChemin(g,6,12);
    afficheListe(l);
    libereListe(l);
    
    FILE* h = fopen("reecriture.txt","w");
    ecrireReseau(R,h);
    fclose(h);

    affiche_graphe(g, "mon_graphe.dot");

    printf("reorganise resaux %d \n",reorganiseReseau(R));

    liberer_reseau(R);
    libereChaines(C);
    libererGraphe(&g);
    return 0;
}