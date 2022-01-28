/*  AUTEUR :    SAURAT DORIAN                                                                               */
/*                                                                                                          */
/*  NOM :   comparaison_image.c                                                                             */
/*                                                                                                          */
/*  Fonction :  Contient les headers et structures nécessaires à l'implémentation de comparaisin_image.c    */

#ifndef COMPARAISON_IMAGE_H
#define COMPARAISON_IMAGE_H

#define MAX_COULEURS_3_BITS 511 // C'est le maximum de couleurs qie peut contenir un descripteur lorsque l'indexation est faite sur 3 bits

/* Structure associant à un niveau de couleur de l'histogramme un nombre d'occurrences */
typedef struct s_coul_occ
{
    int color;
    int occur;
} COULEUR_OCCUR;

/* Structure associant à un nom de fichier, le pourcentage de ressemblance et le nombre de couleurs communes */
typedef struct comp_img
{
    float ressemblance;
    int nb_couleurs_communes; 
    char nom_fichier[6];

} COMP_IMG;

/*  Cette fonction a pour but de récupérer un descripteur d'une image dont le passée en paramètre pour remplir un tableau de COULEUR_OCCUR représentant 
    l'histogramme de l'image, associant à un niveau de couleur un nombre d'occurrences */
int file_to_tab(char *, FILE *, COULEUR_OCCUR *, int); 

/*  Cette fonction permet de concaténer le nom d'un fichier passé en paramètres avec le chemin du fichier contenant les images.
    Elle est utilisée lors de l'appel de file_to_tab() pour permettre de récupérer le bon descripteur */
void name_to_path_fichier(char *, char *); 

/*Comparaison permet de raliser l'oppération de comparaison d'un fichier avec les fichiers indexés.*/
int comparaison(COMP_IMG *comparaison, COULEUR_OCCUR *compare, int taille_compare, int nb_bits_quantif); 


#endif