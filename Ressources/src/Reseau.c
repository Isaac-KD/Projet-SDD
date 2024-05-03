#include "../include/Reseau.h"
#import <math.h>

Reseau * creerReseau(int gamma){
    Reseau * new = (Reseau *) malloc(sizeof(Reseau));
    if (new == NULL) {
        fprintf(stderr, "Erreur d'allocation memoire pour le reseau\n");
    }
    new->nbNoeuds = 0;
    new->gamma = gamma;
    new->noeuds = NULL ;
    new->commodites = NULL;
    return new;
}

Noeud* creerNoeud(int num, double x, double y) {
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    if (!nouveau) {
        fprintf(stderr, "Erreur d'allocation mémoire pour un nouveau noeud\n");
        return NULL;
    }
    nouveau->num = num;
    nouveau->x = x;
    nouveau->y = y;
    nouveau->voisins = NULL;
    return nouveau;
}

CellNoeud * creerCellNoeud( Noeud * n){
    CellNoeud *nouveau = malloc(sizeof(CellNoeud));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour un nouveau CellNoeud\n");
        return NULL;
    }
    nouveau->nd = n;
    nouveau->suiv = NULL;
    return nouveau;
}
CellCommodite * creerCellCommodite(Noeud *  extrA,Noeud * extrB){
    CellCommodite * commodites = (CellCommodite *) malloc(sizeof(CellCommodite));
    if( ! commodites){
        printf(" Erreur allocation commodites \n");return NULL;
    }
    commodites->extrB = extrB;
    commodites->extrA = extrA;
    commodites->suiv = NULL;
    return commodites;
}

/* Fonction pour libérer une liste de CellNoeud */
void liberer_liste_CellNoeud(CellNoeud *liste) {
    CellNoeud *tmp;
    while (liste != NULL) {
        tmp = liste;
        liste = liste->suiv;
        free(tmp);
    }
}

/* Fonction pour libérer un noeud et sa liste de voisins */
void liberer_noeud(Noeud *noeud) {
    if (noeud != NULL) {
        liberer_liste_CellNoeud(noeud->voisins);
        free(noeud);
    }
}

/* Fonction pour libérer une liste de CellCommodite */
void liberer_liste_CellCommodite(CellCommodite *liste) {
    CellCommodite *tmp;
    while (liste != NULL) {
        tmp = liste;
        liste = liste->suiv;
        free(tmp);
    }
}

/* Fonction pour libérer tous les noeuds dans la liste de noeuds du réseau */
void liberer_tous_les_noeuds(CellNoeud *liste) {
    CellNoeud *current;
    while (liste != NULL) {
        current = liste;
        liste = liste->suiv;
        liberer_noeud(current->nd);
        free(current);
    }
}

/* Fonction pour libérer le réseau */
void liberer_reseau(Reseau *reseau) {
    if (reseau != NULL) {
        liberer_tous_les_noeuds(reseau->noeuds);
        liberer_liste_CellCommodite(reseau->commodites);
        free(reseau);
    }
}

void insererVoisins(Noeud *noeud1, Noeud *noeud2) {
    if (!noeud1 || !noeud2)
        return; // Si l'un des noeuds est NULL, sortie de la fonction

    // Vérification si les noeuds sont déjà voisins
    CellNoeud *tmp1 = noeud1->voisins;
    while (tmp1) {
        if (tmp1->nd->num == noeud2->num)
            return; // Les noeuds sont déjà voisins, sortie de la fonction
        tmp1 = tmp1->suiv;
    }

    // Allocation de mémoire pour les nouveaux voisins
    CellNoeud *new1 = (CellNoeud *)malloc(sizeof(CellNoeud));
    CellNoeud *new2 = (CellNoeud *)malloc(sizeof(CellNoeud));

    if (!new1 || !new2) {
        // Affichage de l'erreur d'allocation
        printf("Erreur allocation CellNoeud \n");

        // Libération de la mémoire allouée jusqu'à présent
        if (new1) free(new1);
        if (new2) free(new2);

        return; // Sortie de la fonction en cas d'échec d'allocation
    }

    // Initialisation des nouveaux voisins
    new1->nd = noeud2;
    new2->nd = noeud1;

    // Ajout des nouveaux voisins à la liste des voisins des deux nœuds
    new1->suiv = noeud1->voisins;
    new2->suiv = noeud2->voisins;
    noeud1->voisins = new1;
    noeud2->voisins = new2;
}

Noeud * insererReseau(Reseau * R, double x, double y){
    Noeud * new = (Noeud *) malloc(sizeof(Noeud));
     if (new == NULL) fprintf(stderr, "Erreur d'allocation memoire pour inserer un noeud dans le reseau\n");
    R->nbNoeuds++; // on ajoute +1 au nb de noeuds

    new->num = R->nbNoeuds; 
    new->x =x; // on creer un noeud
    new->y =y;
    new->voisins = NULL;

    /* On ajoute le noeud a reseaux */
    CellNoeud * new_cell_noeud = (CellNoeud *) malloc(sizeof(CellNoeud));
    new_cell_noeud->nd = new;
    new_cell_noeud->suiv = R->noeuds ;
    R->noeuds = new_cell_noeud; 

    return new;
}

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    if(! R) {
        printf("Erreur rechercheCreeNoeudListe R est NULL\n");
        return NULL;}
    CellNoeud *noeud = R->noeuds;
    while(noeud != NULL){
        /*calcule la distance euclidienne entre les 2 points ,car la comparaison n'est pas precise car c'est des double*/
        if(sqrt((noeud->nd->x-x)*(noeud->nd->x-x) +  (noeud->nd->y-y)*(noeud->nd->y-y))<=pow(10,-4)) 
        {
            return noeud->nd;
        }
        noeud = noeud->suiv;
    }
    Noeud* noeud2 = (Noeud*)malloc(sizeof(Noeud));
    if(noeud2 == NULL){
        fprintf(stderr, "Erreur d'allocation mémoire du noeud");
        exit(EXIT_FAILURE);
    }
    noeud2->num = R->nbNoeuds;
    R->nbNoeuds++;

    noeud2->x = x;
    noeud2->y = y;
    noeud2->voisins = NULL;

    CellNoeud* cellnoeud = (CellNoeud*)malloc(sizeof(CellNoeud));
    if(cellnoeud == NULL){
        fprintf(stderr, "Erreur d'allocation mémoire de cellnoeud");
        exit(EXIT_FAILURE);
    }
    cellnoeud->nd = noeud2;
    cellnoeud->suiv = R->noeuds;
    R->noeuds = cellnoeud;

    return noeud2;
}


Reseau* reconstitueReseauListe(Chaines *C) {
    // Création d'un nouveau réseau
    Reseau *R = (Reseau*)malloc(sizeof(Reseau));
    if (R == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le réseau\n");
        exit(EXIT_FAILURE);
    }
    R->noeuds = NULL;
    R->commodites = NULL;
    R->gamma = C->gamma;
    R->nbNoeuds = 0; // Initialiser le nombre de nœuds à zéro

    /* Parcours de la Chaine*/
    CellChaine * chaines = C->chaines; 
    while(chaines){
        // On prend le noeud extrA de la commodite 
        CellPoint * point = chaines->points;
        Noeud * extrA = rechercheCreeNoeudListe(R,point->x,point->y);
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
            Noeud * tmp =rechercheCreeNoeudListe(R,point->x,point->y);
            insererVoisins(prec,tmp);
            prec = tmp;
            point = point->suiv;
        }
        Noeud * extrB = rechercheCreeNoeudListe(R,point->x,point->y);
        insererVoisins(extrB,prec);
        /* Gestion des commodites */
        CellCommodite * commodites = creerCellCommodite(extrA,extrB);
        commodites->suiv = R->commodites;
        R->commodites = commodites;

        chaines = chaines->suiv;
    }
    return R;
}

int nbCommodites(Reseau *R) {
    // simple parcours de listes
    int nbCommodites = 0;
    CellCommodite *commodite = R->commodites;
    while (commodite != NULL) {
        nbCommodites++;
        commodite = commodite->suiv;
    }
    return nbCommodites;
}

int nbLiaisons(Reseau *R)
{
    if (R == NULL) // teste si le reseau donne en argument existe
    {
        fprintf(stderr, "Erreur (fontion nbLiaisons): reseau donne en argument n'existe pas\n");
        return -1;
    }
    // sinon on parcourt la liste des cellules de noeuds
    int nombreDeLiaisons = 0; // nombre total de liaisons dans le reseau R
    CellNoeud *celluleDeNoeudCourante = R->noeuds; // stocke un pointeur vers la cellule de noeud courante dans la liste chaines 
    Noeud *noeudCourant = NULL; // un pointeur vers le noeud courant
    //allocation d'un tableau de booleen pour verifier si le noeud a ete deja vu
    char *tableauDejaVus = (char *)calloc(R->nbNoeuds, sizeof(char));
    char *tableauVoisinsDejaVus = NULL;
    if (tableauDejaVus == NULL)
    {
        fprintf(stderr, "Erreur (fonction ecrireReseau) : allocation tableau de noeuds deja vus\n");
        return -1;
    }
    //
    while (celluleDeNoeudCourante != NULL) // boucle de parcours des cellules de noeuds
    {
        noeudCourant = celluleDeNoeudCourante->nd; // recuperation du noeud courant pointe par la cellule de noeud courante
        if (noeudCourant == NULL) // teste si la cellule courante contient bien un noeud
        {
            fprintf(stderr, "Erreur (fonction nbLiaisons): il existe une cellule de noeud dans le reseau qui ne pointe vers aucuns noeuds\n");
            return -1;
        }
        tableauVoisinsDejaVus = (char *)calloc(R->nbNoeuds, sizeof(char));
        if (tableauVoisinsDejaVus == NULL)
        {
            fprintf(stderr, "Erreur (fonction ecrireReseau) : allocation tableau de voisins deja vus\n");
            free(tableauDejaVus);
            return -1;
        }
        tableauDejaVus[noeudCourant->num-1] = 1; // ce noeud est deja vu
        // si oui on parcourt la liste chainee des voisins du noeud courant
        CellNoeud *celluleDeNoeudVoisin = noeudCourant->voisins; // liste chainee des cellules de noeud des voisins du noeud courant
        Noeud *noeudVoisinDuNoeudCourant = NULL; // noeud voisin du noeud courant
        while (celluleDeNoeudVoisin != NULL) // boucle de parcourt de la liste des voisins (cellules)
        {
            noeudVoisinDuNoeudCourant = celluleDeNoeudVoisin->nd; // noeud voisin pointe par la cellule dans la liste des voisins
            if (noeudVoisinDuNoeudCourant == NULL) // teste si la cellules contient bien un noeud
            {
                fprintf(stderr, "Erreur (fonction nbLiaisons): il existe une cellule de noeud (type Voisins) dans le reseau qui ne pointe vers aucuns noeuds\n");
                return -1;
            }
            // pour chaque noeud, on verifie que ce noeud n'a pas ete deja vue dans la liste des noeuds du reseau parcourue
            if (tableauDejaVus[noeudVoisinDuNoeudCourant->num - 1] == 0 && tableauVoisinsDejaVus[noeudVoisinDuNoeudCourant->num - 1] == 0) // teste si le voisin courant a deja ete trait'e et vu
            {
                // si jamais vue alors on inscrit la liaison (noeud courant <-> voisin courant)
                nombreDeLiaisons ++;
                tableauVoisinsDejaVus[noeudVoisinDuNoeudCourant->num - 1] = 1;
            }
            celluleDeNoeudVoisin = celluleDeNoeudVoisin->suiv; // on avance dans la liste des cellules voisines de la cellule courante(noeud courant)
        }
        free(tableauVoisinsDejaVus);
        celluleDeNoeudCourante = celluleDeNoeudCourante->suiv; // on passe a  la cellule de noeud suivante
    }
    free(tableauDejaVus);
    return nombreDeLiaisons;
}


void ecrireReseau(Reseau *R, FILE *f)
{
    if (R == NULL) // teste si le reseau donne en argument existe reelement
    {
        fprintf(stderr, "Erreur (fonction ecrireReseau): le reseau donne en argument n'existe pas\n");
        return;
    }
    if (f == NULL) // teste si le flux en ecriture est correctement donne en argument
    {
        fprintf(stderr, "Erreur (fonction ecrireReseau): le flux en ecriture donne en argument n'existe pas\n");
        return;
    }
    // on inscrit dans le fichier le nombre de noeuds dans le reseau (Champs nbNoeuds de la structure Reseau)
    fprintf(f, "NbNoeuds: %d\n", R->nbNoeuds);
    //
    // on inscrit dans le fichier le nombre de liaisons dans le reseau en appelant la fonction nbLiaisons sur le reseau R
    fprintf(f, "NbLiaisons: %d\n", nbLiaisons(R));
    //
    // on inscrit dans le fichier le nombre de commodites dans le reseau en appelant la fonction nbCommodites sur le reseau R
    fprintf(f, "NbCommodites: %d\n", nbCommodites(R));
    //
    // on inscrit gamma le nombre maximum de fibre par liaison (champ gamma de Reseau)
    fprintf(f, "Gamma: %d\n\n", R->gamma);
    //

    //on inscrit la liste des noeud contenue dans le reseau
    CellNoeud *celluleDeNoeudCourante = R->noeuds; // pointeur vers la cellule de noeud courante
    Noeud *noeudCourant = NULL; // noeud contenu dans la cellule courante
    while (celluleDeNoeudCourante != NULL) // boucle de parcourt de la liste chainee des cellules de noeud du reseau R
    {
        noeudCourant = celluleDeNoeudCourante->nd; // recuperation du noeud contenu dans la cellule de noeud courante
        if (noeudCourant == NULL) // teste si la cellule de noeud courante contient bien une noeud
        {
            fprintf(stderr, "Erreur (fonction ecrireReseau): il existe une cellule de noeud qui ne contient aucun noeuds\n");
            return;
        }
        // si oui on inscrit son numero, ses coordonnes
        fprintf(f, "v %d %.6f %.6f\n", noeudCourant->num, noeudCourant->x, noeudCourant->y);
        //
        celluleDeNoeudCourante = celluleDeNoeudCourante->suiv; // on passe a la cellule suivante
    }

    fprintf(f, "\n"); // on saute une ligne pour separer les noeuds des liaisons

    //allocation d'un tableau de booleen pour verifier si le noeud a ete deja vu
    char *tableauDejaVus = (char *)calloc(R->nbNoeuds, sizeof(char));
    char *tableauVoisinsDejaVus = NULL;
    if (tableauDejaVus == NULL)
    {
        fprintf(stderr, "Erreur (fonction ecrireReseau) : allocation tableau de noeuds deja vus\n");
        return;
    }
    //
    // on inscrit la liste des liaisons en parcourant les voisins de chaque noeud du reseau
    celluleDeNoeudCourante = R->noeuds; // pointeur vers la cellule de noeud courante
    noeudCourant = NULL; // noeud contenu dans la cellule courante
    while (celluleDeNoeudCourante != NULL) // boucle de parcourt de la liste chainee des cellules de noeud du reseau R
    {
        noeudCourant = celluleDeNoeudCourante->nd; // recuperation du noeud contenu dans la cellule de noeud courante
        if (noeudCourant == NULL) // teste si la cellule de noeud courante contient bien une noeud
        {
            fprintf(stderr, "Erreur (fonction ecrireReseau): il existe une cellule de noeud qui ne contient aucun noeuds\n");
            return;
        }
        tableauVoisinsDejaVus = (char *)calloc(R->nbNoeuds, sizeof(char));
        if (tableauVoisinsDejaVus == NULL)
        {
            fprintf(stderr, "Erreur (fonction ecrireReseau) : allocation tableau de voisins deja vus\n");
            free(tableauDejaVus);
            return;
        }
        tableauDejaVus[noeudCourant->num-1] = 1; // ce noeud est deja vu
        // si oui on parcourt la liste chainee des voisins du noeud courant
        CellNoeud *celluleNoeudVoisinCourant = noeudCourant->voisins; // pointeur vers la cellule contenant le voisin courant
        Noeud *voisinCourant = NULL; // noeud representant le voisin du noeud courant
        while (celluleNoeudVoisinCourant != NULL) // boucle de parcourt de la liste chainee des voisins du noeud courant
        {
            voisinCourant = celluleNoeudVoisinCourant->nd; // recuperation du voisin du noeud courant
            if (voisinCourant == NULL) // teste si la cellule courante (cellule contenant un voisin) contient bien un noeud
            {
                fprintf(stderr, "Erreur (fonction ecrireReseau): il existe une cellule de noeud (type Voisin) qui ne contient aucun noeuds\n");
                return;
            }
            if (tableauDejaVus[voisinCourant->num-1] == 0 && tableauVoisinsDejaVus[voisinCourant->num - 1] == 0) // teste si le voisin courant a deja ete trait'e et vu
            {
                // si jamais vue alors on inscrit la liaison (noeud courant <-> voisin courant)
                fprintf(f, "l %d %d\n", voisinCourant->num, noeudCourant->num);
                tableauVoisinsDejaVus[voisinCourant->num - 1] = 1;
            }
            celluleNoeudVoisinCourant = celluleNoeudVoisinCourant->suiv; // on passe au voisin suivant du noeud courant
        }
        free(tableauVoisinsDejaVus);
        celluleDeNoeudCourante = celluleDeNoeudCourante->suiv; // on passe a la cellule de noeud suivant dans le reseau R
    }
    free(tableauDejaVus);
    fprintf(f, "\n"); // on saute de ligne pour marquer une separation entre le liaisons et les commodites 

    // on inscrit la liste des commodites en parcourant les commodites du reseau R
    CellCommodite *commoditeCourante = R->commodites; // pointeur vers la commodite courante
    while (commoditeCourante != NULL) // boucle de parcourt de la liste des commodites
    {
        Noeud *extrA = NULL, *extrB = NULL; // on definit les noeud extremites de chaque commodite
        // recuperation des noeud extremes A et B de la commodite courante
        extrA = commoditeCourante->extrA;
        extrB = commoditeCourante->extrB;
        //
        if (extrA == NULL || extrB == NULL) // teste si l'une des extremites de la commodite existe (pointe par la commodite courante)
        {
            fprintf(stderr, "Erreur (fonction ecrireReseau): il existe une commodite dont une extremite ne pointe vers aucun noeud du reseau\n");
            return;
        }
        // si les deux extremites existent (sans tester si c'est les memes dans le cas d'une commidite de longueur 1)
        // on inscrit les numeros des deux extremites
        fprintf(f, "k %d %d\n", extrA->num, extrB->num);
        //
        commoditeCourante = commoditeCourante->suiv; // on passe a la commidite suivante dans la liste chainee
    }
}

void afficheReseauSVG(Reseau *R, char* nomInstance) {
    if (R == NULL || nomInstance == NULL) {
        fprintf(stderr, "Erreur : Réseau ou nom d'instance non valide\n");
        return;
    }

    // Création du fichier SVG
    FILE *svgFile = fopen(nomInstance, "w");
    if (svgFile == NULL) {
        fprintf(stderr, "Erreur : Impossible de créer le fichier SVG\n");
        return;
    }

    // Écriture de l'en-tête du fichier SVG
    fprintf(svgFile, "<html><body><svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\"");
    fprintf(svgFile, " width=\"100%%\" height=\"100%%\"");
    fprintf(svgFile, " viewBox=\"%d %d %d %d\"", -2, -2, 500, 500);
    fprintf(svgFile, " preserveAspectRatio=\"yes\">\n");
    fprintf(svgFile, "<g >\n\n");

    // Dessiner les liaisons entre les nœuds
    CellNoeud *noeud = R->noeuds;
    while (noeud != NULL) {
        CellNoeud *voisin = noeud->nd->voisins;
        while (voisin != NULL) {
            // Dessiner la liaison entre le nœud courant et son voisin
            fprintf(svgFile, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:black;stroke-width:2\"/>\n",
                    noeud->nd->x, noeud->nd->y, voisin->nd->x, voisin->nd->y);
            voisin = voisin->suiv;
        }
        noeud = noeud->suiv;
    }

    // Dessiner les nœuds du réseau
    noeud = R->noeuds;
    while (noeud != NULL) {
        fprintf(svgFile, "<circle cx=\"%lf\" cy=\"%lf\" r=\"2\" stroke=\"black\" stroke-width=\"1\" fill=\"green\" />\n",
                noeud->nd->x, noeud->nd->y);
        noeud = noeud->suiv;
    }

    // Écriture de la fin du fichier SVG
    fprintf(svgFile, "\n\n</g></svg></body></html>\n");

    // Fermeture du fichier SVG
    fclose(svgFile);
}

