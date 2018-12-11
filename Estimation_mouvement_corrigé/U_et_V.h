#ifndef U_ET_V_H_INCLUDED
#define U_ET_V_H_INCLUDED
#include "Projet.h"
#include "Gradient.h"

typedef struct {
    double** U;
    double** V;
    double** U_moyen;
    double** V_moyen;
}Vitesse;

//Créé la structure Vitesse
Vitesse creation_vitesse (dimX, dimY);

//Calcule la moyenne de mat et la rentre dans mat_moyenne
void moyenne (double **mat, double** mat_moyenne, int dimx, int dimy);

//Calcule U et V et les rentre dans la structure vitesse
void U_et_V (int** mat1, int** mat2, Gradient* Grad, Vitesse* vitesses, int pas);
#endif // U_ET_V_H_INCLUDED
