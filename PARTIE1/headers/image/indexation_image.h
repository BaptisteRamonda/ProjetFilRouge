#ifndef INDEXATION_IMAGE_H
#define INDEXATION_IMAGE_H

#define POS_VERTS 40000     // position des valeurs vertes de pixels dans le fichier .txt des images couleurs
#define POS_BLEUX 80000     // position des valeurs bleaus de pixels dans le fichier .txt des images couleurs
#define NBPIXEL 40000       //Nombre de pixels dans un fichier image RGB
#define NB_VALS_2BITS 64    // Nombre de valeurs des pixels après quatification du 2 bits
#define NB_VALS_3BITS 512   // Nombre de valeurs des pixels après quatification du 3 bits

#define MSK_2_BITS 0xC0;    //masque binaire 1100 0000 récupère les deux premiers bits lors du prétraitement 192
#define MSK_3_BITS 0XE0;    //masqque binaire 1110 0000 récupère les 3 premiers bits lors du prétraitement

typedef struct descripteur{
    
    int *histogramme; 
    char nom_fichier[6]; 
    
}DESCRIPTEUR; 

void get_taille_image_nb (FILE *, int *, int*); 

/*  Fonction réalisant l'oppération de prétraitement des valeurs contenues dans le fichier .txt décrivant une image couleur ......
    Cette opération est réalisée en fonction des nombre de bits de quantification passés en paramètres ( 2 ou 3) définis dans le ..
    mode administrateur. De plus, un tableau contenant les 120 000 valeurs brutes à traîter est passé en paramètres*/
void Pretraitement(int nb_bits_poids_fort, FILE *fich_image, int *tabPredescripeur); 

/*  Réalise une reconstitution de la valeur RVB du pixel en concaténant dans une seule variable les trois valeurs R V et B 
    du pixel initialement espacées de 40 000 valeurs dans le fichier initial. Elle retourne la valeur ainsi obtenue*/
int reconstitution_pixel(int *tableau_pretraite, int case_R, int nb_bits_quantification); 

/*  Réalise l'oppération de reconstitition du pixel sur l'entièreté des valeurs via la fonction reconstitution_pixel*/
void Reconst_pixels(int *tab_pretrait, int nb_bits_poids_fort); 

/*  Récupère le nombre d'occurences d'une couleur dans l'histogramme représenté par le tableau passé en paramètres, 
    contenant les valeurs des pixels au préalable prétraîtées et reconstituées. Retourne ce nombre sous la forme d'un entier*/
int nb_occurences(int *tab, int nbElem, int valeur); 

/* Fonction de constitution du descripteur définitif*/
int indexation(char *fichier_lu, int nb_bits_quantif, DESCRIPTEUR * descripteur, int nb_images_indexees); 
#endif
