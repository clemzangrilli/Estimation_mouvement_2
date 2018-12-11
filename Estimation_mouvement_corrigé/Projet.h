#ifndef PROJET_H_INCLUDED
#define PROJET_H_INCLUDED
#include "myBmpGris.h"

int char2int_unevaleur (unsigned char val);

int** char2int_matrice(BmpImg image);

void remplissage_fichier_double (char* FileName, int dimX, int dimY, double** mat);

void remplissage_fichier_int (char* FileName, int dimX, int dimY, int** mat);

double** creation_matrice (int dimx, int dimy);

void free_matrice (double*** mat, BmpImg image); //Ne marche pas (encore)


#endif // PROJET_H_INCLUDED
