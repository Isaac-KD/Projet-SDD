#include "../include/Reseau.h"
#include "../include/ArbreQuat.h"
#include "../include/Hachage.h"
#include "../include/Chaine.h"
#include <stdio.h>
#include <time.h>

int main() {

    int M = 10;
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
    //reconstitueReseauArbre(C);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(file, "Temps pour reconstitueReseauArbre: %f secondes\n", cpu_time_used);

    // Mesure du temps pour reconstitueReseauHachage
    start = clock();
    Reseau *R2 =reconstitueReseauHachage(C, M);
    printf(" reseaux construit\n");
    end = clock();
    if(! R2) printf( "Reseau NULL \n");
    FILE *f = fopen("reseau2","w");
    ecrireReseau(R2,f);
    fclose(f);
    afficheReseauSVG(R2, "Hachage.html");

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

    Chaines *CA = generationAleatoire(10,20,200,200);
    printf("CA = %p \n",CA);
    FILE * g = fopen("tmpAleatoire","w");
    ecrireChaines(CA,g);
    fclose(g);

    libereChaines(CA);
    libereChaines(C);
    liberer_reseau(R2);
    return 0;
}
