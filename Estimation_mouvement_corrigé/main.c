#include <stdio.h>
#include <stdlib.h>
#include "myBmpGris.h"
#include "Projet.h"
#include "Gradient.h"
#include "U_et_V.h"

#define PAS 1

int main()
{
    //Permet de lire une image bitmap et remplir la structure (image 24 couleurs)
    BmpImg Image_Initiale = readBmpImage("Rectangle_noir_initial.bmp");
    BmpImg Image_finale = readBmpImage("Rectangle_noir_final.bmp");
    BmpImg Image_binaire_initiale = readBmpImage("Image_binaire_ligne_initiale.bmp");
    BmpImg Image_binaire_finale = readBmpImage("Image_binaire_ligne_finale.bmp");
    //INITIALISATION DES MATRICES
    int** mat1 = char2double_matrice (Image_Initiale);
    int** mat2 = char2double_matrice (Image_finale);
    int** mat3 = char2double_matrice(Image_binaire_initiale);
    int** mat4 = char2double_matrice(Image_binaire_finale);

    //Dimensions des images (même dimensions)
    int dimX = Image_Initiale.dimX;
    int dimY = Image_Initiale.dimY;


    //CREATION DES STRUCTURES
    Gradient Grad = creation_gradient(dimX,dimY);
    Vitesse vitesses = creation_vitesse(dimX,dimY);

    //CALCUL DE U ET V
    U_et_V(mat3,mat4,&Grad,&vitesses,PAS);

    //AFFICHAGE DANS UN FICHIER TEXTE
    remplissage_fichier_double("Rectangle_noir_initial.txt", dimX, dimY,mat1);
    remplissage_fichier_double("Image_Binaire_Initiale.txt",dimX,dimY,mat3);
    remplissage_fichier_double("Image_Binaire_finale.txt",dimX,dimY,mat4);
    remplissage_fichier_double("U.txt",dimX, dimY,vitesses.U); //Ce qui nous interesses
    remplissage_fichier_double("V.txt",dimX, dimY,vitesses.V); //Ce qui nous interesses
    remplissage_fichier_double("grad_x.txt",dimX, dimY,Grad.grad_x);
    remplissage_fichier_double("grad_y.txt",dimX, dimY,Grad.grad_y);
    remplissage_fichier_double("grad_t.txt",dimX, dimY,Grad.grad_t);


    //Création d'une image binaire
    /*BmpImg Creation_image_binaire = readBmpImage("Support_image_binaire.bmp");

    setPixel(Creation_image_binaire, 1, 10, 14);
    setPixel(Creation_image_binaire, 1, 10, 15);
    setPixel(Creation_image_binaire, 1, 10, 16);
    setPixel(Creation_image_binaire, 1, 10, 17);

    writeBmpImage("Image_binaire_ligne_finale.bmp", &Creation_image_binaire );*/


    //LIBERATION DES MATRICES //NE MARCHE PAS (faire à travers une structure)
    //free_matrice(&mat1,Image_Initiale);
    //free_matrice(&mat2,Image_finale);
    //free_matrice(grad_x,Image_Initiale);
    //free_matrice(grad_y,Image_Initiale);

/*
    //Permet de tracer une flèche
    setPixel(Image_Initial, 30, 20, 2);
    setPixel(Image_Initial, 30, 20, 3);
    setPixel(Image_Initial, 30, 20, 4);
    setPixel(Image_Initial, 30, 20, 5);
    setPixel(Image_Initial, 30, 21, 4);
    setPixel(Image_Initial, 30, 19, 4);

    //Permet de créer une nouvelle image à partir d'une image qu'on lui donne
    writeBmpImage("Test_rectangle_initial2.bmp", &Image_Initial );
    */

    return 0;
}

//DIMX --> Nb de lignes
//DIMY --> Nb de colonnes
