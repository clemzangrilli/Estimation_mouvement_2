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

/** Methode de cr�ation d'un carr� en valeur binaire
* @param nom le nom du fichier txt qui sera cr��
* @param taille la taille d'un cot� en pixel
* @param pos_x la coordonn�e x du pixel du coin sup�rieur gauche
* @param pos_y la coordonn�e y du pixel du coin sup�rieur gauche
*/
void creation_image_binaire_carree (char* nom, int taille, int pos_x, int pos_y);
#endif // INTERACTION_UTILISATEUR_H_INCLUDED
