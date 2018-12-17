#ifndef INTERPOLATION_H_INCLUDED
#define INTERPOLATION_H_INCLUDED

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
  * @param dimX_E2 nombre de lignes de l'image �chantillonn�e 2 fois
  * @param dimY_E2 nombre de colonnes de l'image �chantillonn�e 2 fois
  * @return une structure Interpolation avec les matrices interpol�es pr�tes � �tre rempli, et leurs dimensions
  */
Interpolation creation_interpolation (double** mat_E2, int dimX_E2, int dimY_E2);

/** Methode de remplissage d'une structure Interpolation
  * @param interpol la structure Interpolation � remplir
  */
void interpolation_mat (Interpolation* interpol);

/** Methode de creation et remplissage d'une structure Interpolation
  * @param mat_E2 matrice �chantillonn�e 2 fois que l'on veut interpoler
  * @param dimX_E2 nombre de lignes de l'image �chantillonn�e 2 fois
  * @param dimY_E2 nombre de colonnes de l'image �chantillonn�e 2 fois
  * @return une structure Interpolation avec les matrices interpol�es compl�t�es, et leurs dimensions
  */
Interpolation creation_remplissage_interpolation (double** mat_E2, int dimX_E2, int dimY_E2);

/** Methode de destruction d'une structure Interpolation
  * @param interpol la structure Interpolation � d�truire
  */
void destruction_interpolation (Interpolation* interpol);
#endif // INTERPOLATION_H_INCLUDED
