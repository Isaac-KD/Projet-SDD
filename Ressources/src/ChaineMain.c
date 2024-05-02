#include "../include/Chaine.h"

int main(){
    FILE* f = fopen("00014_burma.cha","r");
    Chaines*  C = lectureChaines(f);
    fclose(f);

    FILE* g = fopen("../exo1.2","w");
    ecrireChaines(C,g);
    fclose(g);

    afficheChaineSVG(C, "exo1.3");
    return 0;
}