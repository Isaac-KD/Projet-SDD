#include "ArbreQuat.h"
#import <math.h>
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX,double coteY){
    //printf(" xc: %lf, yc: %lf, coteX: %lf, coteY: %lf\n",xc,yc,coteX,coteY);
    ArbreQuat* new  = (ArbreQuat*) malloc(sizeof(ArbreQuat));

    if( new == NULL ){
        printf("cannot allocate CellPoint\n"); exit(EXIT_FAILURE);
    }

    new->xc = xc; new->yc = yc;
    new->coteX = coteX; new->coteY = coteY;
    new->noeud= NULL;
    new->se = NULL; new->so = NULL;
    new->no = NULL; new->ne = NULL;
    return new;
}

void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent) {
    /* Cas arbre vide */
    if (*a == NULL) {
        // Créer un nouvel arbre si l'arbre actuel est vide
        double moitieCoteX = parent->coteX / 2;
        double moitieCoteY = parent->coteY / 2;
        double nouveauXc = parent->xc + (n->x < parent->xc ? -moitieCoteX / 2 : moitieCoteX / 2);
        double nouveauYc = parent->yc + (n->y < parent->yc ? -moitieCoteY / 2 : moitieCoteY / 2);
        *a = creerArbreQuat(nouveauXc, nouveauYc, moitieCoteX, moitieCoteY);
        (*a)->noeud = n;
        return;
    }
    /* Cas feuilles */
    if ((*a)->noeud != NULL) {
        // Cas d'une feuille : transformer en noe dud interne et réinsérer les noeuds
        Noeud* actuel = (*a)->noeud;
        if (sqrt(actuel->x* n->x + actuel->y *n->y) <= pow(10,-4)) return; // éviter les doublons

        (*a)->noeud = NULL;
        insererNoeudArbre(actuel, a, parent);
        insererNoeudArbre(n, a, parent);
        return;
    }

    /* Cas  noeud interne */
    if (n->x < (*a)->xc) {
        if (n->y < (*a)->yc)
            insererNoeudArbre(n, &((*a)->so), *a);
        else
            insererNoeudArbre(n, &((*a)->no), *a);
    } else {
        if (n->y < (*a)->yc)
            insererNoeudArbre(n, &((*a)->se), *a);
        else
            insererNoeudArbre(n, &((*a)->ne), *a);
    }
}

Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y) {
     /* Cas arbre vide */
    if (*a == NULL) {
        Noeud* n = insererReseau(R, x, y);
        insererNoeudArbre(n, a, parent);
        return n;
    }
    /* Cas feuilles */
    if ((*a)->noeud != NULL) {
        if (sqrt(((*a)->noeud->x - x )*((*a)->noeud->x - x )+ ((*a)->noeud->y -y)*((*a)->noeud->y -y))<= pow(10,-4)) return (*a)->noeud;
        Noeud* new = insererReseau(R, x, y);
        insererNoeudArbre(new, a, parent);
        return new;
    }
    // Pas besoin de vérifier `*a != NULL` ici car couvert par les cas précédents
     if (x < (*a)->xc && y < (*a)->yc) // so
    {
        return rechercheCreeNoeudArbre(R, &((*a)->so), *a, x, y);
    }
    else if (x >= (*a)->xc && y < (*a)->yc) // se
    {
        return rechercheCreeNoeudArbre(R, &((*a)->se), *a, x, y);
    }
    else if (x < (*a)->xc && y >= (*a)->yc) // no
    {
        return rechercheCreeNoeudArbre(R, &((*a)->no), *a, x, y);
    }
    else // ne
    {
        return rechercheCreeNoeudArbre(R, &((*a)->ne), *a, x, y);
    }
    printf("Erreur dans rechercherCreeNoeudArbre \n");
    return NULL;
}

 


Reseau* reconstitueReseauArbre(Chaines* C){
    double xmin = INFINITY;  // Utilisez INFINITY défini dans <math.h>
    double ymin = INFINITY;
    double xmax = -INFINITY;
    double ymax = -INFINITY;    
    chaineCoordMinMax(C,&xmin,&ymin,&xmax,&ymax); // recuprer le min et le max d'une chaine
    double coteX = (xmax-xmin); // dimension du cote X
    double coteY = (ymax-ymin); // dimension du cote Y
    /* Creaion des instances*/
    ArbreQuat * a = creerArbreQuat(coteX/2,coteY/2,coteX,coteY);
    Reseau* R = creerReseau(C->gamma);

    /* Parcours de la Chaine*/
    CellChaine * chaines = C->chaines; 
    while(chaines){
        // On prend le noeud extrA de la commodite 
        CellPoint * point = chaines->points;
        Noeud * extrA = rechercheCreeNoeudArbre(R,&a,a,point->x,point->y);
        /* Si il n'y a que 1 point dans la chaine*/
        if( ! point->suiv){
            Noeud * extrB = extrA;
            CellCommodite * commodites = creerCellCommodite(extrA,extrB);
            commodites->suiv = R->commodites;
            R->commodites = commodites;
            continue;
        }
        Noeud * prec = extrA; // instance utliser pour assosier des voisins
        point = point->suiv;
        /*On parcours la liste des noeuds.
        On s'arrete un noeud avant la fin pour pouvoir obtenir l'extrB */
        while(point->suiv){
            Noeud * tmp = rechercheCreeNoeudArbre(R,&a,a,point->x,point->y);
            insererVoisins(prec,tmp);
            prec = tmp;
            point = point->suiv;
        }
        Noeud * extrB = rechercheCreeNoeudArbre(R,&a,a,point->x,point->y);
        insererVoisins(extrB,prec);
        /* Gestion des commodites */
        CellCommodite * commodites = creerCellCommodite(extrA,extrB);
        commodites->suiv = R->commodites;
        R->commodites = commodites;

        chaines = chaines->suiv;
    }
    return R;
}

void afficherArbre(ArbreQuat* arbre, int level) {
    if (arbre == NULL) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("Arbre: Centre=(%.2f, %.2f), Taille=(%.2f, %.2f)\n", arbre->xc, arbre->yc, arbre->coteX, arbre->coteY);
    if (arbre->noeud != NULL) {
        for (int i = 0; i < level; i++) printf("  ");
        printf("Noeud: Position=(%.2f, %.2f)\n", arbre->noeud->x, arbre->noeud->y);
    }
    afficherArbre(arbre->se, level + 1);
    afficherArbre(arbre->so, level + 1);
    afficherArbre(arbre->ne, level + 1);
    afficherArbre(arbre->no, level + 1);
}