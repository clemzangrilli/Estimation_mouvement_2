#include "Echantillonnage.h"
#include "Projet.h"

/** Methode de creation d'une structure �chantillonnage
  * @param mat_initiale matrice � �chantillonner
  * @param dimX_Initiale nombre de lignes de l'image
  * @param dimY_Initiale nombre de colonnes de l'image
  * @return une structure echantillonnage avec les matrices echantillonnees pr�tes � �tre rempli, et leurs dimensions
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
    if ((dimX_Initiale%2) !=0) {
        echantillon.dimX_E1 = (dimX_Initiale/2)+1;
    }
    else {
        echantillon.dimX_E1 = dimX_Initiale/2;
    }
    if ((dimY_Initiale%2) != 0) {
        echantillon.dimY_E1 = (dimY_Initiale/2)+1;
    }
    else {
        echantillon.dimY_E1 = (dimY_Initiale)/2;
    }
    echantillon.mat_E1 = creation_matrice(echantillon.dimX_E1,echantillon.dimY_E1);

    if ((echantillon.dimX_E1%2) != 0) {
        echantillon.dimX_E2 = (echantillon.dimX_E1/2)+1;
    }
    else {
        echantillon.dimX_E2 = echantillon.dimX_E1/2;
    }
    if ((echantillon.dimY_E1%2) != 0) {
        echantillon.dimY_E2 = (echantillon.dimY_E1/2)+1;
    }
    else {
        echantillon.dimY_E2 = (echantillon.dimY_E1/2);
    }
    echantillon.mat_E2 = creation_matrice(echantillon.dimX_E2,echantillon.dimY_E2);

    return echantillon;
}

/** Methode d'�chantillonnage d'une matrice
  * @param mat_initiale matrice � �chantillonner
  */
void echantillonnage (Echantillonnage* echantillon) {
    int i,j; //Indice mat � �chantillonner
    int l = 0; //Indice ligne matrice �chantillonn�e
    int p = 0; //Indice colonne matrice �chantillonn�e


    for (i=0 ; i<echantillon->dimX_Initiale ; i=i+2) { //Echantillonage facteur 2 (E1)
        for (j=0 ; j<echantillon->dimY_Initiale ; j=j+2) {
            echantillon->mat_E1[l][p] = echantillon->mat_Initiale[i][j];
            p++;
        }
        l++;
        p=0;
    }

    l=0;
    for (i=0 ; i<echantillon->dimX_Initiale ; i=i+4) { //Echantillonage facteur 4 (E2)
        for (j=0 ; j<echantillon->dimY_Initiale ; j=j+4) {
            echantillon->mat_E2[l][p] = echantillon->mat_Initiale[i][j];
            p++;
        }
        l++;
        p=0;
    }

}

/** Methode de creation et remplissage d'une structure �chantillonnage
  * @param mat_initiale matrice � �chantillonner
  * @param dimX_Initiale nombre de lignes de l'image
  * @param dimY_Initiale nombre de colonnes de l'image
  * @return une structure echantillonnage avec les matrices echantillonnees compl�t�es, et leurs dimensions
  */
Echantillonnage creation_remplissage_echantillon (double** mat_Initiale, int dimX_Initiale, int dimY_Initiale) {
    int i,j;
    Echantillonnage echantillon = creation_Echantillonnage(mat_Initiale,dimX_Initiale,dimY_Initiale);
    echantillonnage(&echantillon);
    return echantillon;
}
