#ifndef ECHANTILLONNAGE_H_INCLUDED
#define ECHANTILLONNAGE_H_INCLUDED

//Structure contenant la matrice initiale et ses matrices �chnatillonn�es
typedef struct {

    //Image initiale
    int dimX_Initiale;
    int dimY_Initiale;
    double** mat_Initiale;

    //Image �chantillonn�e une fois
    int dimX_E1;
    int dimY_E1;
    double** mat_E1;

    //Image �chantillonn�e deux fois
    int dimX_E2;
    int dimY_E2;
    double** mat_E2;
}Echantillonnage;

/** Methode de creation d'une structure Echantillonnage
  * @param mat_initiale matrice � �chantillonner
  * @param dimX_Initiale nombre de lignes de l'image
  * @param dimY_Initiale nombre de colonnes de l'image
  * @return une structure echantillonnage avec les matrices echantillonnees pr�tes � �tre rempli, et leurs dimensions
  */
Echantillonnage creation_Echantillonnage (double** mat_initiale, int dimX_Initiale, int dimY_Initiale);

/** Methode de remplissage d'une structure Echantillonnage
  * @param mat_initiale matrice � �chantillonner
  */
void echantillonage (Echantillonnage* echantillon);

/** Methode de creation et remplissage d'une structure Echantillonnage
  * @param mat_initiale matrice � �chantillonner
  * @param dimX_Initiale nombre de lignes de l'image
  * @param dimY_Initiale nombre de colonnes de l'image
  * @return une structure echantillonnage avec les matrices echantillonnees compl�t�es, et leurs dimensions
  */
Echantillonnage creation_remplissage_echantillon (double** mat_Initiale, int dimX_Initiale, int dimY_Initiale);

#endif // ECHANTILLONNAGE_H_INCLUDED
