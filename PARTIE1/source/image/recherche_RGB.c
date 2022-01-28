#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "indexation_image.h"
#include "../../headers/image/recherche_RGB.h"

// void recuperation_histo()
// {

//     char *chemin_base_descripteurs = "Liste_noms_images.txt";
//     char nom_fihier_indexe[7];
//     char *line = NULL;
//     size_t len = 0;
//     ssize_t read;
//     char *noms_fichiers[100];
//     int i=0;

//     FILE *fichier_base;
//     fichier_base = fopen(chemin_base_descripteurs, "r");

//     if (fichier_base == NULL)
//         exit(EXIT_FAILURE);
//     else
//     {
//        while((read = getline(&line, &len, fichier_base)) != 1){
//         strcpy(nom_fihier_indexe, line);
//         nom_fihier_indexe[i] = nom_fihier_indexe;
//        }
//     }
// }

// int main()
// {
//     recuperation_histo();
//     return 0;
// }

int file_to_tab(char *path, int **descripteurs)
{
    int k=0;
    FILE *fichier_descripteurs = NULL;
    fichier_descripteurs = fopen(path, "r");
    

}