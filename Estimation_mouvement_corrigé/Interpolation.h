#ifndef INTERPOLATION_H_INCLUDED
#define INTERPOLATION_H_INCLUDED
#include "Echantillonnage.h"
#include "math.h"

typedef struct {

    //Matrice �chantillonn�e deux fois
    int dimX_E2;
    int dimY_E2;
    double** mat_E2;

    //Matrice �chantillonn�e E2 interpol�e une fois
    int dimX_E1;
    int dimY_E1;
    double** mat_E1;

    //Matrice �chantillonn�e E2 interpol�e deux fois
    int dimX_init;
    int dimY_init;
    double** mat_init;
}Interpolation;

/** Methode de creation d'une structure Interpolation
  * @param mat_E2 matrice �chantillonn�e 2 fois que l'on veut interpoler
  * @param echantillon la structure Echantillon
  * @return une structure Interpolation compl�t�e
  */
Interpolation creation_remplissage_interpolation (double** mat_E2, Echantillonnage echantillon);

/** Methode de creation d'une matrice interpol�e une fois � partir d'une matrice (�chantillonn�e)
  * @param mat_E matrice �chantillonn�e que l'on veut interpoler
  * @param dimX_matE le nombre de ligne de la matrice �chantillonn�e
  * @param dimY_matE le nombre de colonne de la matrice �chantillonn�e
  * @param dimX_matI le nombre de ligne de la matrice interpol�e
  * @param dimY_matI le nombre de colonnes de la matrice interpol�e
  * @return une matrice obtenue par interpolation
  */
double** interpolation (double** mat_E, int dimX_matE, int dimY_matE, int dimX_matI, int dimY_matI);

/** Methode de remplissage d'une structure Interpolation
  * @param interpol la structure Interpolation � remplir
  */
void remplissage_interpolation (Interpolation* interpol);

/** Methode de creation et remplissage d'une structure Interpolation
  * @param mat_E2 matrice �chantillonn�e 2 fois que l'on veut interpoler
  * @param echantillon la structure Echantillonnage
  * @return une structure Interpolation avec les matrices interpol�es compl�t�es, et leurs dimensions
  */
Interpolation creation_remplissage_interpolation (double** mat_E2, Echantillonnage echantillon);

/** Methode de destruction d'une structure Interpolation
  * @param interpol la structure Interpolation � d�truire
  */
void destruction_interpolation (Interpolation* interpol);
#endif // INTERPOLATION_H_INCLUDED
