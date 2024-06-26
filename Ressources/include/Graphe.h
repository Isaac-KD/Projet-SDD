#ifndef __GRAPHE_H__
#define __GRAPHE_H__

#include <stdlib.h>
#include <stdio.h>
#include "Struct_File.h"  
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
   Commod *T_commod; /* Tableau des commodités */
} Graphe;

/* Utiliser pour trouver le chemin le plus court*/
typedef struct liste {
    int valeur;
    struct liste *suiv;
} Liste;

// Déclarations de fonctions pour manipuler des graphes
Arete* creeArete(int u  ,int v);
Cellule_arete* creeCellule_arete( Arete * a);
Sommet* creeSommet(int num,double x,double y);
void libererGraphe(Graphe** G);

void ajouterEnTete(Liste **tete, int valeur) ;
void libereListe(Liste *tete);

// permet d'inserer l'arete {u,v} dans le sommet s si il n'existe pas deja
void insererAreteVoisin( Sommet*s,Sommet*actuel);
void affiche_graphe(Graphe *g, const char *filename);
Graphe *creerGraphe(Reseau *r); 


int cheminPlusCourt(Graphe *g, int u, int v); 
// Calcule le plus court chemin de u à v et retourne le chemin sous forme de liste d'entiers
void ajouterEnTete(Liste **tete, int valeur) ;
void afficheListe(Liste *tete);
Liste* retrouverChemin(Graphe *g, int u, int v);
int reorganiseReseau(Reseau* r);
#endif // __GRAPHE_H__
