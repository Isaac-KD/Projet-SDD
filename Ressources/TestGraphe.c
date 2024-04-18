#include "Graphe.h"
#include "Chaine.h"
#include "Hachage.h"

int main(void){
    FILE* f = fopen("00014_burma.cha", "r");
    Chaines* C = lectureChaines(f);
    fclose(f);
    Reseau* R = reconstitueReseauHachage(C,10);
    FILE* h = fopen("reecriture","w");
    ecrireReseau(R,h);
    fclose(h);

    printf("reseau  reconstituer \n");
    Graphe* g = creerGraphe(R);

    printf("graphe construit\n");
    printf(" Graphe est %p \n",g);

    affiche_graphe(g, "mon_graphe.dot");
    for( int i = 1; i <=g->nbsom;i++){
        Sommet*p12 = g->T_som[i];
        Cellule_arete* voisins = p12->L_voisin;
        printf(" Sommet %d",i);
        while(voisins){
            printf("{%d,%d} ",voisins->a->u,voisins->a->v);
            voisins = voisins->suiv;
        }
        printf("\n");
    }
    for( int i=1; i<=g->nbsom;i++){
        for(int j=1; j<=g->nbsom;j++){
            int s = cheminPlusCourt(g,i,j);
            printf(" U=%d V=%d plus court chemin = %d\n",j,i,s2);
        }
    }
    return 0;
}