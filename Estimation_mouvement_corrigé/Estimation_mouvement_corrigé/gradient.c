#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Projet.h"
#include "myBmpGris.h"
#include "Gradient.h"


/** Methode de création de la structure Gradient
  * @param dimX : Nb de lignes des matrices à créer
  * @param dimY : Nb de colonnes des matrices à créer
  */
Gradient creation_gradient (int dimX, int dimY) {
    Gradient Grad;
    Grad.grad_x = creation_matrice(dimX,dimY);
    Grad.grad_y = creation_matrice(dimX,dimY);
    Grad.grad_t = creation_matrice(dimX,dimY);
    Grad.dimX = dimX;
    Grad.dimY = dimY;

    return Grad;
}

// Calcul du gradient de x
/** Methode de calcul du gradient de x
  * @param mat : matrice de double représentant les intensités
  * @param Grad la structure contenant les matrices des gradients et leur dimension
  */


void gradient_x (double** mat, Gradient* Grad)
{
    int i,j;

    int dimx = Grad->dimX;
    int dimy = Grad->dimY;

    for(i=0; i<dimx; i++)
    {
        for(j=0; j<dimy; j++)
        {
            if(j==0) // Cas limite de la bordure gauche
            {
                Grad->grad_x[i][j]= mat[i][j+1] - mat[i][j];
            }
            else if(j==dimy-1) // Cas limite de la bordure droite
            {
                Grad->grad_x[i][j]= mat[i][j] - mat[i][j-1];
            }
            else
            {
                Grad->grad_x[i][j] = (mat[i][j+1] - (double)mat[i][j-1])/2.0;
            }

        }
    }
}

/** Methode de calcul du gradient de y
  * @param mat : matrice de double représentant les intensités
  * @param Grad la structure contenant les matrices des gradients et leur dimension
  */

void gradient_y(double** mat, Gradient* Grad)
{
    int i,j;
    int dimx = Grad->dimX;
    int dimy = Grad->dimY;


    for(i=0; i<dimx; i++)
    {
        for(j=0; j<dimy; j++)
        {
            if (i==0) // Cas limite de la bordure inférieure
            {
                Grad->grad_y[i][j]= (mat[i+1][j] - mat[i][j]);
            }
            else if (i==dimx-1) // Cas limite de la bordure supérieure
            {
                Grad->grad_y[i][j]= (mat[i][j] - mat[i-1][j]);
            }
            else
                {
                Grad->grad_y[i][j]= (mat[i+1][j] - mat[i-1][j])/2;
            }
        }
    }
}

/** Methode de calcul du gradient de t
  * @param mat1 : matrice de double représentant les intensités de l'image 1
  * @param mat2 : matrice de double représentant les intensités de l'image 2
  * @param Grad la structure contenant les matrices des gradients et leur dimension
  * @param pas : temps entre la prise des deux images
  */

void gradient_t(double** mat1,double** mat2, Gradient* Grad, int pas) //Les 2 images doivent être de même dimensions
{
    int i,j;
    int dimx = Grad->dimX;
    int dimy = Grad->dimY;

    for(i=0; i<dimx; i++)
    {
        for(j=0; j<dimy; j++)
        {
            Grad->grad_t[i][j] = (mat2[i][j] - mat1[i][j])/pas;
        }
    }
}

void calcul_gradient (double** mat1,double** mat2, Gradient* Grad, int pas) {

    gradient_x (mat1,Grad);
    gradient_y (mat1,Grad);
    gradient_t (mat1,mat2,Grad,pas);
}
