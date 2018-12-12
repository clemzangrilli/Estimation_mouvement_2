#include "U_et_V.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Vitesse creation_vitesse (dimX, dimY) {
    Vitesse vitesses;
    vitesses.U = creation_matrice(dimX,dimY);
    vitesses.V = creation_matrice(dimX,dimY);
    vitesses.U_moyen = creation_matrice(dimX,dimY);
    vitesses.V_moyen = creation_matrice(dimX,dimY);

    return vitesses;
}

void moyenne (double **mat, double **mat_moyenne, int dimx, int dimy) { //Rentre le résultat de la moyenne dans une matrice "moyenne" qu'on lui donne (plus malin que de créer une matrice à chaque appel)
    int k = 0;
    int j;

    for (k=0 ; k<dimx ; k++) {
        for (j=0 ; j<dimy ; j++) {

            if (k!=0 && j!=0 && k!=dimx-1 && j!=dimy-1) { //Image sans les bords
                mat_moyenne[k][j] = (mat[k-1][j] + mat[k][j+1] + mat[k+1][j] + mat[k][j-1])/4;
            }
            else { //On est sur les bords
                if ( k==0 && j==0 ) { //Coins en haut à gauche
                    mat_moyenne[k][j] = (mat[k+1][j] + mat[k][j+1])/2;
                }
                else if ( k==dimx-1 && j==0 ) { //Coin en bas à gauche
                    mat_moyenne[k][j] = (mat[k-1][j] + mat[k][j+1])/2;
                }
                else if ( k==0 && j==dimy-1 ) { //Coin en haut à droite
                    mat_moyenne[k][j] = (mat[k+1][j] + mat[k][j-1])/2;
                }
                else if ( k==dimx-1 && j==dimy-1 ) {//Coin en bas à droite
                    mat_moyenne[k][j] = (mat[k-1][j] + mat[k][j-1])/2;
                }
                else if ( (k!=0 && k!=dimx-1) && j==0 ) { //Bord à gauche sans les coins
                    mat_moyenne[k][j] = (mat[k-1][j] + mat[k][j+1] + mat[k+1][j])/3;
                }
                else if ( (k!=0 && k!=dimx-1) && j==dimy-1) { //Bord à droite sans les coins
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

void U_et_V (double** mat1, double** mat2, Gradient* Grad, Vitesse* vitesses, int pas) {
    int i,j;
    int n = 0;
    int alpha = 1;
    int dimX = Grad->dimX;
    int dimY = Grad->dimY;
    while (n<=1000) {
        if (n==0) { //Etat initial : U_moyen et V_moyen sont égaux à 1 et alpha = 3 (on le choisit)
            calcul_gradient(mat1,mat2,Grad,pas);
            for (i=0 ; i<dimX ; i++) {
                for (j=0 ; j<dimY ; j++) {
                    vitesses->U[i][j] = 1 - Grad->grad_x[i][j]*(Grad->grad_x[i][j]*1 + Grad->grad_y[i][j]*1 + Grad->grad_t[i][j])/(alpha + pow(Grad->grad_x[i][j],2) + pow(Grad->grad_y[i][j],2));
                    vitesses->V[i][j] = 1 - Grad->grad_y[i][j]*(Grad->grad_x[i][j]*1 + Grad->grad_y[i][j]*1 + Grad->grad_t[i][j])/(alpha + pow(Grad->grad_x[i][j],2) + pow(Grad->grad_y[i][j],2));
                }
            }
        }
        else {
            moyenne(vitesses->U,vitesses->U_moyen,dimX,dimY);
            moyenne(vitesses->V,vitesses->V_moyen,dimX,dimY);
            for (i=0 ; i<dimX ; i++) {
                for (j=0 ; j<dimY ; j++) {
                    vitesses->U[i][j] = vitesses->U_moyen[i][j] - Grad->grad_x[i][j]*(Grad->grad_x[i][j]*vitesses->U_moyen[i][j] + Grad->grad_y[i][j]*vitesses->V_moyen[i][j] + Grad->grad_t[i][j])/(alpha + pow(Grad->grad_x[i][j],2) + pow(Grad->grad_y[i][j],2));
                    vitesses->V[i][j] = vitesses->V_moyen[i][j] - Grad->grad_y[i][j]*(Grad->grad_x[i][j]*vitesses->U_moyen[i][j] + Grad->grad_y[i][j]*vitesses->V_moyen[i][j] + Grad->grad_t[i][j])/(alpha + pow(Grad->grad_x[i][j],2) + pow(Grad->grad_y[i][j],2));
                }
            }
        }
        n++;
    }
}

