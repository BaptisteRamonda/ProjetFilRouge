/*  AUTEUR :    SAURAT DORIAN                                                                               */
/*                                                                                                          */
/*  NOM :       indexation_image.c                                                                          */
/*                                                                                                          */
/*  Fonction :  Réalise la fonction d'indexation d'un dossier de fichiers images via un prétraitement des   */
/*              documents texte, recomposition des pixels en valeurs RVB puis calcul des histogrammes tous  */
/*              stockés dans un fichier texte                                                               */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../headers/image/indexation_image.h"

void get_Taille_Type_image(FILE *fich_image, int *taille, int *type)
{
    int h = 0;
    int l = 0;

    fscanf(fich_image, "%d", &h);       //Lignes 
    fscanf(fich_image, "%d", &l);       //Colonnes 
    fscanf(fich_image, "%d", type);     //Type
    *taille = (h * l);
}

void Pretraitement(int nb_bits_poids_fort, FILE *fich_image, int *tabPredescripeur)
{

    int vals_traitees = 0;
    int nombre = 0;         //nombre courant lu en cours de traitement

    if (fich_image == NULL)     //test de l'ouverture du fichier image.txt
    {
        printf("Erreur à la lecture du fichier_lu, char *fichier_lu\n");
        exit(1);
    }

    fscanf(fich_image, "%d", &nombre);  // lescture des entiers 1 par 1 dans le fichier jusqu'à la fin du fichier

    do // lecture des entiers 1 par 1 dans le fichier jusqu'à la fin du fichier
    {
        if (nb_bits_poids_fort == 2)
        {
            nombre = nombre & MSK_2_BITS;
            nombre = nombre >> 6;                     //Récupération des deux bits de poids par masquage puis décalage. Normalement un décalage suffit 
            tabPredescripeur[vals_traitees] = nombre; //replace les valeurs après traîtement dans les tableau
            vals_traitees++;
        }
        else
        {
            nombre = nombre & MSK_3_BITS;
            nombre = nombre >> 5;                     //Récupération des trois bits de poids par masquage puis décalage. Normalement un décalage suffit 
            tabPredescripeur[vals_traitees] = nombre; //replace les valeurs après traîtement dnas les tableau
            vals_traitees++;
        }
        fscanf(fich_image, "%d", &nombre);
    } while (fgetc(fich_image) != EOF);
}

int reconstitution_pixel(int *tableau_pretraite, int case_R, int nb_bits_quantification)
{
    int valeur_pixel = 0;

    valeur_pixel = tableau_pretraite[case_R];                                                        // case_R correspond au rang de la valeur rouge du pixel. Nous savons que 40 000 valeurs la séparent de la valeur verte associée dans le fichier et 80 000 de la valeur bleue
    valeur_pixel = (valeur_pixel << nb_bits_quantification) | tableau_pretraite[case_R + POS_VERTS]; // un décalage du nombre de bits de cantification vers la gauche est fait pour insérer la valeur verte
    valeur_pixel = (valeur_pixel << nb_bits_quantification) | tableau_pretraite[case_R + POS_BLEUX]; // un décalage du nombre de bits de cantification vers la gauche est fait pour insérer la valeur bleue
    return valeur_pixel;                                                                             // valeur du pixel reconstituée de la forme RVB avec nb_bits_quantification chacuns
}

void Reconst_pixels(int *tab_pretrait, int nb_bits_poids_fort)
{
    int nb_pix = 0; /*// nombre de pixels traitées doit être de 40000 pour les images couleur;*/

    if (tab_pretrait == NULL)
    {
        printf("Erreur de remplissage du tab_pretrait des valeurs prétraitées\n");
        exit(1);
    }
    else
    {
        for (nb_pix = 0; nb_pix < NBPIXEL; nb_pix++)
        {
            tab_pretrait[nb_pix] = reconstitution_pixel(tab_pretrait, nb_pix, nb_bits_poids_fort); //Reconstion des valeurs finales par concaténation des trois conposantes RVB
        }
    }
}

int nb_occurences(int *tab_valeurs, int nbElem, int valeur) 
{
    if (nbElem == 0)
        return 0;
    if (*tab_valeurs == valeur)
        return 1 + nb_occurences(tab_valeurs + 1, nbElem - 1, valeur);
    else
        return nb_occurences(tab_valeurs + 1, nbElem - 1, valeur);
}

int indexation(char *fichier_lu, int nb_bits_quantif, DESCRIPTEUR *descripteur, int nb_images_indexees)
{
    char *chemin_dossier_images = "../../documents/image/TEST_IMAGE/";
    char chemin_fichier_image[1000];
    strcat(strcpy(chemin_fichier_image, chemin_dossier_images), fichier_lu); // acquisition du chemin du fichier à lire 

    FILE *fich_r = fopen(chemin_fichier_image, "r"); //ouverture fichier image lu  // ouverture du fichier

    int nombre_pixels = 0;
    int type_image = 0;
    int nb_valeurs = 0;
    // printf("test4\n");
    get_Taille_Type_image(fich_r, &nombre_pixels, &type_image); // récupération de la taille et du type de l'image

    if (type_image == 3)
    {
        nb_valeurs = 120000;
    }
    else
    {
        nb_valeurs = nombre_pixels;
    }
    // printf("test3\n");
    int tab_valeurs[nb_valeurs];  // tableau contenant les valeurs à traiter
    int nb_valeur_post_trait = 0; // nombre de valeurs arès le traitement

    if (nb_bits_quantif == 2)
        nb_valeur_post_trait = NB_VALS_2BITS;
    else
        nb_valeur_post_trait = NB_VALS_3BITS;

    int tab_histogramme[nb_valeur_post_trait]; // Contiendra l'histogramme après traitement hormis le nom du fichier

    char *fich_ecrit = "base_descripteur_image.txt";
    char base_descripteurs[30];
    strcpy(base_descripteurs, fich_ecrit);
    char *chemin_dossier_base = "../../documents/image/descripteurs/";
    char chemin_fichier_base[1000];
    strcat(strcpy(chemin_fichier_base, chemin_dossier_base), base_descripteurs);

    FILE *fich_w = fopen(chemin_fichier_base, "a"); //ouverrture du fichier des descripteurs

    fprintf(fich_w, "%s ", chemin_fichier_image);
    fprintf(fich_w, "%s", "\n");

    Pretraitement(nb_bits_quantif, fich_r, tab_valeurs);

    if (type_image == 3)
    {
        Reconst_pixels(tab_valeurs, nb_bits_quantif); // Reconstitution des pixels d'images couleur seulement avec leurs valeurs RVB dans une seule variable
    }
    if (nb_bits_quantif == 2)
    {
        for (int i = 0; i < NB_VALS_2BITS; i++)
        {
            fprintf(fich_w, "%d ", i);
            fprintf(fich_w, "%d ", nb_occurences(tab_valeurs, sizeof(tab_valeurs) / sizeof(*tab_valeurs), i));
            tab_histogramme[i] = nb_occurences(tab_valeurs, sizeof(tab_valeurs) / sizeof(*tab_valeurs), i);
            fprintf(fich_w, "%s", "\n");
            nombre_pixels += nb_occurences(tab_valeurs, sizeof(tab_valeurs) / sizeof(*tab_valeurs), i);
        }
    }
    else
    {
        for (int i = 0; i < NB_VALS_3BITS; i++)
        {
            fprintf(fich_w, "%d ", i);
            fprintf(fich_w, "%d ", nb_occurences(tab_valeurs, sizeof(tab_valeurs) / sizeof(*tab_valeurs), i));
            tab_histogramme[i] = nb_occurences(tab_valeurs, sizeof(tab_valeurs) / sizeof(*tab_valeurs), i);
            fprintf(fich_w, "%s", "\n");
            nombre_pixels += nb_occurences(tab_valeurs, sizeof(tab_valeurs) / sizeof(*tab_valeurs), i);
        }

        fprintf(fich_w, "%s", "\n\r");
    }
    fclose(fich_r);
    fclose(fich_w);

    descripteur[nb_images_indexees].histogramme = tab_histogramme;
    strcpy(descripteur[nb_images_indexees].nom_fichier, fichier_lu);

    nb_images_indexees++;

    if (nombre_pixels == sizeof(tab_valeurs) / sizeof(*tab_valeurs))
        return 1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    // printf("test1\n");
    DESCRIPTEUR liste_descripteurs[100];
    int nb_images_index = 0;
    indexation(argv[1], 2, liste_descripteurs, nb_images_index);

    return 0;
}
