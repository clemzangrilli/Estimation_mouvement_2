#ifndef INTERACTION_UTILISATEUR_H_INCLUDED
#define INTERACTION_UTILISATEUR_H_INCLUDED
#include "Echantillonnage.h"
#include "Gradient.h"
#include "Interpolation.h"
#include "myBmpGris.h"
#include "U_et_V.h"


void lancement_interface (char* Image_initiale,char* Image_finale);

void presentation ();

void demande_utilisateur_int (int* rep);

void demande_utilisateur_char (char* chaine);

void interaction_vitesses (char* Image_initiale, char* Image_finale);

void interaction_vitesses_interpolees (char* Image_initiale, char* Image_finale);

void interaction_creation_rectangle ();

double** creation_matrice (int dimx, int dimy);

int char2double_unevaleur (unsigned char val);

int** char2double_matrice (BmpImg image);

void remplissage_fichier_double (char* FileName, int dimX, int dimY, double** mat);

/** Methode de création d'un carré en valeur binaire
* @param nom le nom du fichier txt qui sera créé
* @param taille la taille d'un coté en pixel
* @param pos_x la coordonnée x du pixel du coin supérieur gauche
* @param pos_y la coordonnée y du pixel du coin supérieur gauche
*/
void creation_image_binaire_carree (char* nom, int taille, int pos_x, int pos_y);
#endif // INTERACTION_UTILISATEUR_H_INCLUDED
