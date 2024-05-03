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
    assert(retrouverChemin(g,6,12) == retrouverChemin(g,12,6));
}

int main(void){
    FILE* f = fopen("05000_USA-road-d-NY.cha", "r");
    Chaines* C = lectureChaines(f);
    fclose(f);
    Reseau* R = reconstitueReseauArbre(C);

    Graphe* g = creerGraphe(R);
    assert(retrouverChemin(g,6,12) == retrouverChemin(g,12,6));
    
    FILE* h = fopen("reecriture","w");
    ecrireReseau(R,h);
    fclose(h);

    affiche_graphe(g, "mon_graphe.dot");
    for( int i = 1; i <=g->nbsom;i++){
        Sommet*p12 = g->T_som[i];
        Cellule_arete* voisins = p12->L_voisin;
        while(voisins){
            printf("{%d,%d} ",voisins->a->u,voisins->a->v);
            voisins = voisins->suiv;
        }
        printf("\n");
    }

    printf("reorganise resaux %d \n",reorganiseReseau(R));
    //afficheListe(retrouverChemin(g,6,12));
    //afficheListe(retrouverChemin(g,12,6));

    liberer_reseau(R);
    libereChaines(C);
    libererGraphe(&g);
    return 0;
}