#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

/** Methode de calcul du gradient de x
  * @param mat1 : matrice de double représentant les intensités de l'image initiale
  * @param mat2 : matrice de double représentant les intensités de l'image finale
  * @param Grad la structure contenant les matrices des gradients et leur dimension
  */
void gradient_x (double** mat1, double** mat2, Gradient* Grad)
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
                Grad->grad_x[i][j]= ( ( mat1[i][j+1] - mat1[i][j] ) + ( mat2[i][j+1] - mat2[i][j] ) )/2.0;
            }
            else if(j==dimy-1) // Cas limite de la bordure droite
            {
                Grad->grad_x[i][j]= ( ( mat1[i][j] - mat1[i][j-1] ) + ( mat2[i][j] - mat2[i][j-1] ) )/2.0;
            }
            else
            {
                Grad->grad_x[i][j] = ( ( (mat1[i][j+1] - (double)mat1[i][j-1])/2.0) + ((mat2[i][j+1] - (double)mat2[i][j-1])/2.0) / 2.0);
            }

        }
    }
}

/** Methode de calcul du gradient de y
  * @param mat1 : matrice de double représentant les intensités de l'image initiale
  * @param mat1 : matrice de double représentant les intensités de l'image finale
  * @param Grad la structure contenant les matrices des gradients et leur dimension
  */
void gradient_y(double** mat1, double** mat2, Gradient* Grad)
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
                Grad->grad_y[i][j]= ( (mat1[i+1][j] - mat1[i][j]) + (mat2[i+1][j] - mat2[i][j]) )/2.0;
            }
            else if (i==dimx-1) // Cas limite de la bordure supérieure
            {
                Grad->grad_y[i][j]= ( (mat1[i][j] - mat1[i-1][j]) + (mat2[i][j] - mat2[i-1][j]) )/2.0;
            }
            else
                {
                Grad->grad_y[i][j]= ( ( (mat1[i+1][j] - mat1[i-1][j])/2 ) + ( (mat2[i+1][j] - mat2[i-1][j])/2 ) )/2.0;
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

/** Methode de calcul des trois gradients
  * @param mat1 : matrice de double représentant les intensités de l'image initiale
  * @param mat1 : matrice de double représentant les intensités de l'image finale
  * @param Grad la structure contenant les matrices des gradients et leur dimension
  * @param pas : temps entre la prise des deux images
  */
void calcul_gradient (double** mat1,double** mat2, Gradient* Grad, int pas) {

    gradient_x (mat1,mat2,Grad);
    gradient_y (mat1,mat2,Grad);
    gradient_t (mat1,mat2,Grad,pas);
}
