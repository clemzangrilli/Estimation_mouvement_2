#ifndef INTERACTION_UTILISATEUR_H_INCLUDED
#define INTERACTION_UTILISATEUR_H_INCLUDED
#include "Echantillonnage.h"
#include "Gradient.h"
#include "Interpolation.h"
#include "myBmpGris.h"
#include "U_et_V.h"

/** Methode de lancement de l'interface utilisateur
  * @param Image_initiale le nom de la premi�re image
  * @param Image_finale le nom de la deuxi�me image
  */
void lancement_interface (char* Image_initiale,char* Image_finale);

/** Methode d'affichage de la pr�sentation du programme et des premiers choix
  */
void presentation ();

/** Methode permettant de demander un entier � l'utilisateur
  * @param rep le pointeur qui pointe vers la r�ponse donn�e par l'utilisateur
  */
void demande_utilisateur_int (int* rep);

/** Methode permettant de demander une chaine de caract�re � l'utilisateur
  * @param chaine le pointeur qui pointe vers la r�ponse donn�e par l'utilisateur
  */
void demande_utilisateur_char (char* chaine);

/** Methode permettant de calculer les vitesses et donner des choix � l'utilisateur
  * @param Image_initiale le nom de la premi�re image
  * @param Image_finale le nom de la deuxi�me image
  */
void interaction_vitesses (char* Image_initiale, char* Image_finale);

/** Methode permettant de calculer les vitesses par �chantillonnage et interpolation, et donner des choix � l'utilisateur
  * @param Image_initiale le nom de la premi�re image
  * @param Image_finale le nom de la deuxi�me image
  */
void interaction_vitesses_interpolees (char* Image_initiale, char* Image_finale);

/** Methode permettant de cr�er une image bitmap binaire avec un rectangle de 1 dont la longueur,la largeur,la position sont demand�es � l'utilisateur
  */
void interaction_creation_rectangle ();

/** Methode permettant de cr�er une matrice de double de dimension dimx x dimy
  * @param dimx le nombre de lignes
  * @param dimY le nombre de colonnes
  * @return une matrice de double pr�te � l'emploi
  */
double** creation_matrice (int dimx, int dimy);

/** Methode de conversion d'un tableau de char vers un entier
  * @param val le tableau de char a convertir
  * @return un entier correspondant � la valeur lu en unsigned char
  */
int char2double_unevaleur (unsigned char val);

/** Methode de cr�ation d'une matrice d'entier � partir d'une matrice de tableau de char
  * @param Image la structure contenant la matrice de tableau de char
  * @return une matrice d'entier correspondant aux valeurx de l'image
  */
int** char2double_matrice (BmpImg image);

/** Methode de cr�ation d'un fichier txt contenant les valeurs de mat
  * @param FileName le nom du fichier txt qui sera cr��
  * @param dimx le nombre de lignes
  * @param dimY le nombre de colonnes
  * @param mat la matrice dont les valeurs remplissent le fichier txt
  */
void remplissage_fichier_double (char* FileName, int dimX, int dimY, double** mat);

/** Methode de cr�ation d'une image binaire (rectangle de 1 entour� de 0)
* @param nom le nom du fichier bitmap qui sera cr��
* @param largeur la largeur du rectangle
* @param longueur la longueur du rectangle
* @param pos_x la coordonn�e x du pixel du coin sup�rieur gauche
* @param pos_y la coordonn�e y du pixel du coin sup�rieur gauche
*/
void creation_rectangle_binaire (char* nom, int largeur, int longueur, int pos_x, int pos_y);

#endif // INTERACTION_UTILISATEUR_H_INCLUDED
