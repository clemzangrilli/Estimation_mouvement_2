#include "Interpolation.h"
#include "Echantillonnage.h"

/** Methode de creation d'une structure Interpolation
  * @param mat_E2 matrice échantillonnée 2 fois que l'on veut interpoler
  * @param dimX_E2 nombre de lignes de l'image échantillonnée 2 fois
  * @param dimY_E2 nombre de colonnes de l'image échantillonnée 2 fois
  * @return une structure Interpolation avec les matrices interpolées prêtes à être rempli, et leurs dimensions
  */
Interpolation creation_interpolation (double** mat_E2, int dimX_E2, int dimY_E2) {
    int i,j;
    Interpolation interpol;
    interpol.dimX_E2 = dimX_E2;
    interpol.dimY_E2 = dimY_E2;
    interpol.mat_E2 = creation_matrice(dimX_E2,dimY_E2);

    for (i=0 ; i<interpol.dimX_E2 ; i++) {
        for (j=0 ; j<interpol.dimY_E2 ; j++) {
            interpol.mat_E2[i][j] = mat_E2[i][j];
        }
    }

    interpol.dimX_E1 = dimX_E2;
    interpol.dimY_E1 = dimY_E2*2;
    interpol.mat_E1 = creation_matrice(interpol.dimX_E1,interpol.dimY_E1);

    interpol.dimX_init = dimX_E2;
    interpol.dimY_init = 2*(interpol.dimY_E1);
    interpol.mat_init = creation_matrice(interpol.dimX_init,interpol.dimY_init);

    return interpol;
}

/** Methode de remplissage d'une structure Interpolation
  * @param interpol la structure Interpolation à remplir
  */
void interpolation_mat (Interpolation* interpol) {
    int i,j;
    int l=0;
    int p;

    //Remplissage d'une valeur sur 2 de la matrice vitesse_interpolee_1 avec les valeur de vitesse_echantillon_2

    for (i=0 ; i<interpol->dimX_E1 ; i++) {
        p=0;
        for (j=0 ; j<interpol->dimY_E1 ; j=j+2) {
            if ((i%2)==0) {
                interpol->mat_E1[i][j] = interpol->mat_E2[l][p];
            }
            else {
                if (j!=(interpol->dimY_E1-1)) { //Sinon ne marchera pas pour image à nb de colonnes pair
                    interpol->mat_E1[i][j+1] = interpol->mat_E2[l][p];
                }
            }
            p++;
        }
        l++;
    }
    double** mat_moyenne_temp = creation_matrice(interpol->dimX_E1, interpol->dimY_E1); //Création d'une matrice moyenne temporaire
    moyenne (interpol->mat_E1,mat_moyenne_temp,interpol->dimX_E1,interpol->dimY_E1); //Calcul de la matrice moyenne de la matrice interpollée incomplète
                                                                                     //Pour lui prendre une valeur sur 2
    for (i=0 ; i<interpol->dimX_E1 ; i++) {
        for (j=0 ; j<interpol->dimY_E1 ; j=j+2) {
            if ((i%2)==0 && j!=(interpol->dimY_E1-1)) {
                interpol->mat_E1[i][j+1] = mat_moyenne_temp[i][j+1];
            }
            else {
                interpol->mat_E1[i][j] = mat_moyenne_temp[i][j];
            }
        }
    }
    //Deuxième interpolation
    l=0;
    for (i=0 ; i<interpol->dimX_init ; i++) {
        p=0;
        for (j=0 ; j<interpol->dimY_init ; j=j+2) {
            if ((i%2)==0) {
                interpol->mat_init[i][j] = interpol->mat_E1[l][p];
            }
            else {
                if (j!=(interpol->dimY_E1-1)) { //Sinon ne marchera pas pour image à nb de colonnes pair
                    interpol->mat_init[i][j+1] = interpol->mat_E1[l][p];
                }
            }
            p++;
        }
        l++;
    }

    double** mat_moyenne_temp2 = creation_matrice(interpol->dimX_init, interpol->dimY_init);//Création d'une matrice moyenne temporaire
    moyenne (interpol->mat_init,mat_moyenne_temp2,interpol->dimX_init,interpol->dimY_init); //Calcul de la matrice moyenne de la matrice interpollée incomplète
                                                                                            //Pour lui prendre une valeur sur 2
    for (i=0 ; i<interpol->dimX_init ; i++) {
        for (j=0 ; j<interpol->dimY_init ; j=j+2) {
            if ((i%2)==0 && j!=(interpol->dimY_init-1)) {
                interpol->mat_init[i][j+1] = mat_moyenne_temp2[i][j+1];
            }
            else {
                interpol->mat_init[i][j] = mat_moyenne_temp2[i][j];
            }
        }
    }
}

/** Methode de creation et remplissage d'une structure Interpolation
  * @param mat_E2 matrice échantillonnée 2 fois que l'on veut interpoler
  * @param dimX_E2 nombre de lignes de l'image échantillonnée 2 fois
  * @param dimY_E2 nombre de colonnes de l'image échantillonnée 2 fois
  * @return une structure Interpolation avec les matrices interpolées complétées, et leurs dimensions
  */
Interpolation creation_remplissage_interpolation (double** mat_E2, int dimX_E2, int dimY_E2) {
    Interpolation interpol = creation_interpolation(mat_E2,dimX_E2,dimY_E2);
    interpolation_mat(&interpol);
    return interpol;
}
