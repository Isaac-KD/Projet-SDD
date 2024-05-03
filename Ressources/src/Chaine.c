#include "../include/Chaine.h"

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

void libereCellPoint(CellPoint *p){
    while(p){
        CellPoint*tmp = p->suiv;
        free(p);
        p=tmp;
    }
    free(p);
}

void libereCellChaine(CellChaine *p){
    while(p){
        CellChaine* tmp = p->suiv;
        libereCellPoint(p->points);
        free(p);
        p=tmp;
    }
    free(p);
}

void libereChaines(Chaines *p){
    libereCellChaine(p->chaines);
    free(p);
}


void ajoute_point_cellpoint(CellPoint **p, double x, double y) {
    CellPoint *new = creer_Cellpoint(x, y);
    CellPoint * tmp = *p;
    if(! tmp ) *p = new;
    else {
        //while( tmp->suiv) tmp = tmp->suiv;  // on aurais pu juste ajouter en tete mais on a prefere ajouter en queu pour que ce soit la meme representation dans la strcture et dans le fichier(dans le meme ordre)
        new->suiv = tmp;
        *p = new;

    }
}

void ajoute_cellpoint_cellchaine(CellChaine **ch,int numero,CellPoint * p){
    CellChaine *new = creer_Cellchaine(numero,p);
    CellChaine *tmp = *ch;
    if(! tmp ) *ch = new;
    else {
        //while( tmp->suiv) tmp = tmp->suiv;  // on aurais pu juste ajouter en tete mais on a prefere ajouter en queu pour que ce soit la meme representation dans la strcture et dans le fichier(dans le meme ordre)
        //tmp->suiv=new;
        new->suiv = tmp;
        *ch = new;
    }
}

void ajoute_cellchaine_cellchaine(CellChaine **src,CellChaine *new){
    CellChaine * ch = *src;
    if( ! ch ) {
        *src = new;
        return;
        }
    else { 
        //while(ch->suiv){  // on aurais pu juste ajouter en tete mais on a prefere ajouter en queu pour que ce soit la meme representation dans la strcture et dans le fichier(dans le meme ordre)
         //   ch=ch->suiv;
       // }
       // ch->suiv=new;
        new->suiv = ch;
        *src = new;
    }
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

CellChaine* lire_ligne(char* ligne) {
    if (!ligne) return NULL;

    int numero, taille, count;
    if (sscanf(ligne, "%d %d%n", &numero, &taille, &count) != 2) return NULL;
    ligne += count; // Avance après la lecture de numero et taille

    CellPoint* head = NULL;
    double x, y;
    for (int i = 0; i < taille; ++i) {
        if (sscanf(ligne, "%lf %lf%n", &x, &y, &count) != 2) {
            // En cas d'erreur de lecture, nettoyer et sortir
            while (head != NULL) {
                CellPoint* tmp = head;
                head = head->suiv;
                free(tmp);
            }
            return NULL;
        }
        ajoute_point_cellpoint(&head, x, y);
        ligne += count; // Avance après la lecture de chaque point
    }

    return creer_Cellchaine(numero, head);
}

Chaines* lectureChaines(FILE *f) {
    int gamma;
    int nbChaines;
    char ligne[MAX_LINE_LENGTH];
    rewind(f);// on ce place au debut du fichier
    if (ferror(f)) {
    fprintf(stderr, "Erreur lors de la réinitialisation du fichier\n");
    fclose(f);
    return NULL;
}

    if (fgets(ligne, sizeof(ligne), f) != NULL) {
        sscanf(ligne, "NbChain: %d", &nbChaines);
    }
    if (fgets (ligne, sizeof(ligne), f) != NULL) {
        sscanf(ligne, "Gamma: %d", &gamma);
    }
    CellChaine *tmp = NULL;
    while(fgets(ligne, MAX_LINE_LENGTH, f) != NULL){
        ajoute_cellchaine_cellchaine(&tmp,lire_ligne(ligne));
    }
    return creer_Chaines(gamma,nbChaines,tmp);
}

void afficheChaineSVG(Chaines *C, char* nomInstance){
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
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
}

Chaines *generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax) {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires

    CellChaine *chaines = NULL;
    for (int i = 0; i < nbChaines; i++) {
        CellPoint *points = NULL;
        for (int j = 0; j < nbPointsChaine; j++) {
            double x = (rand() / (double)RAND_MAX) * xmax;
            double y = (rand() / (double)RAND_MAX) * ymax;
            ajoute_point_cellpoint(&points, x, y);  // Ajout du point à la liste des points
        }
        CellChaine *nouvelleChaine = creer_Cellchaine(i + 1, points);  // Crée une nouvelle chaîne avec les points générés
        ajoute_cellchaine_cellchaine(&chaines, nouvelleChaine);  // Ajoute la nouvelle chaîne à la liste des chaînes
    }

    int gamma = 1+(int)(rand()%20);  // Valeur du gamma non preciser , genartion d'un valeur entre 1 et 20
    return creer_Chaines(gamma, nbChaines, chaines);
}