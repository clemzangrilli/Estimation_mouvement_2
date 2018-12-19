#include "U_et_V.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** Methode de creation d'une structure Vitesse
  * @param dimX nombre de lignes de l'image dont on calcule la vitesse
  * @param dimY nombre de colonnes de l'image dont on calcule la vitesse
  * @return une structure Vitesse avec les matrices vitesses et vitesses moyennes pr�tes � �tre remplies, et leurs dimensions
  */
Vitesse creation_vitesse (dimX, dimY) {
    Vitesse vitesses;
    vitesses.U = creation_matrice(dimX,dimY);
    vitesses.V = creation_matrice(dimX,dimY);
    vitesses.dimX = dimX;
    vitesses.dimY = dimY;

    return vitesses;
}

/** Methode de calcul de la moyenne d'une matrice
  * @param mat la matrice dont on veut calculer la moyenne des pixels autour de chaques pixels
  * @param mat_moyenne la matrice qui contiendra la valeur de ces moyennes aux coordonn�es du pixel initial
  * @param dimX le nombre de ligne de la matrice dont on veut calculer la moyenne
  * @param dimY le nombre de colonne de la matrice dont on veut calculer la moyenne
  */
void moyenne (double **mat, double **mat_moyenne, int dimx, int dimy) { //Rentre le r�sultat de la moyenne dans une matrice "moyenne" qu'on lui donne (plus malin que de cr�er une matrice � chaque appel)
    int k = 0;
    int j;

    for (k=0 ; k<dimx ; k++) {
        for (j=0 ; j<dimy ; j++) {

            if (k!=0 && j!=0 && k!=dimx-1 && j!=dimy-1) { //Image sans les bords
                mat_moyenne[k][j] = (mat[k-1][j] + mat[k][j+1] + mat[k+1][j] + mat[k][j-1])/4;
            }
            else { //On est sur les bords
                if ( k==0 && j==0 ) { //Coins en haut � gauche
                    mat_moyenne[k][j] = (mat[k+1][j] + mat[k][j+1])/2;
                }
                else if ( k==dimx-1 && j==0 ) { //Coin en bas � gauche
                    mat_moyenne[k][j] = (mat[k-1][j] + mat[k][j+1])/2;
                }
                else if ( k==0 && j==dimy-1 ) { //Coin en haut � droite
                    mat_moyenne[k][j] = (mat[k+1][j] + mat[k][j-1])/2;
                }
                else if ( k==dimx-1 && j==dimy-1 ) {//Coin en bas � droite
                    mat_moyenne[k][j] = (mat[k-1][j] + mat[k][j-1])/2;
                }
                else if ( (k!=0 && k!=dimx-1) && j==0 ) { //Bord � gauche sans les coins
                    mat_moyenne[k][j] = (mat[k-1][j] + mat[k][j+1] + mat[k+1][j])/3;
                }
                else if ( (k!=0 && k!=dimx-1) && j==dimy-1) { //Bord � droite sans les coins
                    mat_moyenne[k][j] = (mat[k-1][j] + mat[k][j-1] + mat[k+1][j])/3;
                }
                else if ( (j!=0 && j!=dimy-1) && k==0) {//Bord en haut sans les coins
                    mat_moyenne[k][j] = (mat[k][j-1] + mat[k][j+1] + mat[k+1][j])/3;
                }
                else if ( (j!=0 && j!=dimy-1) && k==dimx-1) { //Bord en bas sans les coins
                    mat_moyenne[k][j] = (mat[k][j-1] + mat[k][j+1] + mat[k-1][j])/3;
                }
            }
        }
    }
}

/** Methode de calcul des vitesses U et V
  * @param mat1 l'image initiale
  * @param mat2 l'image finale
  * @param Grad la structure contenant les matrices de gradients pr�tes � �tre remplies
  * @param vitesses la structure contenant les matrices de vitesses pr�tes � �tre remplies
  * @param pas : temps entre la prise des deux images
  */
void U_et_V (double** mat1, double** mat2, Gradient* Grad, Vitesse* vitesses, int pas) {
    int i,j;
    int n = 0;
    double alpha = 0.01;
    int dimX = vitesses->dimX;
    int dimY = vitesses->dimY;
    double** U_moyen = creation_matrice(dimX,dimY);
    double** V_moyen = creation_matrice(dimX,dimY);
    double** denominateur = creation_matrice(dimX,dimY);

    while (n<=10000) {
        if (n==0) { //Etat initial : U_moyen et V_moyen sont �gaux � 1 et alpha = 3 (on le choisit)
            calcul_gradient(mat1,mat2,Grad,pas);
            for (i=0 ; i<dimX ; i++) {
                for (j=0 ; j<dimY ; j++) {
                    denominateur[i][j] = alpha + pow(Grad->grad_x[i][j],2) + pow(Grad->grad_y[i][j],2); //On le pr�calcule � l'�tat initial pour gagner du temps pour les autres it�ration
                    vitesses->U[i][j] = 0 - Grad->grad_x[i][j]*(Grad->grad_x[i][j]*0 + Grad->grad_y[i][j]*0 + Grad->grad_t[i][j])/denominateur[i][j];
                    vitesses->V[i][j] = 0 - Grad->grad_y[i][j]*(Grad->grad_x[i][j]*0 + Grad->grad_y[i][j]*0 + Grad->grad_t[i][j])/denominateur[i][j];
                }
            }
        }
        else {
            moyenne(vitesses->U,U_moyen,dimX,dimY);
            moyenne(vitesses->V,V_moyen,dimX,dimY);
            for (i=0 ; i<dimX ; i++) {
                for (j=0 ; j<dimY ; j++) {
                    vitesses->U[i][j] = U_moyen[i][j] - Grad->grad_x[i][j]*(Grad->grad_x[i][j]*U_moyen[i][j] + Grad->grad_y[i][j]*V_moyen[i][j] + Grad->grad_t[i][j])/denominateur[i][j];
                    vitesses->V[i][j] = V_moyen[i][j] - Grad->grad_y[i][j]*(Grad->grad_x[i][j]*U_moyen[i][j] + Grad->grad_y[i][j]*V_moyen[i][j] + Grad->grad_t[i][j])/denominateur[i][j];
                }
            }
        }
        n++;
    }
}

