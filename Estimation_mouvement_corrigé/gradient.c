#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Projet.h"
#include "myBmpGris.h"
#include "Gradient.h"


//Création de la structure Gradient
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
  * @param matint : matrice d'entier représentant les intensités
  * @param image la structure contenant les dimensions
  */


void gradient_x (int** matint, Gradient* Grad)
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
                Grad->grad_x[i][j]= matint[i][j+1] - matint[i][j];
            }
            else if(j==dimy-1) // Cas limite de la bordure droite
            {
                Grad->grad_x[i][j]= matint[i][j] - matint[i][j-1];
            }
            else
            {
                Grad->grad_x[i][j] = (matint[i][j+1] - matint[i][j-1])/2;
            }

        }
    }
}

// Calcul du gradient de y
/** Methode de calcul du gradient de y
  * @param image la structure contenant les dimensions
  */

void gradient_y(int** matint, Gradient* Grad)
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
                Grad->grad_y[i][j]= (matint[i+1][j] - matint[i][j]);
            }
            else if (i==dimx-1) // Cas limite de la bordure supérieure
            {
                Grad->grad_y[i][j]= (matint[i][j] - matint[i-1][j]);
            }
            else
                {
                Grad->grad_y[i][j]= (matint[i+1][j] - matint[i-1][j])/2;
            }
        }
    }
}

// Calcul du gradient de t
/** Methode de calcul du gradient de t
  * @param matint1 : matrice d'entier représentant les intensités de l'image 1
  * @param matint2 : matrice d'entier représentant les intensités de l'image 2
  * @param image la structure contenant les dimensions
  * @param pas : temps entre la prise des deux images
  */

void gradient_t(int** matint1,int** matint2, Gradient* Grad, int pas) //Les 2 images doivent être de même dimensions
{
    int i,j;
    int dimx = Grad->dimX;
    int dimy = Grad->dimY;

    for(i=0; i<dimx; i++)
    {
        for(j=0; j<dimy; j++)
        {
            Grad->grad_t[i][j] = (matint2[i][j] - matint1[i][j])/pas;
        }
    }
}

void calcul_gradient (int** matint1,int** matint2, Gradient* Grad, int pas) {

    gradient_x (matint1,Grad);
    gradient_y (matint1,Grad);
    gradient_t (matint1,matint2,Grad,pas);
}
