#ifndef __CHAINE_H__
#define __CHAINE_H__	

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>

#define MAX_LINE_LENGTH 1024

/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;

CellPoint * creer_Cellpoint(double x, double y);
CellChaine * creer_Cellchaine(int numero,CellPoint * points);
Chaines * creer_Chaines(int gamma,int nbChaines, CellChaine * chaine);

void ajoute_point_cellpoint(CellPoint **p, double x, double y);
void ajoute_cellpoint_cellchaine(CellChaine **ch,int numero,CellPoint * p);
void ajoute_cellchaine_cellchaine(CellChaine **src,CellChaine *new);
int taille_CellPoint(CellPoint * p);

void affiche_CellPoint(CellPoint *p, FILE *f);
void affiche_CellChaine(CellChaine *ch,FILE *f);
void ecrireChaines(Chaines *C, FILE *f);

CellChaine * lire_ligne(char * ligne);
Chaines* lectureChaines(FILE *f);

double longueurChaine(CellChaine *c);

void afficheChainesSVG(Chaines *C, char* nomInstance);
double longueurTotale(Chaines *C);
int comptePointsTotal(Chaines *C);

void changeMinMax(double newx, double newy, double* xmin, double* ymin, double* xmax, double* ymax);
void chaineCoordMinMax(Chaines* C, double* xmin, double*ymin, double* xmax, double* ymax);

 Chaines* generationAleatoire(int nbChaines,int nbPointsChaine,int xmax,int ymax);
#endif	
