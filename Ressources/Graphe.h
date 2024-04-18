#ifndef __GRAPHE_H__
#define __GRAPHE_H__

#include <stdlib.h>
#include <stdio.h>
#include "StructListe.h"  
#include "Reseau.h"
typedef struct {
    int u, v;  // Numéros des sommets extrémité
} Arete;

typedef struct cellule_arete {
    Arete *a;  /* Pointeur sur l'arête */
    struct cellule_arete *suiv;  
} Cellule_arete;

typedef struct {
    int num;                     /*Numéro du sommet (le même que dans T_som)*/
    double x, y; 
    Cellule_arete *L_voisin;     /*Liste chaînée des voisins*/
} Sommet;

typedef struct {
    int e1, e2;  /*Les deux extrémités de la commodité*/
} Commod;

typedef struct {
    int nbsom;         /* Nombre de sommets */
    Sommet **T_som;    /* Tableau de pointeurs sur sommets */
    int gamma;  
    int nbcommod;      /* Nombre de commodités */
    Commod *T_commod;  /* Tableau des commodités */
} Graphe;

// Déclarations de fonctions pour manipuler des graphes
Graphe *creerGraphe(Reseau *r); 
//int cheminPlusCourt(Graphe *g, int u, int v); 
//ListeEntiers *retrouverChemin(Graphe *g, int u, int v);
//int reorganiseReseau(Reseau* r);
#endif // __GRAPHE_H__
