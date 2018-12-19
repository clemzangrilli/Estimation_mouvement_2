#ifndef INTERPOLATION_H_INCLUDED
#define INTERPOLATION_H_INCLUDED
#include "Echantillonnage.h"
#include "math.h"

typedef struct {

    //Matrice échantillonnée deux fois
    int dimX_E2;
    int dimY_E2;
    double** mat_E2;

    //Matrice échantillonnée E2 interpolée une fois
    int dimX_E1;
    int dimY_E1;
    double** mat_E1;

    //Matrice échantillonnée E2 interpolée deux fois
    int dimX_init;
    int dimY_init;
    double** mat_init;
}Interpolation;

/** Methode de creation d'une structure Interpolation
  * @param mat_E2 matrice échantillonnée 2 fois que l'on veut interpoler
  * @param echantillon la structure Echantillon
  */
Interpolation creation_remplissage_interpolation (double** mat_E2, Echantillonnage echantillon);


double** interpolation (double** mat_E, int dimX_matE, int dimY_matE, int dimX_matI, int dimY_matI);

/** Methode de remplissage d'une structure Interpolation
  * @param interpol la structure Interpolation à remplir
  */
void remplissage_interpolation (Interpolation* interpol);

/** Methode de creation et remplissage d'une structure Interpolation
  * @param mat_E2 matrice échantillonnée 2 fois que l'on veut interpoler
  * @param dimX_E2 nombre de lignes de l'image échantillonnée 2 fois
  * @param dimY_E2 nombre de colonnes de l'image échantillonnée 2 fois
  * @return une structure Interpolation avec les matrices interpolées complétées, et leurs dimensions
  */
Interpolation creation_remplissage_interpolation (double** mat_E2, Echantillonnage echantillon);

/** Methode de destruction d'une structure Interpolation
  * @param interpol la structure Interpolation à détruire
  */
void destruction_interpolation (Interpolation* interpol);
#endif // INTERPOLATION_H_INCLUDED
