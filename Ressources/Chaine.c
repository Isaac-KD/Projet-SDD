#include "Chaine.h"
//#define MAX_LINE_LENGTH 1024



CellPoint * creer_Cellpoint(double x, double y){
    CellPoint * p = malloc(sizeof(CellPoint));
    if( p == NULL ) printf("cannot allocate CellPoint\n");

    p->x = x;   p->y = y; p->suiv = NULL;
    return p;
}

CellChaine * creer_Cellchaine(int numero,CellPoint * points){
    CellChaine * c = malloc(sizeof(CellChaine));
    if( c == NULL ) printf("cannot allocate CellChaine\n");

    c->numero = numero ; c->points = points; c->suiv = NULL;

    return c;
}

Chaines * creer_Chaines(int gamma,int nbChaines, CellChaine * chaine){
    Chaines * ch = malloc(sizeof(Chaines));
    if( ch == NULL ) printf("cannot allocate Chaines\n"); 

    ch ->chaines = chaine; ch ->gamma = gamma; ch ->nbChaines = nbChaines;

    return ch;
}

void ajoute_point_cellpoint(CellPoint **p, double x, double y) {
    CellPoint *new = creer_Cellpoint(x, y);
    CellPoint * tmp = *p;
    if(! tmp ) *p = new;
    else {
        while( tmp->suiv) tmp = tmp->suiv;
        tmp->suiv=new;
    }
}

void ajoute_cellpoint_cellchaine(CellChaine **ch,int numero,CellPoint * p){
    CellChaine *new = creer_Cellchaine(numero,p);
    CellChaine *tmp = *ch;
    if(! tmp ) *ch = new;
    else {
        while( tmp->suiv) tmp = tmp->suiv;
        tmp->suiv=new;
    }
}

void ajoute_cellchaine_cellchaine(CellChaine **src,CellChaine *new){
    CellChaine * ch = *src;
    if( ! ch ) {
        *src = new;
        return;
        }
    while(ch->suiv){ 
        ch=ch->suiv;
        }
    ch->suiv=new;
}


int taille_CellPoint(CellPoint * p){
    int i =0;
    while(p){
        p=p->suiv;
        i++;
    }
    return i;
}

void affiche_CellPoint(CellPoint *p, FILE *f) {
    if (f == NULL) {
        while (p) {
            printf(" %0.2f %0.2f", p->x, p->y);
            p = p->suiv; 
        }
    }
    else {
        while (p) {
            fprintf(f, " %0.2f %0.2f", p->x, p->y);
            p = p->suiv;
        }
    }
}

void affiche_CellChaine(CellChaine *ch,FILE *f) {
    if( f == NULL){
        while(ch){
        fprintf(stdout,"%d",ch->numero);
        fprintf(stdout," %d",taille_CellPoint(ch->points));
        affiche_CellPoint(ch->points,f);
        ch = ch->suiv;
        printf("\n");
        }
    }
    else { 
        while(ch){
        fprintf(f,"%d",ch->numero);
        fprintf(f," %d",taille_CellPoint(ch->points));
        affiche_CellPoint(ch->points,f);
        ch = ch->suiv;
        fprintf(f,"\n");
        }
    }
}

void ecrireChaines(Chaines *C,FILE *f) {
        fprintf(f,"NbChain: %d\nGamma: %d\n",C->nbChaines,C->gamma);
        affiche_CellChaine(C->chaines,f);
}

CellChaine * lire_ligne(char * ligne){
    if( ! ligne ) return NULL;
    double x;
    int numero,taille;
    int i=0;
    sscanf(ligne,"%d %d",&numero,&taille);

    double all_nb[taille*2];
    while(sscanf(ligne,"%lf",&x)==1){
        ligne += strcspn(ligne, " \t");
        ligne += strcspn(ligne, "0123456789.-");
        if(i>1) all_nb[i-2]=x;
        i++;
    }
    
    CellPoint * tmp= creer_Cellpoint(all_nb[0],all_nb[1]);
    for(int j=2; j<2*taille; j+=2) {
        ajoute_point_cellpoint(&tmp,all_nb[j],all_nb[j+1]);
    }
    return creer_Cellchaine(numero,tmp);
}


Chaines* lectureChaines(FILE *f) {
    int gamma;
    int nbChaines;
    char ligne[MAX_LINE_LENGTH];

    rewind(f);

    if (fgets(ligne, sizeof(ligne), f) != NULL) {
        sscanf(ligne, "NbChain: %d", &nbChaines);
        //printf(" NBCHAINNNNNNN %d",nbChaines);
    }
    if (fgets (ligne, sizeof(ligne), f) != NULL) {
        sscanf(ligne, "Gamma: %d", &gamma);
        //printf(" GAMMMAAAA %d",gamma);
    }

    CellChaine *tmp = NULL;
    while(fgets(ligne, MAX_LINE_LENGTH, f) != NULL){
        ajoute_cellchaine_cellchaine(&tmp,lire_ligne(ligne));
    }

    return creer_Chaines(gamma,nbChaines,tmp);
}

double longueurChaine(CellChaine *c) {
    double longueur = 0.0;
    CellPoint *point = c->points;
    while (point != NULL && point->suiv != NULL) {
        double x1 = point->x;
        double y1 = point->y;
        double x2 = point->suiv->x;
        double y2 = point->suiv->y;
        longueur += sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

        point = point->suiv;
    }

    return longueur;
}

double longueurTotale(Chaines *C) {
    double longueurTotale = 0.0;
    for (int i = 0; i < C->nbChaines; i++) {
        longueurTotale += longueurChaine(&(C->chaines[i]));
    }
    return longueurTotale;
}

int comptePointsTotal(Chaines *C) {
    int totalPoints = 0;
    for (int i = 0; i < C->nbChaines; i++) {
        CellChaine *chaine = &(C->chaines[i]);
        CellPoint *point = chaine->points;
        while (point != NULL) {
            totalPoints++;
            point = point->suiv;
        }
    }

    return totalPoints;
}

void changeMinMax(double newx, double newy, double* xmin, double* ymin, double* xmax, double* ymax) {
    if (newx > *xmax) *xmax = newx;
    if (newy > *ymax) *ymax = newy;
    if (newx < *xmin) *xmin = newx;
    if (newy < *ymin) *ymin = newy;
}


void chaineCoordMinMax(Chaines* C, double* xmin, double*ymin, double* xmax, double* ymax){
    CellChaine* pch = C->chaines;
    while(pch){
        CellPoint*pcn = pch->points;
        while(pcn){
            changeMinMax(pcn->x,pcn->y,xmin,ymin,xmax,ymax);
            pcn=pcn->suiv;
        }
        pch=pch->suiv;
    }
    printf("minx = %lf, ymin = %lf, xmax = %lf, ymax = %lf",*xmin,*ymin,*xmax,*ymax);
}