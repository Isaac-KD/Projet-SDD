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

void affiche_graphe(Graphe *g, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    fprintf(f, "graph G {\n");
    for (int i = 1; i <= g->nbsom; i++) {
        Sommet *som = g->T_som[i];
        fprintf(f, "  %d [label=\"(%d, %.2f, %.2f)\"];\n", som->num, som->num, som->x, som->y);

        Cellule_arete *current = som->L_voisin;
        while (current != NULL) {
            Arete *a = current->a;
            if (a->u == som->num) {  // Vérifie si le sommet courant est l'extrémité 'u' de l'arête
                fprintf(f, "  %d -- %d;\n", a->u, a->v);
            }
            current = current->suiv;
        }
    }
    fprintf(f, "}\n");
    fclose(f);
}
void insererAreteVoisin(Sommet *s, Sommet *actuel) {
    if (s == NULL || actuel == NULL) {
        return;
    }

    // Vérifie si l'arête existe déjà entre s et actuel
    Cellule_arete *cur = s->L_voisin;
    while (cur != NULL) {
        Arete *a = cur->a;
        // Vérifier si l'arête entre s et actuel existe déjà
        if ((a->u == s->num && a->v == actuel->num) || (a->u == actuel->num && a->v == s->num)) {
            return;  // L'arête existe déjà, donc on ne l'ajoute pas
        }
        cur = cur->suiv;
    }

    // Si non trouvée, créer la nouvelle arête
    Arete *a = creeArete(s->num, actuel->num);
    Cellule_arete *newS = creeCellule_arete(a);
    Cellule_arete *newA = creeCellule_arete(a);

    // Associer chaque nouvelle cellule à son sommet
    newS->suiv = s->L_voisin;
    newA->suiv = actuel->L_voisin;
    actuel->L_voisin = newA;
    s->L_voisin = newS;
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
    while(noeuds) {
        Noeud* actuel = noeuds->nd;
        Sommet* sommet = creeSommet(actuel->num,actuel->x,actuel->y);
        graphe->T_som[actuel->num] = sommet;
        noeuds = noeuds->suiv;
    }

    /* assotiation des vosins*/
    noeuds = r->noeuds;
    while(noeuds){
        Noeud*actuel = noeuds->nd;
        CellNoeud* voisins = actuel->voisins;
        Sommet* sommet =  graphe->T_som[actuel->num] ;
        while(voisins){ // on parcours les voisins pour associer chaque sommet voisins a sommet actuel
            Sommet* sommet_ajouter = graphe->T_som[voisins->nd->num];
            // insert sans doublons l'arete { u,v } u = sommet->num , v le sommet associer a voisins
            insererAreteVoisin(sommet_ajouter, sommet);
            // on passe au voisins suivant 
            voisins = voisins->suiv;
        }
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

#include <stdio.h>
#include <stdlib.h>

// La fonction cheminPlusCourt calcule le plus court chemin dans un graphe non pondéré entre deux sommets u et v
int cheminPlusCourt(Graphe *g, int u, int v) {
    if (g == NULL || u < 1 || v < 1 || u > g->nbsom || v > g->nbsom) {
        fprintf(stderr, "Paramètres invalides\n");
        return -1;
    }

    int *distance = malloc((g->nbsom + 1) * sizeof(int));  // Allocation dynamique pour le tableau des distances, +1 pour indexer de 1 à nbsom
    if (distance == NULL) {
        perror("Erreur d'allocation pour le tableau distance");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= g->nbsom; i++) {
        distance[i] = -1;  // Initialiser toutes les distances à -1, signifiant non visité
    }

    // Structure pour gérer une file d'attente simple
    int *queue = malloc((g->nbsom + 1) * sizeof(int));
    if (queue == NULL) {
        free(distance);
        perror("Erreur d'allocation pour la file");
        exit(EXIT_FAILURE);
    }

    int front = 0, rear = 0;  // Pointeurs de début et de fin pour la file
    queue[rear++] = u;  // Enfiler le sommet de départ u
    distance[u] = 0;  // La distance du sommet de départ à lui-même est 0

    while (front != rear) {  // Tant que la file n'est pas vide
        int sommet_courant = queue[front++];  // Défiler un élément
        Cellule_arete *cur = g->T_som[sommet_courant]->L_voisin;  // Accéder aux voisins du sommet

        while (cur != NULL) {
            int voisin = (cur->a->u == sommet_courant) ? cur->a->v : cur->a->u;
            if (distance[voisin] == -1) {  // Si le voisin n'a pas encore été visité
                distance[voisin] = distance[sommet_courant] + 1;  // Mettre à jour la distance
                queue[rear++] = voisin;  // Enfiler le voisin
                if (voisin == v) {  // Si le voisin est le sommet destination v
                    int result = distance[voisin];  // Sauvegarder le résultat
                    free(distance);  // Libérer le tableau de distance
                    free(queue);     // Libérer la file d'attente
                    return result;   // Retourner le résultat immédiatement
                }
            }
            cur = cur->suiv;  // Passer au voisin suivant
        }
    }

    free(distance);  // Libération des ressources allouées
    free(queue);
    return -1;  // Si aucun chemin n'a été trouvé, retourner -1
}
