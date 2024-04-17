#include "Reseau.h"
#include "ArbreQuat.h"
#include "Hachage.h"
#include "Chaine.h"
#include <stdio.h>
#include <time.h>

int main() {
    printf(" Strat \n");
    FILE *src = fopen("00014_burma.cha", "r");
    if (src == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier source.\n");
        return 1;
    }

    Chaines* C = lectureChaines(src);
    fclose(src);  // Fermer le fichier source après la lecture

    FILE* e = fopen("tmp","w");
    ecrireChaines(C,e);
    fclose(e); 
    //int M = 10;  // Taille pour la table de hachage
    clock_t start, end;
    double cpu_time_used;

    FILE *file = fopen("resultats_temps.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de résultats.\n");
        return 1;
    }
    
    // Mesure du temps pour reconstitueReseauArbre
    start = clock();
    printf("ok\n");
    reconstitueReseauArbre(C);
    printf("Reseau passedddddddddddddddddd \n ");
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(file, "Temps pour reconstitueReseauArbre: %f secondes\n", cpu_time_used);

    // Mesure du temps pour reconstitueReseauHachage
    start = clock();
    //Reseau *R2 =reconstitueReseauHachage(C, M);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(file, "Temps pour reconstitueReseauHachage: %f secondes\n", cpu_time_used);

    // Mesure du temps pour reconstitueReseauListe
    start = clock();
    //Reseau *R3 =reconstitueReseauListe(C);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(file, "Temps pour reconstitueReseauListe: %f secondes\n", cpu_time_used);

    fclose(file);

    printf(" Finish \n");
    return 0;
}
