/*  AUTEUR :    SAURAT DORIAN                                                                               */
/*                                                                                                          */
/*  NOM :   comparaison_image.c                                                                             */
/*                                                                                                          */
/*  Fonction :  Réalise la fonction de recherche d'image par comparaison d'un fichier normalement entré     */
/*              au clavier par l'utilisateur. En réalisté, ce fichier est encore en phase de test et le     */
/*              texte comparé est encore changé de manière brute dans le code                               */



/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Cette partie à été  ajoutése au projet après le rendu du 21 car  buggée et incomplète 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Indexation_image.h"
#include "comparaison_image.h"

int file_to_tab(char *path, FILE *fichier_descripteurs, COULEUR_OCCUR *index, int nb_bits_quantif)
{
    char buffer_path[100];
    char path_fichier[100];
    strcpy(path_fichier, path);

    char *ret;
    int couleur = 0;
    int occurences = 0;
    int nb_valeurs_img = 0;

    if (nb_bits_quantif == 2)
        nb_valeurs_img = NB_VALS_2BITS;
    else
        nb_valeurs_img = NB_VALS_3BITS;

    do
    {
        fgets(buffer_path, 200, fichier_descripteurs);
        ret = strstr(buffer_path, path_fichier);
    } while (ret == NULL);

    if (ret != NULL)
    {

        for (int i = 0; i < nb_valeurs_img; i++)
        {
            fscanf(fichier_descripteurs, "%d", &couleur);
            printf("%d ", couleur);
            index[i].color = couleur;
            fscanf(fichier_descripteurs, "%d", &occurences);
            printf("%d \n", occurences);
            index[i].occur = occurences;
        }

        ret = NULL;
    }

    return nb_valeurs_img;
}

void name_to_path_fichier(char *nom, char *path_para) //Marche uniquement avec un passage par paramètres
{
    char *path = "/home/saurat/Documents/UPSSITECH/SRI_1A/Projet_Fil_Rouge/DATA_FIL_ROUGE_DEV/IMAGES/";
    strcat(strcpy(path_para, path), nom);
}

int comparaison(COMP_IMG *comparaison, COULEUR_OCCUR *compare, int taille_compare, int nb_bits_quantif)
{

    FILE *liste_fichiers = NULL;
    liste_fichiers = fopen("/home/saurat/Documents/UPSSITECH/SRI_1A/Projet_Fil_Rouge/Module_image/IMAGE/Image/Liste_noms_images.txt", "r");

    FILE *base_descripteurs = NULL;
    base_descripteurs = fopen("/home/saurat/Documents/UPSSITECH/SRI_1A/Projet_Fil_Rouge/Module_image/IMAGE/Image/base_descripteur_image.txt", "r");

    char buff[250];

    char path_fichier[250];
    int j;
    int nb_couleurs = 0;
    int indice_tableau = -1;
    while (fscanf(liste_fichiers, "%s", buff) != EOF)
    {

        COULEUR_OCCUR index[511];

        name_to_path_fichier(buff, path_fichier);
        nb_couleurs = file_to_tab(path_fichier, base_descripteurs, index, nb_bits_quantif);
        j = 0;
        int total = 0;
        for (int k = 0; k < taille_compare; k++)
        {
            total += compare[k].occur;
            for (int i = 0; i < nb_couleurs; i++)
            {
                if (compare[k].color == index[i].color)
                {
                    if (j == 0)
                    {
                        indice_tableau++;
                    }

                    if (index[i].occur <= compare[k].occur)
                    {
                        comparaison[indice_tableau].ressemblance += index[i].occur;
                    }
                    else
                    {
                        comparaison[indice_tableau].ressemblance += compare[k].occur;
                    }

                    strcpy(comparaison[indice_tableau].nom_fichier, buff);

                    comparaison[indice_tableau].nb_couleurs_communes = j;
                    j++;
                }
            }
        }
        comparaison[indice_tableau].ressemblance = (comparaison[indice_tableau].ressemblance / total) * 100;
       
    }
    fclose(base_descripteurs);
    fclose(liste_fichiers);

    COMP_IMG temp;
    for (int i = 0; i < nb_couleurs - 1; i++)
    {
        for (int j = i + 1; j < nb_couleurs; j++)
        {
            if (comparaison[i].ressemblance < comparaison[j].ressemblance)
            {
                strcpy(temp.nom_fichier, comparaison[i].nom_fichier);
                temp.nb_couleurs_communes = comparaison[i].nb_couleurs_communes;
                temp.ressemblance = comparaison[i].ressemblance;

                strcpy(comparaison[i].nom_fichier, comparaison[j].nom_fichier);
                comparaison[i].nb_couleurs_communes = comparaison[j].nb_couleurs_communes;
                comparaison[i].ressemblance = comparaison[j].ressemblance;

                strcpy(comparaison[j].nom_fichier, temp.nom_fichier);
                comparaison[j].nb_couleurs_communes = temp.nb_couleurs_communes;
                comparaison[j].ressemblance = temp.ressemblance;
            }
        }
    }

    return indice_tableau;
}

int main(int arc, char *argv[])
{
    char path_para[250];

    name_to_path_fichier("40.txt", path_para);
    COULEUR_OCCUR moc[511];
    FILE *base_descripteurs = NULL;
    base_descripteurs = fopen("/home/saurat/Documents/UPSSITECH/SRI_1A/Projet_Fil_Rouge/Module_image/IMAGE/Image/base_descripteur_image.txt", "r");

    int taille_moc = file_to_tab(path_para, base_descripteurs, moc, 2);
    fclose(base_descripteurs);
    COMP_IMG compar[63];
    comparaison(compar, moc, taille_moc, 2);
    for (int i = 0; i < 10; i++)
    {
        printf("SCORE : %f AVEC", compar[i].ressemblance);
        printf("%s \n", compar[i].nom_fichier);
    }

}