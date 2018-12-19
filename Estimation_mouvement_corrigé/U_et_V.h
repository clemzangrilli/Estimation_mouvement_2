#ifndef U_ET_V_H_INCLUDED
#define U_ET_V_H_INCLUDED
#include "Gradient.h"

typedef struct {
    double** U;
    double** V;
    int dimX;
    int dimY;
}Vitesse;

/** Methode de creation d'une structure Vitesse
  * @param dimX nombre de lignes de l'image dont on calcule la vitesse
  * @param dimY nombre de colonnes de l'image dont on calcule la vitesse
  * @return une structure Vitesse avec les matrices vitesses et vitesses moyennes pr�tes � �tre remplies, et leurs dimensions
  */
Vitesse creation_vitesse (dimX, dimY);

/** Methode de calcul de la moyenne d'une matrice
  * @param mat la matrice dont on veut calculer la moyenne des pixels autour de chaques pixels
  * @param mat_moyenne la matrice qui contiendra la valeur de ces moyennes aux coordonn�es du pixel initial
  * @param dimX le nombre de ligne de la matrice dont on veut calculer la moyenne
  * @param dimY le nombre de colonne de la matrice dont on veut calculer la moyenne
  */
void moyenne (double **mat, double** mat_moyenne, int dimx, int dimy);

/** Methode de calcul des vitesses U et V
  * @param mat1 l'image initiale
  * @param mat2 l'image finale
  * @param Grad la structure contenant les matrices de gradients pr�tes � �tre remplies
  * @param vitesses la structure contenant les matrices de vitesses pr�tes � �tre remplies
  * @param pas : temps entre la prise des deux images
  */
void U_et_V (double** mat1, double** mat2, Gradient* Grad, Vitesse* vitesses, int pas);
#endif // U_ET_V_H_INCLUDED
