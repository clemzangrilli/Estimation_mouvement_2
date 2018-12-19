#include "Interpolation.h"
#include "Echantillonnage.h"

/** Methode de creation d'une structure Interpolation
  * @param mat_E2 matrice échantillonnée 2 fois que l'on veut interpoler
  * @param dimX_E2 nombre de lignes de l'image échantillonnée 2 fois
  * @param dimY_E2 nombre de colonnes de l'image échantillonnée 2 fois
  * @return une structure Interpolation avec les matrices interpolées prêtes à être rempli, et leurs dimensions
  */
Interpolation creation_interpolation (double** mat_E2, Echantillonnage echantillon) {
    int i,j;
    Interpolation interpol;
    interpol.dimX_E2 = echantillon.dimX_E2;
    interpol.dimY_E2 = echantillon.dimY_E2;
    interpol.mat_E2 = creation_matrice(interpol.dimX_E2,interpol.dimY_E2);

    for (i=0 ; i<interpol.dimX_E2 ; i++) {
        for (j=0 ; j<interpol.dimY_E2 ; j++) {
            interpol.mat_E2[i][j] = mat_E2[i][j];
        }
    }

    interpol.dimX_E1 = echantillon.dimX_E1;
    interpol.dimY_E1 = echantillon.dimY_E1;
    interpol.mat_E1 = creation_matrice(interpol.dimX_E1,interpol.dimY_E1);

    interpol.dimX_init = echantillon.dimX_Initiale;
    interpol.dimY_init = echantillon.dimY_Initiale;
    interpol.mat_init = creation_matrice(interpol.dimX_init,interpol.dimY_init);

    return interpol;
}

double** interpolation (double** mat_E, int dimX_matE, int dimY_matE, int dimX_matI, int dimY_matI) {
    int i,j;
    int l=0;
    int p;
    int bool_dimX_pair = 0; //initialisation à false
    int bool_dimY_pair = 0;
    int dimX_impair = dimX_matI; //Initialisation comme si la matrice était déjà impair (sera modifié par le if si pair)
    int dimY_impair = dimY_matI;
    int dimX_pair,dimY_pair;
    double p1,p2,p3; //Necessaire pour la formule d'interpolation (poids dépendant de la distance)

    //Remplissage d'une valeur sur 2 de la matrice interpolee avec les valeur de la matrice échantillonnée

    double** mat_I = creation_matrice(dimX_matI, dimY_matI);
    for (i=0 ; i<dimX_matI ; i=i+2) {
        p=0;
        for (j=0 ; j<dimY_matI ; j=j+2) {
            mat_I[i][j] = mat_E[l][p];
            p++;
        }
        l++;
    }

    //On réduit les dimensions pour ne pas entrer dans les bords droit et bas
    if ((dimX_matI%2)==0) {
        bool_dimX_pair = 1;
        dimX_pair = dimX_matI;
        dimX_impair = dimX_matI - 1;
    }
    if ((dimY_matI%2)==0) {
        bool_dimY_pair = 1;
        dimY_pair = dimY_matI;
        dimY_impair = dimY_matI - 1;
    }

    for (i=0 ; i<dimX_impair ; i++) { //On parcourt comme si c'était une matrice paire, même si elle peut être impaire
        for (j=0 ; j<dimY_impair ; j++) {
            if ( (i%2)== 0 && (j%2)!=0 ) { //Sur les lignes paires on calcul une valeur sur 2 en partant de la deuxième
                mat_I[i][j] = (mat_I[i][j-1] + mat_I[i][j+1])/2.0;
            }
            else if ( (i%2)!=0 && (j%2)==0) { //Sur les lignes impaires on calcul une valeur sur 2 en partant de la première
                mat_I[i][j] = (mat_I[i+1][j] + mat_I[i-1][j])/2.0;
            }
            else if ( (i%2)!=0 && (j%2)!=0) { //Pixel entouré par 4 pixels en diagonal
                mat_I[i][j] = (mat_I[i-1][j-1] + mat_I[i-1][j+1] + mat_I[i+1][j-1] + mat_I[i+1][j+1])/4;
            }
            if (bool_dimX_pair == 1) { //Si la dimension dimX est paire (dernière ligne)
                if (j==0) {
                    p1 = 1.0/3.0; //2e valeur au-dessus
                    p2 = 1; //1ère valeur au-dessus
                    p3 = 1/sqrt(5); //Valeur au-dessus à droite
                    mat_I[dimX_pair-1][j] = (mat_I[(dimX_pair-1)-3][j]*p1 + mat_I[(dimX_pair-1)-1][j]*p2 + mat_I[(dimX_pair-1)-1][j+2]*p3)/(p1+p2+p3);//Coin inférieur gauche
                }
                else if ( (j%2)!=0 ) { //Entre deux pixels du dessus
                    p1 = 1.0/sqrt(2); //Valeur en haut à gauche
                    p2 = p1; //Valeur en haut à droite
                    mat_I[dimX_pair-1][j] = (mat_I[(dimX_pair-1)-1][j-1]*p1 + mat_I[(dimX_pair-1)-1][j+1]*p2)/(p1+p2);
                }
                else if ( ( (j%2) == 0 ) && (j!=0) && (j!=dimY_impair-1) ) { //On est sur les pixels des colonnes paires sans le premier à gauche et sans l'avant dernier à droite
                    p1 = 1/sqrt(5); //Valeur au-dessus à gauche
                    p2 = 1; //Valeur juste au-dessus
                    p3 = p1; //Valeur au-dessus à droite
                    mat_I[dimX_pair-1][j] = (mat_I[(dimX_pair-1)-1][j-2]*p1 + mat_I[(dimX_pair-1)-1][j]*p2 + mat_I[(dimX_pair-1)-1][j+2]*p3)/(p1+p2+p3);
                }
                else if (j==dimY_impair-1) { //Avant dernier pixel à droite
                    p1 = 1.0/3.0; //2e valeur au-dessus
                    p2 = 1; //1ère valeur au-dessus
                    p3 = 1/sqrt(5); //Valeur au-dessus à droite
                    mat_I[dimX_pair-1][j] = (mat_I[(dimX_pair-1)-3][j]*p1 + mat_I[(dimX_pair-1)-1][j]*p2 + mat_I[(dimX_pair-1)-1][j-2]*p3)/(p1+p2+p3);
                }
            }
            if (bool_dimY_pair == 1) { //Si la dimension dimY est paire (dernière colonne)
                if (i==0) {//Coin supérieur droit
                    p1 = 1.0/3.0; //2e valeur à gauche
                    p2 = 1; //1ère valeur à gauche
                    p3 = 1/sqrt(5); //Valeur à gauche en dessous
                    mat_I[i][dimY_pair-1] = (mat_I[i][(dimY_pair-1)-3]*p1 + mat_I[i][(dimY_pair-1)-1]*p2 + mat_I[i+2][(dimY_pair-1)-1]*p3)/(p1+p2+p3);
                }
                else if ( (i%2)!=0) { //Entre deux pixels de gauche
                    p1 = 1.0/sqrt(2); //Valeur en haut à gauche
                    p2 = p1; //Valeur en bas à gauche
                    mat_I[i][dimY_pair-1] = (mat_I[i-1][(dimY_pair-1)-1]*p1 + mat_I[i+1][(dimY_pair-1)-1]*p2)/(p1+p2);
                }
                else if ( (i%2)==0 && (i!=0) && (i!=dimX_impair-1)) { //Pixels des lignes paires sans le premier (en haut) et l'avant dernier (bas)
                    p1 = 1/sqrt(5); //Valeur en haut à gauche
                    p2 = 1; //Valeur juste à gauche
                    p3 = p1; //Valeur en bas à gauche
                    mat_I[i][dimY_pair-1] = (mat_I[i-2][(dimY_pair-1)-1]*p1 + mat_I[i][(dimY_pair-1)-1]*p2 + mat_I[i+2][(dimY_pair-1)-1]*p3)/(p1+p2+p3);
                }
                else if ( (i==dimX_impair-1)) { //Avant dernier pixel
                    p1 = 1.0/3.0; //2e valeur à gauche
                    p2 = 1; //1ère valeur à gauche
                    p3 = 1/sqrt(5); //Valeur à gauche au-dessus
                    mat_I[i][dimY_pair-1] = (mat_I[i][(dimY_pair-1)-3]*p1 + mat_I[i][(dimY_pair-1)-1]*p2 + mat_I[i-2][(dimY_pair-1)-1]*p3)/(p1+p2+p3);
                }
            }
            if (bool_dimX_pair == 1 && bool_dimY_pair == 1) { //Si les dimensions dimX et dimY sont paires
                p1 = 1.0/sqrt(10); //2e valeur en haut à gauche
                p2 = 1.0/sqrt(2); //1ère valeur à gauche
                p3 = 1/sqrt(10); //2e valeur à gauche
                mat_I[dimX_pair-1][dimY_pair-1] = (mat_I[(dimX_pair-3)-1][(dimY_pair-1)-1]*p1 + mat_I[(dimX_pair-1)-1][(dimY_pair-1)-1]*p2 + mat_I[(dimX_pair-1)-1][(dimY_pair-1)-3]*p3)/(p1+p2+p3);//Coin inférieur droit
            }
        }
    }
    return mat_I;
}

/** Methode de remplissage d'une structure Interpolation
  * @param interpol la structure Interpolation à remplir
  */
void remplissage_interpolation (Interpolation* interpol) {
    int i,j;
    double** mat_E1 = interpolation(interpol->mat_E2,interpol->dimX_E2,interpol->dimY_E2,interpol->dimX_E1,interpol->dimY_E1);
    for (i=0 ; i<interpol->dimX_E1 ; i++) {
        for (j=0 ; j<interpol->dimY_E1 ; j++) {
            interpol->mat_E1[i][j] = mat_E1[i][j];
        }
    }
    double** mat_init = interpolation(interpol->mat_E1,interpol->dimX_E1,interpol->dimY_E1,interpol->dimX_init,interpol->dimY_init);

    for (i=0 ; i<interpol->dimX_init ; i++) {
        for (j=0 ; j<interpol->dimY_init ; j++) {
            interpol->mat_init[i][j] = mat_init[i][j];
        }
    }
}

/** Methode de creation et remplissage d'une structure Interpolation
  * @param mat_E2 matrice échantillonnée 2 fois que l'on veut interpoler
  * @param echantillon la structure echantillon contenant entre autre les dimensions
  * @return une structure Interpolation avec les matrices interpolées complétées, et leurs dimensions
  */
Interpolation creation_remplissage_interpolation (double** mat_E2, Echantillonnage echantillon) {
    Interpolation interpol = creation_interpolation(mat_E2,echantillon);
    remplissage_interpolation(&interpol);
    return interpol;
}
