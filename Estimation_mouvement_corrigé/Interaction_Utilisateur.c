#include "Interaction_Utilisateur.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //Permet entre autre d'utiliser strcat qui permet de concatener deux chaines de caractères (pour .txt par exemple)


/** Methode d'affichage de la présentation du programme et des premiers choix
  */
void presentation () {
    printf ("****************************ESTIMATION DE MOUVEMENT****************************\n\n");
    printf ("Presentation : Bonjour utilisateur, je suis un programme permettant d'estimer \n"
            "le mouvement a partir de deux images bitmap.\n"
            "Vous pouvez modifier les images dans mes DEFINES\n"
            "Je peux prendre toute image bitmap 24 couleurs, car je gere les effets de bords\n"
            "et la paritee des dimensions !");
    printf ("      Avant de m'utiliser, s'il vous plait veuillez verifier que : \n"
            "        - Les noms des images dans les DEFINE sont corrects\n"
            "        - Le deplacement de l'objet n'est pas trop important\n"
            "        - Les fichiers txt sont tous supprimes pour plus de lisibilite\n\n"
            "(Si vous n'avez pas modifie les images, inutile de faire les verifications)\n\n");
    printf ("Veuillez choisir une option en tapant le chiffre correspondant : \n\n");
    printf ("1 : Calcul des vitesses U et V par la methode de Horn & Schunck\n"
            "2 : Calcul des vitesses U et V optimise avec echantillonnage et interpolation\n"
            "3 : Creation d'un rectangle en image binaire (rectangle de 1 entoure de 0)\n\n"
            "Choix : ");
}

/** Methode de lancement de l'interface utilisateur
  * @param Image_initiale le nom de la première image
  * @param Image_finale le nom de la deuxième image
  */
void lancement_interface(char* Image_initiale,char* Image_finale) {
    presentation();
    int rep = 0;
    int compteur = 0;
    while (compteur<3) {
        demande_utilisateur_int(&rep);
        if (rep ==1 || rep ==2 || rep==3) {
            compteur=3;
            if (rep==1) { //Calcul des vitesses normales
                interaction_vitesses(Image_initiale,Image_finale);
                printf ("\n\n Les fichiers ont ete crees et completes. \n"
                        "Vous pouvez relancer ce programme pour choisir d'autres options !\n\n\n");
            }
            if (rep==2) { //Calcul des vitesses avec echantillonngage et interpolation
                interacion_vitesses_interpolees(Image_initiale,Image_finale);
                printf ("\n\n Les fichiers ont ete crees et completes. \n"
                        "Vous pouvez relancer ce programme pour choisir d'autres options !\n\n\n");
            }
            if (rep==3) { //Création d'un rectangle
                interaction_creation_rectangle();
                printf ("\n\n Creation reussie. Vous pouvez relancer ce programme pour choisir d'autres options !\n\n\n");
            }
        }
        else {
            compteur++;
            printf ("\nVous n'avez pas rentre 1,2 ou 3\n\n"
                    "Il vous reste %d essai(s) : ",3-compteur);
        }
    }
}

/** Methode permettant de demander un entier à l'utilisateur
  * @param rep le pointeur qui pointe vers la réponse donnée par l'utilisateur
  */
void demande_utilisateur_int (int* rep) {
    if (scanf ("%d",rep) == NULL) {
        printf ("Erreur lors de la saisie\n");
        exit (1);
    }
}

/** Methode permettant de demander une chaine de caractère à l'utilisateur
  * @param chaine le pointeur qui pointe vers la réponse donnée par l'utilisateur
  */
void demande_utilisateur_char(char* chaine) {
    if (scanf ("%s",chaine) == NULL) {
        printf ("Erreur lors de la saisie\n");
        exit(1);
    }
}

/** Methode permettant de calculer les vitesses et donner des choix à l'utilisateur
  * @param Image_initiale le nom de la première image
  * @param Image_finale le nom de la deuxième image
  */
void interaction_vitesses(char* Image_initiale,char* Image_finale) {
    //Permet de lire une image bitmap et remplir la structure (image 24 couleurs)
    BmpImg Image_init = readBmpImage(Image_initiale);
    BmpImg Image_fin = readBmpImage(Image_finale);
    //INITIALISATION DES MATRICES
    double** mat1 = char2double_matrice(Image_init);
    double** mat2 = char2double_matrice(Image_fin);

    //Dimensions des images (même dimensions)
    int dimX = Image_init.dimX;
    int dimY = Image_fin.dimY;

    //CREATION DES STRUCTURES SANS ECHANTILLONNEE
    Gradient Grad = creation_gradient(dimX,dimY);
    Vitesse vitesses = creation_vitesse(dimX,dimY);

    //CALCUL DE U ET V
    printf ("\n Je procede au calcul de U et V, quelques instants svp ...");
    U_et_V(mat1,mat2,&Grad,&vitesses,1);

    //REMPLISSAGE DES FICHIERS TEXT
    int rep = 0;
    printf ("\n\n*********************** Les vitesses ont ete calculees ! ***********************\n\n"
            "Choisissez les fichiers txt qui vous conviennent : \n"
            "1: U.txt et V.txt les fichiers vitesses (a rentrer dans matlab)\n"
            "2: Fichiers precedents + Image_initiale.txt et Image_finale.txt\n"
            "3: Fichiers precedents + grad_x et grad_y et grad_t\n\n"
            "Choix : ");
            demande_utilisateur_int(&rep);
            if (rep==1) {
                remplissage_fichier_double("U.txt",vitesses.dimX,vitesses.dimY,vitesses.U);
                remplissage_fichier_double("V.txt",vitesses.dimX,vitesses.dimY,vitesses.V);
            }
            else if (rep==2) {
                remplissage_fichier_double("U.txt",vitesses.dimX,vitesses.dimY,vitesses.U);
                remplissage_fichier_double("V.txt",vitesses.dimX,vitesses.dimY,vitesses.V);
                remplissage_fichier_double("Image_initiale.txt",dimX,dimY,mat1);
                remplissage_fichier_double("Image_finale.txt",dimX,dimY,mat2);
            }
            else if (rep==3) {
                remplissage_fichier_double("U.txt",vitesses.dimX,vitesses.dimY,vitesses.U);
                remplissage_fichier_double("V.txt",vitesses.dimX,vitesses.dimY,vitesses.V);
                remplissage_fichier_double("Image_initiale.txt",dimX,dimY,mat1);
                remplissage_fichier_double("Image_finale.txt",dimX,dimY,mat2);
                remplissage_fichier_double("Grad_x.txt",dimX,dimY,Grad.grad_x);
                remplissage_fichier_double("Grad_y.txt",dimX,dimY,Grad.grad_y);
                remplissage_fichier_double("Grad_t.txt",dimX,dimY,Grad.grad_t);

            }
            else {
                printf ("\n\nVotre choix n'est pas 1,2 ou 3 ... Extinction du programme");
                return (1);
            }
}

/** Methode permettant de calculer les vitesses par échantillonnage et interpolation, et donner des choix à l'utilisateur
  * @param Image_initiale le nom de la première image
  * @param Image_finale le nom de la deuxième image
  */
void interacion_vitesses_interpolees(char* Image_initiale, char* Image_finale) {
    //Permet de lire une image bitmap et remplir la structure (image 24 couleurs)
    BmpImg Image_init = readBmpImage(Image_initiale);
    BmpImg Image_fin = readBmpImage(Image_finale);
    //INITIALISATION DES MATRICES
    double** mat1 = char2double_matrice(Image_init);
    double** mat2 = char2double_matrice(Image_fin);
    //ECHANTILLONNAGE
    Echantillonnage echantillon_i_init = creation_remplissage_echantillon(mat1,Image_init.dimX,Image_init.dimY);
    Echantillonnage echantillon_i_fin = creation_remplissage_echantillon(mat2,Image_fin.dimX,Image_fin.dimY);

    //DIMENSION DES IMAGES ÉCHANTILLONNÉES
    int dimX_E2 = echantillon_i_init.dimX_E2;
    int dimY_E2 = echantillon_i_init.dimY_E2;

    //CREATION DES STRUCTURES POUR ECHANTILLONNEE (échantillonnée initiale et finale de même dimensions)
    Gradient Grad_E = creation_gradient(dimX_E2,dimY_E2);
    Vitesse vitesses_E = creation_vitesse(dimX_E2,dimY_E2);

    //Calcul vitesse échantillonnée
    U_et_V(echantillon_i_init.mat_E2,echantillon_i_fin.mat_E2,&Grad_E,&vitesses_E,1);

    //Interpolation
    Interpolation U_I = creation_remplissage_interpolation(vitesses_E.U,echantillon_i_init);
    Interpolation V_I = creation_remplissage_interpolation(vitesses_E.V,echantillon_i_init);

    //REMPLISSAGE DES FICHIERS TEXT
    int rep = 0;
    printf ("\n\n*********************** Les vitesses ont ete calculees ! ***********************\n\n"
            "Choisissez les fichiers txt qui vous conviennent : \n"
            "1: U_I.txt et V_I.txt les fichiers vitesses obtenue par interpolation\n"
            "2: Fichiers precedents + Image_initiale.txt et Image_finale.txt\n\n"
            "Choix : ");
    demande_utilisateur_int(&rep);
    if (rep==1) {
        remplissage_fichier_double("U_I.txt",U_I.dimX_init,U_I.dimY_init,U_I.mat_init);
        remplissage_fichier_double("V_I.txt",V_I.dimX_init,V_I.dimY_init,V_I.mat_init);
    }
    else if (rep==2) {
        remplissage_fichier_double("U_I.txt",U_I.dimX_init,U_I.dimY_init,U_I.mat_init);
        remplissage_fichier_double("V_I.txt",V_I.dimX_init,V_I.dimY_init,V_I.mat_init);
        remplissage_fichier_double("Image_initiale_E.txt",Image_init.dimX,Image_init.dimY,mat1);
        remplissage_fichier_double("Image_finale_E.txt",Image_init.dimX,Image_init.dimY,mat2);
    }
    else {
        printf ("\n\nVotre choix n'est pas 1,2 ou 3 ... Extinction du programme");
        return (1);
    }
}

/** Methode permettant de créer une image bitmap binaire avec un rectangle de 1 dont la longueur,la largeur,la position sont demandées à l'utilisateur
  */
void interaction_creation_rectangle() {
    char nom_image [50];
    int largeur;
    int longueur;
    int pos_x;
    int pos_y;
    int rep = 0;
    printf ("Vous voulez creer un rectangle binaire bitmap\n\n"
            "La taille de l'image est 63x101, veuillez rentrer :\n"
            "La longueur du rectangle en nombre de pixels : "); demande_utilisateur_int(&largeur);
    printf("\nLa largeur du rectangle en nombre de pixels : "); demande_utilisateur_int(&longueur);
    printf("\nLa position x du coin supérieur gauche : "); demande_utilisateur_int(&pos_x);
    printf("\nLa position y du coin supérieur gauche : "); demande_utilisateur_int(&pos_y);
    printf("\nLe nom de l'image (SANS le .bmp) : "); demande_utilisateur_char(nom_image);

    creation_rectangle_binaire (nom_image, largeur, longueur, pos_x, pos_y);
    printf ("\n\n Voulez-vous le fichier txt associe ? \n"
            "1 : Oui\n"
            "2 : Non\n\n"
            "Reponse : ");
    demande_utilisateur_int(&rep);
    if (rep==1) {
        BmpImg rectangle = readBmpImage(nom_image);
        double** mat_rectangle = char2double_matrice(rectangle);

        printf ("\nChoisissez le nom du fichier txt (SANS .txt) : ");
        char nom_fichier_txt [50];
        demande_utilisateur_char(nom_fichier_txt);
        strcat(nom_fichier_txt,".txt");
        remplissage_fichier_double(nom_fichier_txt,rectangle.dimX,rectangle.dimY,mat_rectangle);
    }
    else if (rep==2) {
        printf ("\n C'est compris, vous pouvez relancer le programme pour choisir d'autres options");
        exit (1);
    }
    else {
        printf ("Vous n'avez pas rentre 1 ou 2 ... Extinction du programme");
        exit(1);
    }
}

/** Methode de conversion d'un tableau de char vers un entier
  * @param val le tableau de char a convertir
  * @return un entier correspondant à la valeur lu en unsigned char
  */
int char2double_unevaleur (unsigned char val) {
    int res = (double)val;
    return res;
    }

/** Methode de création d'une matrice d'entier à partir d'une matrice de tableau de char
  * @param Image la structure contenant la matrice de tableau de char
  * @return une matrice d'entier correspondant aux valeurx de l'image
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

/** Methode permettant de créer une matrice de double de dimension dimx x dimy
  * @param dimx le nombre de lignes
  * @param dimY le nombre de colonnes
  * @return une matrice de double prête à l'emploi
  */
double** creation_matrice (int dimx, int dimy) {
    double** mat = malloc(dimx*sizeof (double*));
    int i;
    for (i=0 ; i<dimx ; i++) {
        mat[i] = calloc(dimy, sizeof (double));
    }

return mat;
}

/** Methode de création d'un fichier txt contenant les valeurs de mat
  * @param FileName le nom du fichier txt qui sera créé
  * @param dimx le nombre de lignes
  * @param dimY le nombre de colonnes
  * @param mat la matrice dont les valeurs remplissent le fichier txt
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
            fprintf (fichier, "%.2f \t", mat[i][j]);
        }
            fprintf (fichier, "%\n");
    }
    fclose (fichier);
}

/** Methode de création d'une image binaire (rectangle de 1 entouré de 0)
* @param nom le nom du fichier bitmap qui sera créé
* @param largeur la largeur du rectangle
* @param longueur la longueur du rectangle
* @param pos_x la coordonnée x du pixel du coin supérieur gauche
* @param pos_y la coordonnée y du pixel du coin supérieur gauche
*/
void creation_rectangle_binaire (char* nom, int largeur, int longueur, int pos_x, int pos_y) {
    BmpImg Creation_image_binaire = readBmpImage("Support_image_binaire.bmp");
    int i,j;
    int dimX = Creation_image_binaire.dimX;
    int dimY = Creation_image_binaire.dimY;

    if ((pos_x+longueur) >= dimX || (pos_y+largeur) >= dimY) {
        printf ("Votre carré sortirait de l'image support (101x63)\n");
        exit(1);
    }

    for (i=pos_x ; i<pos_x+longueur ; i++) {
        for (j=pos_y ; j<pos_y+largeur ; j++) {
            setPixel(Creation_image_binaire, 1, i, j);
        }
    }
    strcat(nom,".bmp");
    writeBmpImage(nom, &Creation_image_binaire);
}
