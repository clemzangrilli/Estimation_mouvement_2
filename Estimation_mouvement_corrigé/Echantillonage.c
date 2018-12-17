#include "Echantillonnage.h"
#include "Projet.h"

/** Methode de creation d'une structure échantillonnage
  * @param mat_initiale matrice à échantillonner
  * @param dimX_Initiale nombre de lignes de l'image
  * @param dimY_Initiale nombre de colonnes de l'image
  * @return une structure echantillonnage avec les matrices echantillonnees prêtes à être rempli, et leurs dimensions
  */
Echantillonnage creation_Echantillonnage (double** mat_Initiale, int dimX_Initiale, int dimY_Initiale) {
    int i;
    int j;

    Echantillonnage echantillon;

    echantillon.dimX_Initiale = dimX_Initiale;
    echantillon.dimY_Initiale = dimY_Initiale;
    echantillon.mat_Initiale = creation_matrice(dimX_Initiale,dimY_Initiale);

    for (i=0 ; i<echantillon.dimX_Initiale ; i++) {
        for (j=0 ; j<echantillon.dimY_Initiale ; j++) {
            echantillon.mat_Initiale[i][j] = mat_Initiale[i][j];
        }
    }
    //À modifier (enlever le cas impair)
    if ((dimY_Initiale%2) !=0) {
        echantillon.dimX_E1 = dimX_Initiale;
        echantillon.dimY_E1 = (dimY_Initiale/2);//+1
        echantillon.mat_E1 = creation_matrice(echantillon.dimX_E1,echantillon.dimY_E1);

        echantillon.dimX_E2 = dimX_Initiale;
        echantillon.dimY_E2 = (echantillon.dimY_E1)/2;
        echantillon.mat_E2 = creation_matrice(echantillon.dimX_E2,echantillon.dimY_E2);
    }
    else {
        echantillon.dimX_E1 = dimX_Initiale;
        echantillon.dimY_E1 = (dimY_Initiale)/2;
        echantillon.mat_E1 = creation_matrice(echantillon.dimX_E1,echantillon.dimY_E1);

        echantillon.dimX_E2 = dimX_Initiale;
        echantillon.dimY_E2 = (echantillon.dimY_E1)/2;
        echantillon.mat_E2 = creation_matrice(echantillon.dimX_E2,echantillon.dimY_E2);
    }
    return echantillon;
}

/** Methode d'échantillonnage d'une matrice
  * @param mat_initiale matrice à échantillonner
  */
void echantillonnage (Echantillonnage* echantillon) {
    int i,j; //Indice mat à échantillonner
    int l = 0; //Indice ligne matrice échantillonnée
    int p; //Indice colonne matrice échantillonnée

    //Creation mat_echantillon_1
    for (i=0 ; i<echantillon->dimX_Initiale ; i++) {
        p=0;
        for (j=0 ; j<echantillon->dimY_Initiale ; j=j+2) {
            if ((i%2)==0) { //Cas ligne paire
                echantillon->mat_E1[l][p] = echantillon->mat_Initiale[i][j];
            }
            else { //Cas ligne impaire
                if (j != (echantillon->dimY_Initiale-1)) { //Important pour ne pas sortir de la matrice
                    echantillon->mat_E1[l][p] = echantillon->mat_Initiale[i][j+1];
                }
            }
            p++;
        }
        l++;
    }

    //Creation mat_echantillon_2
    l=0;
    for (i=0 ; i<echantillon->dimX_E1 ; i++) {
        p=0;
        for (j=0 ; j<echantillon->dimY_E1 ; j=j+2) {
            if ((i%2)==0) { //Cas ligne paire
                echantillon->mat_E2[l][p] = echantillon->mat_E1[i][j];
            }
            else { //Cas ligne impaire
                if (j != (echantillon->dimY_E1-1)) { //Important pour ne pas sortir de la matrice
                    echantillon->mat_E2[l][p] = echantillon->mat_E1[i][j+1];
                }
            }
            p++;
        }
        l++;
    }

}

/** Methode de creation et remplissage d'une structure échantillonnage
  * @param mat_initiale matrice à échantillonner
  * @param dimX_Initiale nombre de lignes de l'image
  * @param dimY_Initiale nombre de colonnes de l'image
  * @return une structure echantillonnage avec les matrices echantillonnees complétées, et leurs dimensions
  */
Echantillonnage creation_remplissage_echantillon (double** mat_Initiale, int dimX_Initiale, int dimY_Initiale) {
    int i,j;
    Echantillonnage echantillon = creation_Echantillonnage(mat_Initiale,dimX_Initiale,dimY_Initiale);
    echantillonnage(&echantillon);
    return echantillon;
}
