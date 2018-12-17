#include <stdio.h>
#include <stdlib.h>
#include "myBmpGris.h"
#include "Projet.h"
#include "Gradient.h"
#include "U_et_V.h"
#include "Echantillonnage.h"
#include "Interpolation.h"

#define PAS 1

int main()
{
    //Permet de lire une image bitmap et remplir la structure (image 24 couleurs)
    BmpImg Image_binaire_initiale = readBmpImage("Image_binaire_carre_Initial.bmp");
    BmpImg Image_binaire_finale = readBmpImage("Image_binaire_carre_Final.bmp");
    //INITIALISATION DES MATRICES
    int** mat1 = char2double_matrice(Image_binaire_initiale);
    int** mat2 = char2double_matrice(Image_binaire_finale);

                /*******POUR UNE IMAGE ENTIERE*******/

    //Dimensions des images (même dimensions)
    int dimX = Image_binaire_initiale.dimX;
    int dimY = Image_binaire_finale.dimY;

    //CREATION DES STRUCTURES SANS ECHANTILLONNEE
    Gradient Grad = creation_gradient(dimX,dimY);
    Vitesse vitesses = creation_vitesse(dimX,dimY);

    //CALCUL DE U ET V
    U_et_V(mat1,mat2,&Grad,&vitesses,PAS);

    //REMPLISSAGE DES FICHIERS TEXT
    remplissage_fichier_double("Image_initiale.txt",dimX,dimY,mat1);
    remplissage_fichier_double("Image_finale.txt",dimX,dimY,mat2);
    remplissage_fichier_double("U.txt",dimX,dimY,vitesses.U);
    remplissage_fichier_double("V.txt",dimX,dimY,vitesses.V);

            /*******POUR UNE IMAGE ÉCHANTILLONNÉE*******/

    //ECHANTILLONNAGE
    Echantillonnage echantillon_i_init = creation_remplissage_echantillon(mat1,dimX,dimY);
    Echantillonnage echantillon_i_fin = creation_remplissage_echantillon(mat2,dimX,dimY);
    //Echantillonnage E_test = creation_remplissage_echantillon(mat3,Image_binaire_initiale.dimX,Image_binaire_initiale.dimY);

    //DIMENSION DES IMAGES ÉCHANTILLONNÉES
    int dimX_E2 = echantillon_i_init.dimX_E2; //Même dimension que l'image finale
    int dimY_E2 = echantillon_i_init.dimY_E2;

    //CREATION DES STRUCTURES POUR ECHANTILLONNEE (échantillonnée initiale et finale de même dimensions)
    Gradient Grad_E = creation_gradient(dimX_E2,dimY_E2);
    Vitesse vitesses_E = creation_vitesse(dimX_E2,dimY_E2);

    //Calcul vitesse échantillonnée
    U_et_V(echantillon_i_init.mat_E2,echantillon_i_fin.mat_E2,&Grad_E,&vitesses_E,PAS);

    //Interpolation
    Interpolation interpol = creation_remplissage_interpolation(vitesses_E.U,echantillon_i_init.dimX_E2,echantillon_i_init.dimY_E2);

    //REMPLISSAGE DES FICHIERS TXT
    remplissage_fichier_double("Image_initiale_echantillonnee.txt",dimX_E2,dimY_E2,echantillon_i_init.mat_E2);
    remplissage_fichier_double("Image_finale_echantillonnee.txt",dimX_E2,dimY_E2,echantillon_i_fin.mat_E2);
    remplissage_fichier_double("U_échantillonnee.txt",dimX_E2,dimY_E2,vitesses_E.U);

    remplissage_fichier_double("grad_x_echantillonnee.txt",dimX_E2,dimY_E2,Grad_E.grad_x);
    remplissage_fichier_double("grad_y_echantillonnee.txt",dimX_E2, dimY_E2,Grad_E.grad_y);
    remplissage_fichier_double("grad_t_echantillonnee.txt",dimX_E2, dimY_E2,Grad_E.grad_t);

    remplissage_fichier_double("U_interpolee.txt",interpol.dimX_init,interpol.dimY_init,interpol.mat_init);

    //LIBERATION DES MATRICES //NE MARCHE PAS (faire à travers une structure)
    //free_matrice(&mat1,Image_Initiale);
    //free_matrice(&mat2,Image_finale);
    //free_matrice(grad_x,Image_Initiale);
    //free_matrice(grad_y,Image_Initiale);


    //Création d'une image binaire
   /* BmpImg Creation_image_binaire = readBmpImage("Support_image_binaire.bmp");

    setPixel(Creation_image_binaire, 1, 8, 15);
    setPixel(Creation_image_binaire, 1, 8, 16);
    setPixel(Creation_image_binaire, 1, 8, 17);
    setPixel(Creation_image_binaire, 1, 9, 15);
    setPixel(Creation_image_binaire, 1, 9, 16);
    setPixel(Creation_image_binaire, 1, 9, 17);
    setPixel(Creation_image_binaire, 1, 10, 15);
    setPixel(Creation_image_binaire, 1, 10, 16);
    setPixel(Creation_image_binaire, 1, 10, 17);

    writeBmpImage("Image_binaire_carre_Finale.bmp", &Creation_image_binaire );*/

    return 0;
}
