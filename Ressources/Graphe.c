#include "Graphe.h"

Arete* creeArete(int u  ,int v){
    Arete * new = (Arete *) malloc(sizeof(Arete));
    if( new == NULL ){
        printf("cannot allocate Arete\n");return NULL;
    }
    new->u = u;new->v = v;
    return new;
}

Cellule_arete* creeCellule_arete( Arete * a){
    Cellule_arete * new = (Cellule_arete *) malloc(sizeof(Cellule_arete));
    if( new == NULL ){
        printf("cannot allocate Cellule_arete\n");return NULL;
    }
   new->a = a;new->suiv = suiv;new->NULL;
   return new;
}

Sommet* creeSommet(int num,double x,double y){
    Sommet* new = (Sommet*) malloc(sizeof(Sommet));
    if( new == NULL ){
        printf("cannot allocate Sommet\n");return NULL;
    }
    new->num = num; new->x = x; new->y = y;
    new->L_voisin = NULL;
    return new;
}

Commod* creeCommod( int e1, int e2){
    Commod* newCommod = malloc(sizeof(Commod));
    if( new == NULL ){
        printf("cannot allocate commod du graphe\n");return NULL;
    }
    new->e1 = e1; new->e2 = e2;
    return new;
}

Graphe *creerGraphe(Reseau *r){
    /* Alloctaion de la structure */
    Graphe* graphe = (Graphe*) malloc(sizeof(Graphe));
    if( graphe == NULL ){
        printf("cannot allocate graphe\n");return NULL;
    }

    /*Initialisation des varibale deja connu */
    graphe->nbsom = r->nbNoeuds;
    graphe->gamma = r->gamma;
    graphe->nbcommod = nbCommodites(r);

                /* Creation de T_som*/

    /*initialisation du tableau*/
    CellNoeud * noeuds = r->noeuds;
    while(noeuds){
        Noeud * actuel = noeuds->nd;
        // creation du sommet assosier a chaque noeud
        Sommet * sommet ;
        if(! graphe->T_som[actuel->num]){ // on verifie que l'on pas deja creer le noeud
        sommet = creeSommet(actuel->num, actuel->x, actuel->y);
        }
        else {  // le sommet existe deja 
            sommet = graphe->T_som[actuel->num];
        }
        


    }
}