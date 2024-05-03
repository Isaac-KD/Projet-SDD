#include "../include/Chaine.h"
#include "../include/Reseau.h"
#include "../include/ArbreQuat.h"
#include "../include/Hachage.h"
#include <time.h>
#include <stdio.h>

void genererDonneesPerformanceReconstitueReseauListe() {
    FILE *f = fopen("performances_econstitueReseauListe.txt", "w");
    int nbPointsChaine = 100;
    int xmax = 5000;
    int ymax = 5000;

    for (int nbChaines = 500; nbChaines <= 5000; nbChaines += 500) {
        printf(" torur n liste %d\n", nbChaines/500);
        Chaines *chaines = generationAleatoire(nbChaines, nbPointsChaine, xmax, ymax);
        clock_t debut = clock();
        Reseau* R = reconstitueReseauListe(chaines);
        clock_t fin = clock();
        double temps = (double)(fin - debut) / CLOCKS_PER_SEC;
        fprintf(f, "%d %f\n", nbChaines, temps);

        libereChaines(chaines);
        liberer_reseau(R);
    }

    fclose(f);
}

void genererDonneesPerformance() {
    FILE *f = fopen("performances.txt", "w");
    int nbPointsChaine = 100;
    int xmax = 5000;
    int ymax = 5000;

for (int nbChaines = 500; nbChaines <= 5000; nbChaines += 500) {
        printf("tour %d\n", nbChaines/500);
        Chaines *chaines = generationAleatoire(nbChaines, nbPointsChaine, xmax, ymax);

        clock_t debut, fin;
        double temps_arbre,temps_Hashage50;

        debut = clock();
        Reseau*R1 = reconstitueReseauHachage(chaines, 5000);
        fin = clock();
        temps_arbre = (double)(fin - debut) / CLOCKS_PER_SEC;

        debut = clock();
        Reseau*R2 = reconstitueReseauHachage(chaines, 1500);
        fin = clock();
        temps_Hashage50 = (double)(fin - debut) / CLOCKS_PER_SEC;
        /*
        debut = clock();
        Reseau*R3 = reconstitueReseauHachage(chaines, 5000);
        fin = clock();
        temps_Hashage100 = (double)(fin - debut) / CLOCKS_PER_SEC;

        debut = clock();
        Reseau*R4 = reconstitueReseauHachage(chaines, 50000);
        fin = clock();
        temps_Hashage200 = (double)(fin - debut) / CLOCKS_PER_SEC;
        */
        fprintf(f, "%d %f %f\n", nbChaines,temps_arbre,temps_Hashage50);

        // Libération de la mémoire si nécessaire
        liberer_reseau(R1);
        liberer_reseau(R2);
        //liberer_reseau(R3);
        //liberer_reseau(R4);
    }

    fclose(f);
}
int main() {
    genererDonneesPerformanceReconstitueReseauListe();
    genererDonneesPerformance();
    return 0;
}
