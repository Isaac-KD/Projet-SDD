#include "Hachage.h"

int h( int k,int M){
    double A=(sqrt(5)-1)/2.0;
    return (int)(fabs(M*(k*A-fabs(k*A))));// le cast en int n'est pas nécessaire 
}

int f( int x, int y ){ // oui cette fonction est appropier elle repartide maniere asser uniformement les valeurs.
    return (int)((y+(x+y)*(x+y+1))/2);
}

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage*H, double x, double y){
    int M= H->tailleMax;
    int K = f(x,y);
    int clée = h(K,M)%M; //
    CellNoeud *liste = H->T[clée];
    
    /* Verification de si le noeud est deja present */
    while (liste) {
        if (liste->nd->x == x && liste->nd->y == y) {
            return liste->nd;  // Noeud déjà présent, on ne l'ajoute pas
        }
        liste = liste->suiv;
    }
    /* noued non present donc on l'ajoute au resau et a la table */
    Noeud* new = insererReseau(R,x,y);
    CellNoeud *nouveau = creerCellNoeud(new);
    nouveau->suiv = H->T[clée];
    H->T[clée] = nouveau;
    H->nbElement++;
    return new;
}

Reseau* reconstitueReseauHachage(Chaines *C, int M){
    // creation de la table de hashage
    printf("step 1\n");
    TableHachage *H = (TableHachage *)malloc(sizeof(TableHachage));
    if (H == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour un nouveau Hashage\n");
        return NULL;
    }

    H->tailleMax = M;
    H->nbElement = 0;
   // Allocation de mémoire pour le tableau de pointeurs
    H->T = malloc(M * sizeof(CellNoeud*));
    if (H->T == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le tableau de pointeurs.\n");
        return NULL;
    }
    // Initialisation des éléments du tableau à NULL
    for (int i = 0; i < M; i++) {
        H->T[i] = NULL;
    }


    /* On reconstitue le reseaux */
    Reseau * R = creerReseau(C->gamma);
    CellChaine* chaine = C->chaines;
    if (! R) printf("Reseaux NULL d");
    /* On parcours la chaine */
    printf("step 2\n");
    int i = 0;
    while(chaine){
        printf("tour %d\n",i);
        i++;
        CellPoint * point = chaine->points;
        printf("step 2a \n");
        //if( ! point) printf("Erreur les points sont NULL\n"); return NULL;
         printf("step 2a bis \n");
        Noeud *extrA = rechercheCreeNoeudHachage(R,H,point->x,point->y);
        printf("step 2a bis  bis\n");
        Noeud* prec=extrA;
        point = point->suiv;
        /* On parcours les points*/
        printf("step 2b \n");
        int z=0;
        while(point->suiv){
            printf(" tour %dB %d",i,z);
            Noeud* new = rechercheCreeNoeudHachage(R,H,point->x,point->y);

            printf(" noeud trouver\n");
            //on assosie les voisins
            insererVoisins( prec, new );
            printf(" inserer voisins\n");
            prec=new;
            
            //On avance
            point=point->suiv;
        }
        printf(" step 2b fini\n");
        /* Creation de la commodite*/
        Noeud *extrB = rechercheCreeNoeudHachage(R,H,point->x,point->y);
        printf("extrB fini\n");
        CellCommodite* commodite = creerCellCommodite(extrA,extrB);
        if( commodite == NULL ) printf(" erreur d'allocation "); return NULL;
        printf(" commodite fini\n");
        commodite->suiv = R->commodites;
        R->commodites = commodite;

        // on assosie extrB avec son voisin
        insererVoisins(prec,extrB);
        printf(" voison extrB fini\n");
        // On passe a la chaine suivant
        chaine=chaine->suiv;  
        printf(" tour suiv\n");
    }
    printf("step 3\n"); printf("Reseaux %p\n",R);
    return R;
}
