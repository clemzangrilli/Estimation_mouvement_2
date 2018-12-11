#ifndef GRADIENT_H_INCLUDED
#define GRADIENT_H_INCLUDED

typedef struct {
    double** grad_x;
    double** grad_y;
    double** grad_t;
    int dimX;
    int dimY;
}Gradient;

Gradient creation_gradient (int dimX, int dimY);

void gradient_x(int** matint, Gradient* Grad);

void gradient_y(int** matint, Gradient* Grad);

void gradient_t(int** matint1,int** matint2, Gradient* Grad, int pas);

//Calcul les gradient et les rentre dans la structure Gradient (Appelle les 3 fonctions)
void calcul_gradient (int** matint1,int** matint2, Gradient* Grad, int pas);


#endif // GRADIENT_H_INCLUDED
