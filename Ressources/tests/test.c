#include "Chaine.h"
/*
CellChaine * lire_ligne(FILE * f){
    char ligne[MAX_LINE_LENGTH];
    double numbers[MAX_NUMBERS];
    int i = 0;

    if (fgets(ligne, MAX_LINE_LENGTH, f) != NULL) {
        // Utilisation de sscanf pour extraire les nombres de la ligne
        double number;
        char *ptr = ligne;
        printf("%d %d \n",atoi(ptr),atoi(ptr+2));
        while (sscanf(ptr, "%lf", &number) == 1) {
            numbers[(i++)] = number;
            // Chercher le prochain espace
            while (*ptr && *ptr != ' ') {
                ptr++;
            }
            // Ignorer les espaces supplémentaires
            while (*ptr && *ptr == ' ') {
                ptr++;
            }
        }
    }
    CellPoint * p= creer_Cellpoint(numbers[2],numbers[3]);
    for (int j = 4; j < i; j+=2) {
        //printf("%.2lf ", numbers[j]);
        ajoute_point_cellpoint(&p, numbers[j], numbers[j+1]);
    }
    
    return creer_Cellchaine((int)(numbers[0]),p);
}
*/
int main() {

   FILE *f = fopen("/Users/isaac/Desktop/S4/structure_de_donnée/s5-10_projet/Ressources/00014_burma.cha","r");
   Chaines * c = lectureChaines(f);
    ecrireChaines(c,f); 
    fclose(f);
    FILE *g = fopen("tmp","w");
    ecrireChaines(c,g);
    fclose(g);
    return 0;
}