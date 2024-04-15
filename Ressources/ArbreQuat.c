#include "ArbreQuat.h"

ArbreQuat* creerArbreQuat(double xc, double yc, double coteX,double coteY){
    printf(" xc: %lf, yc: %lf, coteX: %lf, coteY: %lf\n",xc,yc,coteX,coteY);
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

void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat*parent){
    double xc = parent->xc; double yc = parent->yc; // position x,y parent
    double coteX = parent->coteX; double coteY = parent->coteY; // taille du coter du parent 

    double nx = n->x; double ny = n->y; // position du nouveau noeud a inserer


    if( ! *a){
        // cas ou c'est vide 
        double newcoterX = coteX/2; double newcoterY = coteY/2; // taille d'un sous rectangle
        double quatX = (newcoterX/2); double quatY = (newcoterY/2);// longueur a soustraire oun a additiona chaque point

        if(nx < xc&& ny < yc){ // cas so
            *a = creerArbreQuat(xc-quatX,yc-quatY,newcoterX,newcoterY);
            (*a)->noeud = n;
        }
        else if (nx >= xc&& ny < yc){ // cas se
            *a =creerArbreQuat(xc+quatX,yc-quatY,newcoterX,newcoterY);
            (*a)->noeud = n;
        }
        else if (nx < xc&& ny >= yc){ //cas no
            *a =creerArbreQuat(xc-quatX,yc+quatY,newcoterX,newcoterY);
            (*a)->noeud = n;
        }   
        else if (nx >= xc&& ny >= yc){ // cas ne
            *a =creerArbreQuat(xc+quatX,yc+quatY,newcoterX,newcoterY);
            (*a)->noeud = n;
        }
        return;
    }
    if ((*a)->noeud != NULL){
        // cas ou il faut creer des sous arbres
        Noeud * noeudInitial = (*a)->noeud;
        if( (noeudInitial->x == n->x) && (noeudInitial->y == n->y)) return; // si on inserer deux noeud a la meme position on risque d'avoir des appelles infinie
        (*a)->noeud = NULL;

        double Ix = noeudInitial->x;double Iy = noeudInitial->y; // position du noeud initial

        /* On reinsere le noeud deja present en fonction de la posititon */
        if(Ix < xc && Iy < yc){
            insererNoeudArbre(noeudInitial,&((*a)->so),(*a));    //cas so, on insere le noeud deja present 
        }
        else if (Ix >= xc && Iy < yc){
            insererNoeudArbre(noeudInitial,&((*a)->se),(*a));    //cas se, on insere le noeud deja present 
        }
        else if (Ix < xc && Iy >= yc){
            insererNoeudArbre(noeudInitial,&((*a)->no),(*a));    // cas no, on insere le noeud deja present 
        }   
        else if (Ix >= xc && Iy >= yc){
            insererNoeudArbre(noeudInitial,&((*a)->ne),(*a));    //cas ne, on insere le noeud deja present 
        }

        /* On insere le nouveau en fonction de la posititon */
        if(nx < xc && ny < yc){
            insererNoeudArbre(n,&((*a)->so),(*a));    //cas so, on insere le nouveau noeud
        }
        else if (nx >= xc && ny < yc){
            insererNoeudArbre(n,&((*a)->se),(*a));    //cas se, on insere le nouveau noeud
        }
        else if (nx < xc && ny >= yc){
            insererNoeudArbre(n,&((*a)->no),(*a));    // cas no, on insere le nouveau noeud
        }   
        else if (nx >= xc && ny >= yc){
            insererNoeudArbre(n,&((*a)->ne),(*a));    //cas ne, on insere le nouveau noeud
        }
        return;
    }
    if(( *a != NULL) && ((*a)->noeud == NULL)){
        /*cas ou on doit parcourir l'arbre*/
        if(nx < xc && ny < yc){
            insererNoeudArbre(n,(&(*a)->so),(*a));    //cas on parrcours le sous arbre so
        }
        else if (nx >= xc && ny < yc){
            insererNoeudArbre(n,(&(*a)->se),(*a));    //cas on parrcours le sous arbre se
        }
        else if (nx < xc && ny >= yc){
            insererNoeudArbre(n,(&(*a)->no),(*a));    // cas on parrcours le sous arbre no
        }   
        else if (nx >= xc && ny >= yc){
            insererNoeudArbre(n,(&(*a)->ne),(*a));    //cas on parrcours le sous arbre ne
        }
        return;
    }
}

Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat*parent, double x, double y){
    /* cas ou l'arbre ets vide */
    if( ! *a){
        Noeud* n = rechercheCreeNoeudListe(R,x,y); // On creer ou insere un noeud dans le Reseau
        insererNoeudArbre(n,a,parent); // on insere le noeud dans l'arbre
        return n;
    }

    /* cas ou on est sur une feuille */
    if ((*a)->noeud != NULL){
        Noeud * noeudInitial =(*a)->noeud; // le noeud actuel
         if( (noeudInitial->x == x) && (noeudInitial->y == y)) return noeudInitial;// retourne le noeud deja existant
         else{
            Noeud* n = rechercheCreeNoeudListe(R,x,y); // On creer ou insere un noeud dans le Reseau
            insererNoeudArbre(n,a,parent); // on insere le noeud dans l'arbre
            return n;
         }
    }   

    /* cas d'une cellule interne*/
    if((*a != NULL)&& ((*a)->noeud == NULL)){
        double xc = parent->xc; double yc = parent->yc; // position x,y parent

        if(x < xc && y < yc){
            return rechercheCreeNoeudArbre(R,&((*a)->so),(*a),x,y);    //cas on parrcours le sous arbre so
        }
        else if (x >= xc && y < yc){
            return rechercheCreeNoeudArbre(R,&((*a)->se),(*a),x,y);    //cas on parrcours le sous arbre se
        }
        else if (x < xc && y >= yc){
            return rechercheCreeNoeudArbre(R,&((*a)->no),(*a),x,y);     // cas on parrcours le sous arbre no
        }   
        else if (x >= xc && y >= yc){
            return rechercheCreeNoeudArbre(R,&((*a)->ne),(*a),x,y);     //cas on parrcours le sous arbre ne
        }
    }
    return NULL;    // ce cas ne devrait jamais arriver 
}

Reseau* reconstitueReseauArbre(Chaines* C){
    double xmin,xmax,ymin,ymax;
    chaineCoordMinMax(C,&xmin,&ymin,&xmax,&ymax); // recuprer le min et le max d'une chaine
    double coteX = (xmax-xmin); // dimension du cote X
    double coteY = (ymax-ymax); // dimension du cote Y
    /* Creaion des instances*/
    ArbreQuat * a = creerArbreQuat(coteX/2,coteY/2,coteX,coteY);
    Reseau* R = creerReseau(C->nbChaines,C->gamma); // |||||||| il faut creer la fonction ||||||||

    /* Parcours de la Chaine*/
    CellChaine * lchaines = C->chaines; 
    while( lchaines){
        CellPoint * lpoints = lchaines->points;
        while( lpoints){

            rechercheCreeNoeudArbre(R,&a,a,lpoints->x,lpoints->y);// reconstitution du reseau
            lpoints = lpoints->suiv;
        }
        lchaines = lchaines->suiv;
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