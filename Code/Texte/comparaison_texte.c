#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "recherche_texte.h"
#include "structures_texte.h"

int comparison(comp_textes *comparaison, mot_occurences *compare, int taille_compare)
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
        for (int k = 0; k < taille_compare; k++)
        {
            for (int i = 0; i < nombre_mots; i++) /* Si segmentation fault essayer de changer <= */
            {

                // if (strcmp(compare[k].mot, index[i].mot) == 0)
                // {
                //     comparaison[nombre_fois_trouve].ressemblance.occurences = index[i].occurences;
                //     strcpy(comparaison[nombre_fois_trouve].ressemblance.mot, index[i].mot);
                //     strcpy(comparaison[nombre_fois_trouve].nom_fichier, buff);
                //     nombre_fois_trouve++;
                //     break;
                // }
                if (strcmp(compare[k].mot, index[i].mot) == 0)
                {
                    if (j == 0)
                    {
                        indice_tableau++;
                    }
                    comparaison[indice_tableau].ressemblance[j].occurences = index[i].occurences;
                    strcpy(comparaison[indice_tableau].ressemblance[j].mot, index[i].mot);
                    strcpy(comparaison[indice_tableau].nom_fichier, buff);
                    comparaison[indice_tableau].nb_mots_communs = j;
                    j++;
                }
            }
        }
        fclose(descripteurs);
    }
    fclose(liste_fichiers);

    return nombre_fois_trouve;
}
int main()
{
    mot_occurences moc[250];
    int taille_moc = file_to_tab("ProjetFilRouge/Documents/Textes/Corpus/03-Des_chercheurs_parviennent_à_régénérer.xml", moc);
    comp_textes comparaison[500];
    int entier = comparison(comparaison, moc, taille_moc);
    for (int i = 0; i < entier; i++)
    {
        printf("%s", comparaison[i].nom_fichier);
    }
}