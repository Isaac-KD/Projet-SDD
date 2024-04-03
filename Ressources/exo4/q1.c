#include <stdlib.h>
#include "../Hachage.h"
#include "../Reseau.h"

int f( int x, int y ){
    return (int)((y+(x+y)*(x+y+1))/2);
}
int main(){
    int tab[5500];
    int nb=0;
    for (int i=0;i<5500;i++) tab[i]=0;
    for(int x=0;x<10;x++){ 
        for(int y=0;y<10;y++){
            tab[f(x,y)%25]+=1;
        }
    }
    for (int i=0;i<5500;i++) if (tab[i] >1) {
        printf("%d :  %d fois \n",i,tab[i]);
        nb++;
    }
    printf("%d \n",nb);
    /* on observe qu'il y a bcp de colision 9 pour 7 , 8 colision pour 6 alors que bcp d'autre on que 2 colision
     Non , ici la fontion n'est pas approrier 
     */
}