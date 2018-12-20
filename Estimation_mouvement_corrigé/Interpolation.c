#include "Interpolation.h"
#include "Echantillonnage.h"

/** Methode de creation d'une structure Interpolation
  * @param mat_E2 matrice �chantillonn�e 2 fois que l'on veut interpoler
  * @param echantillon la structure Echantillon
  * @return une structure Interpolation compl�t�e
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

/** Methode de creation d'une matrice interpol�e une fois � partir d'une matrice (�chantillonn�e)
  * @param mat_E matrice �chantillonn�e que l'on veut interpoler
  * @param dimX_matE le nombre de ligne de la matrice �chantillonn�e
  * @param dimY_matE le nombre de colonne de la matrice �chantillonn�e
  * @param dimX_matI le nombre de ligne de la matrice interpol�e
  * @param dimY_matI le nombre de colonnes de la matrice interpol�e
  * @return une matrice obtenue par interpolation
  */
double** interpolation (double** mat_E, int dimX_matE, int dimY_matE, int dimX_matI, int dimY_matI) {
    int i,j;
    int l=0;
    int p;
    int bool_dimX_pair = 0; //initialisation � false
    int bool_dimY_pair = 0;
    int dimX_impair = dimX_matI; //Initialisation comme si la matrice �tait d�j� impair (sera modifi� par le if si pair)
    int dimY_impair = dimY_matI;
    int dimX_pair,dimY_pair;
    double p1,p2,p3; //Necessaire pour la formule d'interpolation (poids d�pendant de la distance)

    //Remplissage d'une valeur sur 2 de la matrice interpolee avec les valeur de la matrice �chantillonn�e

    double** mat_I = creation_matrice(dimX_matI, dimY_matI);
    for (i=0 ; i<dimX_matI ; i=i+2) {
        p=0;
        for (j=0 ; j<dimY_matI ; j=j+2) {
            mat_I[i][j] = mat_E[l][p];
            p++;
        }
        l++;
    }

    //On r�duit les dimensions pour ne pas entrer dans les bords droit et bas
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

    for (i=0 ; i<dimX_impair ; i++) { //On parcourt comme si c'�tait une matrice paire, m�me si elle peut �tre impaire
        for (j=0 ; j<dimY_impair ; j++) {
            if ( (i%2)== 0 && (j%2)!=0 ) { //Sur les lignes paires on calcul une valeur sur 2 en partant de la deuxi�me
                mat_I[i][j] = (mat_I[i][j-1] + mat_I[i][j+1])/2.0;
            }
            else if ( (i%2)!=0 && (j%2)==0) { //Sur les lignes impaires on calcul une valeur sur 2 en partant de la premi�re
                mat_I[i][j] = (mat_I[i+1][j] + mat_I[i-1][j])/2.0;
            }
            else if ( (i%2)!=0 && (j%2)!=0) { //Pixel entour� par 4 pixels en diagonal
                mat_I[i][j] = (mat_I[i-1][j-1] + mat_I[i-1][j+1] + mat_I[i+1][j-1] + mat_I[i+1][j+1])/4;
            }
            if (bool_dimX_pair == 1) { //Si la dimension dimX est paire (derni�re ligne)
                if (j==0) {
                    p1 = 1.0/3.0; //2e valeur au-dessus
                    p2 = 1; //1�re valeur au-dessus
                    p3 = 1/sqrt(5); //Valeur au-dessus � droite
                    mat_I[dimX_pair-1][j] = (mat_I[(dimX_pair-1)-3][j]*p1 + mat_I[(dimX_pair-1)-1][j]*p2 + mat_I[(dimX_pair-1)-1][j+2]*p3)/(p1+p2+p3);//Coin inf�rieur gauche
                }
                else if ( (j%2)!=0 ) { //Entre deux pixels du dessus
                    p1 = 1.0/sqrt(2); //Valeur en haut � gauche
                    p2 = p1; //Valeur en haut � droite
                    mat_I[dimX_pair-1][j] = (mat_I[(dimX_pair-1)-1][j-1]*p1 + mat_I[(dimX_pair-1)-1][j+1]*p2)/(p1+p2);
                }
                else if ( ( (j%2) == 0 ) && (j!=0) && (j!=dimY_impair-1) ) { //On est sur les pixels des colonnes paires sans le premier � gauche et sans l'avant dernier � droite
                    p1 = 1/sqrt(5); //Valeur au-dessus � gauche
                    p2 = 1; //Valeur juste au-dessus
                    p3 = p1; //Valeur au-dessus � droite
                    mat_I[dimX_pair-1][j] = (mat_I[(dimX_pair-1)-1][j-2]*p1 + mat_I[(dimX_pair-1)-1][j]*p2 + mat_I[(dimX_pair-1)-1][j+2]*p3)/(p1+p2+p3);
                }
                else if (j==dimY_impair-1) { //Avant dernier pixel � droite
                    p1 = 1.0/3.0; //2e valeur au-dessus
                    p2 = 1; //1�re valeur au-dessus
                    p3 = 1/sqrt(5); //Valeur au-dessus � droite
                    mat_I[dimX_pair-1][j] = (mat_I[(dimX_pair-1)-3][j]*p1 + mat_I[(dimX_pair-1)-1][j]*p2 + mat_I[(dimX_pair-1)-1][j-2]*p3)/(p1+p2+p3);
                }
            }
            if (bool_dimY_pair == 1) { //Si la dimension dimY est paire (derni�re colonne)
                if (i==0) {//Coin sup�rieur droit
                    p1 = 1.0/3.0; //2e valeur � gauche
                    p2 = 1; //1�re valeur � gauche
                    p3 = 1/sqrt(5); //Valeur � gauche en dessous
                    mat_I[i][dimY_pair-1] = (mat_I[i][(dimY_pair-1)-3]*p1 + mat_I[i][(dimY_pair-1)-1]*p2 + mat_I[i+2][(dimY_pair-1)-1]*p3)/(p1+p2+p3);
                }
                else if ( (i%2)!=0) { //Entre deux pixels de gauche
                    p1 = 1.0/sqrt(2); //Valeur en haut � gauche
                    p2 = p1; //Valeur en bas � gauche
                    mat_I[i][dimY_pair-1] = (mat_I[i-1][(dimY_pair-1)-1]*p1 + mat_I[i+1][(dimY_pair-1)-1]*p2)/(p1+p2);
                }
                else if ( (i%2)==0 && (i!=0) && (i!=dimX_impair-1)) { //Pixels des lignes paires sans le premier (en haut) et l'avant dernier (bas)
                    p1 = 1/sqrt(5); //Valeur en haut � gauche
                    p2 = 1; //Valeur juste � gauche
                    p3 = p1; //Valeur en bas � gauche
                    mat_I[i][dimY_pair-1] = (mat_I[i-2][(dimY_pair-1)-1]*p1 + mat_I[i][(dimY_pair-1)-1]*p2 + mat_I[i+2][(dimY_pair-1)-1]*p3)/(p1+p2+p3);
                }
                else if ( (i==dimX_impair-1)) { //Avant dernier pixel
                    p1 = 1.0/3.0; //2e valeur � gauche
                    p2 = 1; //1�re valeur � gauche
                    p3 = 1/sqrt(5); //Valeur � gauche au-dessus
                    mat_I[i][dimY_pair-1] = (mat_I[i][(dimY_pair-1)-3]*p1 + mat_I[i][(dimY_pair-1)-1]*p2 + mat_I[i-2][(dimY_pair-1)-1]*p3)/(p1+p2+p3);
                }
            }
            if (bool_dimX_pair == 1 && bool_dimY_pair == 1) { //Si les dimensions dimX et dimY sont paires
                p1 = 1.0/sqrt(10); //2e valeur en haut � gauche
                p2 = 1.0/sqrt(2); //1�re valeur � gauche
                p3 = 1/sqrt(10); //2e valeur � gauche
                mat_I[dimX_pair-1][dimY_pair-1] = (mat_I[(dimX_pair-3)-1][(dimY_pair-1)-1]*p1 + mat_I[(dimX_pair-1)-1][(dimY_pair-1)-1]*p2 + mat_I[(dimX_pair-1)-1][(dimY_pair-1)-3]*p3)/(p1+p2+p3);//Coin inf�rieur droit
            }
        }
    }
    return mat_I;
}

/** Methode de remplissage d'une structure Interpolation
  * @param interpol la structure Interpolation � remplir
  */
void remplissage_interpolation (Interpolation* interpol) {
    int i,j;
    double** mat_E1 = interpolation(interpol->mat_E2,interpol->dimX_E2,interpol->dimY_E2,interpol->dimX_E1,interpol->dimY_E1);
    for (i=0 ; i<interpol->dimX_E1 ; i++) {
        for (j=0 ; j<interpol->dimY_E1 ; j++) {
            interpol->mat_E1[i][j] = mat_E1[i][j];
        }
    }
    remplissage_fichier_double("U_E1.txt",interpol->dimX_E1,interpol->dimY_E1,interpol->mat_E1);
    remplissage_fichier_double("U_E2.txt",interpol->dimX_E2,interpol->dimY_E2,interpol->mat_E2);
    double** mat_init = interpolation(interpol->mat_E1,interpol->dimX_E1,interpol->dimY_E1,interpol->dimX_init,interpol->dimY_init);

    for (i=0 ; i<interpol->dimX_init ; i++) {
        for (j=0 ; j<interpol->dimY_init ; j++) {
            interpol->mat_init[i][j] = mat_init[i][j];
        }
    }
}

/** Methode de creation et remplissage d'une structure Interpolation
  * @param mat_E2 matrice �chantillonn�e 2 fois que l'on veut interpoler
  * @param echantillon la structure echantillon contenant entre autre les dimensions
  * @return une structure Interpolation avec les matrices interpol�es compl�t�es, et leurs dimensions
  */
Interpolation creation_remplissage_interpolation (double** mat_E2, Echantillonnage echantillon) {
    Interpolation interpol = creation_interpolation(mat_E2,echantillon);
    remplissage_interpolation(&interpol);
    return interpol;
}
