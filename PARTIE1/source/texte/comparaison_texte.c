#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../headers/texte/structures_texte.h"
#define MAX 1000

int file_to_tab(char *path, mot_occurences *index)
{

    FILE *fichier_descripteur = NULL;
    fichier_descripteur = fopen(path, "r");
    int j = 0;
    int i = 0;
    char buff[MAX_MOT];
    char *useless;
    while (fscanf(fichier_descripteur, "%s", buff) != EOF)
    {
        if (j % 2 == 0)
            strcpy(index[i].mot, buff);
        if (j % 2 != 0)
            index[i].occurences = strtol(buff, &useless, 10);
        j++;
        if (j % 2 == 0)
            i++;
    }

    fclose(fichier_descripteur);
    return i;
}

void name_to_path_descripteurs(char *nom, char *path_para) //Marche uniquement avec un passage par paramètres
{
    char *path = "../../documents/texte/descripteurs_textes/Descripteurs_";
    strcpy(path_para, " ");
    strcat(strcpy(path_para, path), nom);
}

int comparison(comp_textes *comparaison, mot_occurences *compare, int taille_compare)
{

    char parcours;
    FILE *liste_fichiers = NULL;
    liste_fichiers = fopen("../../documents/texte/liste_noms_textes/liste_noms_textes.txt", "r");
    int j;
    int nombre_mots = 0;
    char buff[250];
    char path_file[250];
    int indice_tableau = -1;
    while (fscanf(liste_fichiers, "%s", buff) != EOF)
    {

        FILE *descripteurs;

        name_to_path_descripteurs(buff, path_file);
        descripteurs = fopen(path_file, "r");
        while ((parcours = fgetc(descripteurs)) != EOF)
        {
            if (parcours == '\n')
                nombre_mots++;
        }
        fseek(descripteurs, 0, SEEK_SET);

        mot_occurences index[nombre_mots];
        nombre_mots = file_to_tab(path_file, index);
        j = 0;
        int total = 0;
        for (int k = 0; k < taille_compare; k++)
        {
            total += compare[k].occurences;
            for (int i = 0; i < nombre_mots; i++) /* Si segmentation fault essayer de changer <= */
            {

                if (strcmp(compare[k].mot, index[i].mot) == 0)
                {
                    if (j == 0)
                    {
                        indice_tableau++;
                    }

                    if (index[i].occurences <= compare[k].occurences)
                    {
                        comparaison[indice_tableau].ressemblance += index[i].occurences;
                    }
                    else
                    {
                        comparaison[indice_tableau].ressemblance += compare[k].occurences;
                    }

                    strcpy(comparaison[indice_tableau].nom_fichier, buff);

                    comparaison[indice_tableau].nb_mots_communs = j;
                    j++;
                }
            }
        }
        comparaison[indice_tableau].ressemblance = (comparaison[indice_tableau].ressemblance / total) * 100;

        fclose(descripteurs);
    }

    fclose(liste_fichiers);

    comp_textes temp;
    for (int i = 0; i < indice_tableau - 1; i++)
    {
        for (int j = i + 1; j < indice_tableau; j++)
        {
            if (comparaison[i].ressemblance < comparaison[j].ressemblance)
            {
                strcpy(temp.nom_fichier, comparaison[i].nom_fichier);
                temp.nb_mots_communs = comparaison[i].nb_mots_communs;
                temp.ressemblance = comparaison[i].ressemblance;

                strcpy(comparaison[i].nom_fichier, comparaison[j].nom_fichier);
                comparaison[i].nb_mots_communs = comparaison[j].nb_mots_communs;
                comparaison[i].ressemblance = comparaison[j].ressemblance;

                strcpy(comparaison[j].nom_fichier, temp.nom_fichier);
                comparaison[j].nb_mots_communs = temp.nb_mots_communs;
                comparaison[j].ressemblance = temp.ressemblance;
            }
        }
    }

    return indice_tableau;
}

int main(int arc, char *argv[])
{
    char path_para[250];
    name_to_path_descripteurs(argv[1], path_para);
    mot_occurences moc[MAX];
    int taille_moc = file_to_tab(path_para, moc);
    comp_textes comparaison[MAX];
    int entier = comparison(comparaison, moc, taille_moc);
    for (int i = 0; i < 5; i++)
    {
        printf("SCORE : %f AVEC", comparaison[i+1].ressemblance);
        printf(" %d MOTS DISTINCTS EN COMMUN : ", comparaison[i+1].nb_mots_communs);
        printf("%s \n", comparaison[i+1].nom_fichier);
    }
}
