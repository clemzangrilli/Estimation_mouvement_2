#ifndef ECHANTILLONNAGE_H_INCLUDED
#define ECHANTILLONNAGE_H_INCLUDED

//Structure contenant la matrice initiale et ses matrices échnatillonnées
typedef struct {

    int dimX_Initiale;
    int dimY_Initiale;
    double** mat_Initiale;

    int dimX_Echantillon_1;
    int dimY_Echantillon_1;
    double** mat_Echantillon_1;

    int dimX_Echantillon_2;
    int dimY_Echantillon_2;
    double** mat_Echantillon_2;
}Echantillonnage;

Echantillonnage creation_Echantillonnage (double** mat_initiale, int dimX_Initiale, int dimY_Initiale);

void echantillonage (Echantillonnage* echantillon);

Echantillonnage creation_remplissage_echantillon (double** mat_Initiale, int dimX_Initiale, int dimY_Initiale);

#endif // ECHANTILLONNAGE_H_INCLUDED
