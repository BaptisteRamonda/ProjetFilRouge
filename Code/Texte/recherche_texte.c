#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures_texte.h"
#define MAX 1000
#define MAX_MOT 50

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
    char *path = "../../Documents/Textes/Descripteurs_Textes/Descripteurs_";
    strcpy(path_para, " ");
    strcat(strcpy(path_para, path), nom);
}

int recherche(freq_mot_texte *frequence, char *mot)
{
    int nombre_fois_trouve = 0;
    //Les prochaines lignes comptent le nombre de fichiers indexés
    int nombre_fichiers_listes;
    char parcours;
    FILE *liste_fichiers = NULL;
    liste_fichiers = fopen("../../Documents/Textes/Liste_Noms_Textes/Liste_noms_textes.txt", "r");

    while ((parcours = fgetc(liste_fichiers)) != EOF)
    {
        if (parcours == '\n')         //Si c'est un retour à la ligne
            nombre_fichiers_listes++; //On incrémente le compteur
    }
    fseek(liste_fichiers, 0, SEEK_SET); //On retourne au début du fichier

    int nombre_mots;
    char buff[250];
    char path_file[250];

    while (fscanf(liste_fichiers, "%s", buff) != EOF)
    {

        int nombre_mots = 0;
        FILE *descripteurs;
        // strcpy(path_file, " ");
        // strcat(strcpy(path_file, "../../Documents/Textes/Descripteurs_Textes/Descripteurs_"), buff);

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
        for (int i = 0; i < nombre_mots; i++) /* Si segmentation fault essayer de changer <= */
        {

            if (strcmp(mot, index[i].mot) == 0)
            {
                frequence[nombre_fois_trouve].mot_recherche.occurences = index[i].occurences;
                strcpy(frequence[nombre_fois_trouve].mot_recherche.mot, index[i].mot);
                strcpy(frequence[nombre_fois_trouve].nom_fichier, buff);
                nombre_fois_trouve++;
                break;
            }
        }
        fclose(descripteurs);
    }
    fclose(liste_fichiers);

    return nombre_fois_trouve;
}

void tri_frequences(freq_mot_texte *frequences, int nombre_mots)
{
    freq_mot_texte temp;
    for (int i = 0; i < nombre_mots - 1; i++)
    {
        for (int j = i + 1; j < nombre_mots; j++)
        {
            if (frequences[i].mot_recherche.occurences < frequences[j].mot_recherche.occurences)
            {
                strcpy(temp.mot_recherche.mot, frequences[i].mot_recherche.mot);
                strcpy(temp.nom_fichier, frequences[i].nom_fichier);
                temp.mot_recherche.occurences = frequences[i].mot_recherche.occurences;

                strcpy(frequences[i].mot_recherche.mot, frequences[j].mot_recherche.mot);
                strcpy(frequences[i].nom_fichier, frequences[j].nom_fichier);
                frequences[i].mot_recherche.occurences = frequences[j].mot_recherche.occurences;

                strcpy(frequences[j].mot_recherche.mot, temp.mot_recherche.mot);
                strcpy(frequences[j].nom_fichier, temp.nom_fichier);
                frequences[j].mot_recherche.occurences = temp.mot_recherche.occurences;
            }
        }
    }
}

int main(int argc, char *argv[])
{

    freq_mot_texte frequence[MAX];
    char mot[50];
    scanf("%s", mot);
    int taille2 = recherche(frequence, mot);
    tri_frequences(frequence, taille2);
    for (int i = 0; i < taille2; i++)
    {
        printf("%s ", frequence[i].nom_fichier);
        printf("%s ", frequence[i].mot_recherche.mot);
        printf("%d \n", frequence[i].mot_recherche.occurences);
    }
}
