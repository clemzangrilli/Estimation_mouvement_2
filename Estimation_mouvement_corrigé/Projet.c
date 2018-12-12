#include "Projet.h"
#include <stdlib.h>
#include <stdio.h>

/** Methode de conversion d'un tableau de char vers un entier
  * @param val le tableau de char a convertir
*/

int char2double_unevaleur (unsigned char val) {
    int res = (double)val;
    return res;
    }

/** Methode de création d'une matrice d'entier à partir d'une matrice de tableau de char
  * @param Image la structure contenant la matrice de tableau de char
  */
int** char2double_matrice(BmpImg image) {
    int dimy=image.dimY;
    int dimx=image.dimX;
    int i,k,j;
    double** mat = creation_matrice(dimx,dimy);

    for (k=0 ; k<dimx ; k++)
    {
        for (j=0 ; j<dimy ; j++)
        {
           mat[k][j] = char2double_unevaleur(image.img[k][j]);
        }
    }
    return mat;
}

double** creation_matrice (int dimx, int dimy) {
    double** mat = malloc(dimx*sizeof (double*));
    int i;
    for (i=0 ; i<dimx ; i++) {
        mat[i] = calloc(dimy, sizeof (double));
    }

return mat;
}

void free_matrice (double*** mat, BmpImg image) { //A modifier avec structure
    int i;
    int dimX = image.dimX;
    if( mat != NULL ){
        for( i = 0; i < dimX; i++ )
            free( mat[i] );
        free( mat );
    }
    *mat = NULL;
}
//À voir si c'est sa place
//Permet de visualiser les valeurs des intensités de nos images
/** Methode de remplissage d'un fichier texte à partir des valeurs d'une matrice d'une structure BmpImg
* @param FileName le nom du fichier TXT
* @param image la structure contenant les dimensions de la matrice (la matrice peut ne pas être comprise dans cette structure, mais elle doit être de la même dimension que celle comprise)
*/
void remplissage_fichier_double (char* FileName, int dimX, int dimY, double** mat) {

    int i,j;
    FILE* fichier = fopen (FileName, "w");
    if (fichier == NULL) {
        printf ("Erreur d'ouverture du fichier à écrire");
        return (1);
    }
    for (i=0 ; i<dimX ; i++) {
        for (j=0 ; j<dimY ; j++) {
            fprintf (fichier, "%.1f \t", mat[i][j]);
        }
            fprintf (fichier, "%\n");
    }
    fclose (fichier);
}

void remplissage_fichier_int (char* FileName, int dimX, int dimY, int** mat) {

    int i,j;
    FILE* fichier = fopen (FileName, "w");

    if (fichier == NULL) {
        printf ("Erreur d'ouverture du fichier à écrire");
        return (1);
    }
    for (i=0 ; i<dimX ; i++) {
        for (j=0 ; j<dimY ; j++) {
            fprintf (fichier, "%d\t", mat[i][j]);
        }
            fprintf (fichier, "%\n");
    }
    fclose (fichier);
}
