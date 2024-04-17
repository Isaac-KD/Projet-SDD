printf("cas 2 xc = %f yc = %f and nx = %f ny = %f \n",xc,yc,nx,ny);
        // cas ou il faut creer des sous arbres
        Noeud * noeudInitial = (*a)->noeud;
        if( (noeudInitial->x == n->x) && (noeudInitial->y == n->y)) return; // si on inserer deux noeud a la meme position on risque d'avoir des appelles infinie
        (*a)->noeud = NULL;

        double Ix = noeudInitial->x; double Iy = noeudInitial->y; // position du noeud initial

        /* On reinsere le noeud deja present en fonction de la posititon */
        if(Ix < xc && Iy < yc){
            printf("so IN \n");
             printf("cas 2 xc = %f yc = %f and nx = %f ny = %f \n",xc,yc,nx,ny);
            insererNoeudArbre(noeudInitial,&((*a)->so),(*a));    //cas so, on insere le noeud deja present 
        }
        else if (Ix >= xc && Iy < yc){
            printf("se IN");
            insererNoeudArbre(noeudInitial,&((*a)->se),(*a));    //cas se, on insere le noeud deja present 
        }
        else if (Ix < xc && Iy >= yc){
            printf("no IN");
            insererNoeudArbre(noeudInitial,&((*a)->no),(*a));    // cas no, on insere le noeud deja present 
        }   
        else if (Ix >= xc && Iy >= yc){
            printf("ne IN");
            insererNoeudArbre(noeudInitial,&((*a)->ne),(*a));    //cas ne, on insere le noeud deja present 
        }

        /* On insere le nouveau en fonction de la posititon */
        if(nx < xc && ny < yc){
            printf("so\n ");
             printf("cas so, xc = %f yc = %f and nx = %f ny = %f \n",xc,yc,nx,ny);
            insererNoeudArbre(n,&((*a)->so),(*a));    //cas so, on insere le nouveau noeud
            return;
        }
        else if (nx >= xc && ny < yc){
            printf("se ");
            insererNoeudArbre(n,&((*a)->se),(*a));    //cas se, on insere le nouveau noeud
        }
        else if (nx < xc && ny >= yc){
            printf("no ");
            insererNoeudArbre(n,&((*a)->no),(*a));    // cas no, on insere le nouveau noeud
        }   
        else if (nx >= xc && ny >= yc){
            printf("ne");
            insererNoeudArbre(n,&((*a)->ne),(*a));    //cas ne, on insere le nouveau noeud
        }
        return;
    }
    if(( *a != NULL) && ((*a)->noeud == NULL)){
        printf(" cas 3 \n");
        /*cas ou on doit parcourir l'arbre*/
        if(nx < xc && ny < yc){
            insererNoeudArbre(n,(&(*a)->so),(*a));    //cas on parrcours le sous arbre so
        }
        else if (nx >= xc && ny < yc){
            insererNoeudArbre(n,(&(*a)->se),(*a));    //cas on parrcours le sous arbre se
        }
        else if (nx < xc && ny >= yc){
            insererNoeudArbre(n,(&(*a)->no),(*a));    // cas on parrcours le sous arbre no
        }   
        else if (nx >= xc && ny >= yc){
            insererNoeudArbre(n,(&(*a)->ne),(*a));    //cas on parrcours le sous arbre ne
        }
        return;
    }
}

Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat*parent, double x, double y){
    /* cas ou l'arbre est vide */
    if( ! *a){
        printf("Arbre vide: Création et insertion d'un nouveau noeud.\n");
        Noeud* n = insererReseau(R,x,y); // On creer et insere un noeud dans le Reseau
        insererNoeudArbre(n,a,parent); // on insere le noeud dans l'arbre
        printf(" xc = %lf, yc = %lf \n",(*a)->xc,(*a)->yc);
        return n;
    }
  
    if ((*a)->noeud != NULL){
        printf("Feuille trouvée: Vérification du noeud existant.\n");
        Noeud * noeudInitial =(*a)->noeud; // le noeud actuel
         if( (noeudInitial->x == x) && (noeudInitial->y == y)) return noeudInitial;// retourne le noeud deja existant
         else{
            printf("inserer n\n");	
            Noeud* n = insererReseau(R,x,y); // On creer ou insere un noeud dans le Reseau
            printf("inserer n arbre \n");
            insererNoeudArbre(n,a,parent); // on insere le noeud dans l'arbre
            printf(" ok  \n");
            return n;
         }