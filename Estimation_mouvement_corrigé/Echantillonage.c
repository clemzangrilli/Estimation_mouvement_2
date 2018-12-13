#include "Echantillonnage.h"
#include "Projet.h"


Echantillonnage creation_Echantillonnage (double** mat_initiale, int dimX_Initiale, int dimY_Initiale) {
    Echantillonnage echantillon;

    echantillon.dimX_Initiale = dimX_Initiale;
    echantillon.dimY_Initiale = dimY_Initiale;
    echantillon.mat_Initiale = creation_matrice(dimX_Initiale,dimY_Initiale);

    if ((dimY_Initiale%2) !=0) {
        echantillon.dimX_Echantillon_1 = dimX_Initiale;
        echantillon.dimY_Echantillon_1 = (dimY_Initiale/2)+1;
        echantillon.mat_Echantillon_1 = creation_matrice(echantillon.dimX_Echantillon_1,echantillon.dimY_Echantillon_1);

        echantillon.dimX_Echantillon_2 = dimX_Initiale;
        echantillon.dimY_Echantillon_2 = (echantillon.dimY_Echantillon_1)/2;
        echantillon.mat_Echantillon_2 = creation_matrice(echantillon.dimX_Echantillon_2,echantillon.dimY_Echantillon_2);
    }
    else {
        echantillon.dimX_Echantillon_1 = dimX_Initiale;
        echantillon.dimY_Echantillon_1 = (dimY_Initiale)/2;
        echantillon.mat_Echantillon_1 = creation_matrice(echantillon.dimX_Echantillon_1,echantillon.dimY_Echantillon_1);

        echantillon.dimX_Echantillon_2 = dimX_Initiale;
        echantillon.dimY_Echantillon_2 = (echantillon.dimY_Echantillon_1)/2;
        echantillon.mat_Echantillon_2 = creation_matrice(echantillon.dimX_Echantillon_2,echantillon.dimY_Echantillon_2);
    }
    return echantillon;
}

void echantillonnage (Echantillonnage* echantillon) {
    int i,j; //Indice mat à échantillonner
    int l = 0; //Indice ligne matrice échantillonnée
    int p; //Indice colonne matrice échantillonnée

    //Creation mat_echantillon_2
    for (i=0 ; i<echantillon->dimX_Initiale ; i++) {
        p=0;
        for (j=0 ; j<echantillon->dimY_Initiale ; j=j+2) {
            if ((i%2)==0) { //Cas ligne paire
                echantillon->mat_Echantillon_1[l][p] = echantillon->mat_Initiale[i][j];
            }
            else { //Cas ligne impaire
                echantillon->mat_Echantillon_1[l][p] = echantillon->mat_Initiale[i][j+1];
            }
            p++;
        }
        l++;
    }

    //Creation mat_echantillon_2
    l=0;
    for (i=0 ; i<echantillon->dimX_Echantillon_1 ; i++) {
        p=0;
        for (j=0 ; j<echantillon->dimY_Echantillon_1 ; j=j+2) {
            if ((i%2)==0) { //Cas ligne paire
                echantillon->mat_Echantillon_2[l][p] = echantillon->mat_Echantillon_1[i][j];
            }
            else { //Cas ligne impaire
                echantillon->mat_Echantillon_2[l][p] = echantillon->mat_Echantillon_1[i][j+1];
            }
            p++;
        }
        l++;
    }

}

Echantillonnage creation_remplissage_echantillon (double** mat_Initiale, int dimX_Initiale, int dimY_Initiale) {
    int i,j;
    Echantillonnage echantillon = creation_Echantillonnage(mat_Initiale,dimX_Initiale,dimY_Initiale);

    for (i=0 ; i<echantillon.dimX_Initiale ; i++) {
        for (j=0 ; j<echantillon.dimY_Initiale ; j++) {
            echantillon.mat_Initiale[i][j] = mat_Initiale[i][j];
        }
    }
    echantillonnage(&echantillon);
    return echantillon;
}
