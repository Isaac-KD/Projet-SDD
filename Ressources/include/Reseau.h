#ifndef __RESEAU_H__
#define __RESEAU_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Chaine.h"


typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud *nd;               /* Pointeur vers le noeud stock\'e */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
};

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;       /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
Reseau* reconstitueReseauListe(Chaines *C);
void ecrireReseau(Reseau *R, FILE *f);
int nbLiaisons(Reseau *R);
int nbCommodites(Reseau *R);
void afficheReseauSVG(Reseau *R, char* nomInstance);

Reseau * creerReseau(int gamma);
Noeud* creerNoeud(int num, double x, double y);
CellNoeud * creerCellNoeud( Noeud * n);
CellCommodite * creerCellCommodite(Noeud *  extrA,Noeud * extrB);

void liberer_liste_CellNoeud(CellNoeud *liste);
void liberer_noeud(Noeud *noeud);
void libererNoeudSimple(CellNoeud *nd);
void liberer_liste_CellCommodite(CellCommodite *liste);
void liberer_tous_les_noeuds(CellNoeud *liste);
void liberer_reseau(Reseau *reseau);

void insererVoisins(Noeud * noeud1, Noeud * noeud2);
Noeud * insererReseau(Reseau * R, double x, double y);
#endif

