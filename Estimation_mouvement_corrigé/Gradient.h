#ifndef GRADIENT_H_INCLUDED
#define GRADIENT_H_INCLUDED

typedef struct {
    double** grad_x;
    double** grad_y;
    double** grad_t;
    int dimX;
    int dimY;
}Gradient;

/** Methode de création de la structure Gradient
  * @param dimX : Nb de lignes des matrices à créer
  * @param dimY : Nb de colonnes des matrices à créer
  */
Gradient creation_gradient (int dimX, int dimY);

/** Methode de calcul du gradient de x
  * @param mat1 : matrice de double représentant les intensités de l'image initiale
  * @param mat1 : matrice de double représentant les intensités de l'image finale
  * @param Grad la structure contenant les matrices des gradients et leur dimension
  */
void gradient_x(double** mat, double** mat1, Gradient* Grad);

/** Methode de calcul du gradient de y
  * @param mat1 : matrice de double représentant les intensités de l'image initiale
  * @param mat1 : matrice de double représentant les intensités de l'image finale
  * @param Grad la structure contenant les matrices des gradients et leur dimension
  */
void gradient_y(double** mat, double** mat2, Gradient* Grad);

/** Methode de calcul du gradient de t
  * @param mat1 : matrice de double représentant les intensités de l'image 1
  * @param mat2 : matrice de double représentant les intensités de l'image 2
  * @param Grad la structure contenant les matrices des gradients et leur dimension
  * @param pas : temps entre la prise des deux images
  */
void gradient_t(double** mat1,double** mat2, Gradient* Grad, int pas);

/** Methode de calcul des trois gradients
  * @param mat1 : matrice de double représentant les intensités de l'image initiale
  * @param mat1 : matrice de double représentant les intensités de l'image finale
  * @param Grad la structure contenant les matrices des gradients et leur dimension
  * @param pas : temps entre la prise des deux images
  */
void calcul_gradient (double** mat1,double** mat2, Gradient* Grad, int pas);


#endif // GRADIENT_H_INCLUDED
