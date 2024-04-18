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
   new->a = a;new->suiv = NULL;
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
    graphe->T_som = (Sommet**)malloc(sizeof(Sommet*)*(graphe->nbsom+1));
    if( graphe->T_som == NULL ){
        printf("cannot allocate graphe->T_som \n");return NULL;
    }
    // tableau de taille nbNoeud+1 pour que ce soit plus partique lors de l'association d'un noeud dans le tableau
    for( int i = 0; i < graphe->nbsom+1;i++ ){ // on initialise le tableau a NULL
        graphe->T_som[i] = NULL;
    }
    /* Initialisation du tabeau de commodités */
    graphe->T_commod = malloc(graphe->nbcommod * sizeof(Commod));
    if (!graphe->T_commod) {
        free(graphe);
        return NULL;
    }

                /* Creation de T_som*/
    /*initialisation du tableau*/
    CellNoeud * noeuds = r->noeuds;
    while(noeuds){
        Noeud * actuel = noeuds->nd;
        // creation du sommet assosier a chaque noeud
        Sommet * sommet = creeSommet(actuel->num, actuel->x, actuel->y);
        graphe->T_som[actuel->num] = sommet;

        // assosiation des noeuds voisins
        CellNoeud * voisins = actuel->voisins;
        while(voisins){
            Sommet* sommetVoisins = graphe->T_som[voisins->nd->num];
            if( sommetVoisins ){ // si le sommet existe dans le graphe alors on cree les aretes
                Arete* a = creeArete(sommet->num,sommetVoisins->num) ;// on cree l'arete entre le sommet initial et le sommet voisins
                Cellule_arete* cellS = creeCellule_arete(a); // cellule pour le sommet initial
                Cellule_arete* cellSV = creeCellule_arete(a);// cellule pour le sommet voisins

                /* On implement les Cellule_arete dans le sommet */
                cellS->suiv = sommet->L_voisin;
                sommet->L_voisin = cellS;
                /* On implement les Cellule_arete dans le sommet voisins */
                cellSV->suiv = sommetVoisins->L_voisin;
                sommet->L_voisin = cellSV;
            }
            voisins = voisins->suiv;
        }

        /* On passe au noeud suivant */
        noeuds = noeuds->suiv;
    }

    /* Creation de la commodite */
    CellCommodite * commoditeActuel = r->commodites;
   for(int i = 0; i <graphe->nbcommod; i++){
        graphe->T_commod[i].e1 = commoditeActuel ->extrA->num;
        graphe->T_commod[i].e2 = commoditeActuel ->extrB->num;
        commoditeActuel = commoditeActuel ->suiv;
   }
    return graphe;
}