#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
#define MAX_MOT 50

typedef struct s_mot_occ
{
    char mot[MAX_MOT];
    int occurences;
} mot_occurences;

// char[10][250] recherche_mot(char *mot, char *nom_fichier) //changer type retour
// {
//     //Les lignes suivantes ouvrent le tableau des descripteurs du fhichier donné en paramètre
//     FILE *fichier_descripteur = NULL;
//     char fichier_a_rechercher[250];
//     char *chemin_dossier_tableaux = "../../Documents/Textes/Descripteurs_Textes/";
//     strcat(strcpy(fichier_a_rechercher, chemin_dossier_tableaux), nom_fichier);
//     fichier_descripteur = fopen(fichier_a_rechercher, "r");
// }

void file_to_tab(char *path, mot_occurences *index)
{

    FILE *fichier_descripteur = NULL;
    fichier_descripteur = fopen(path, "r");
    char caractere_actuel;
    int i = 0;
    int j = 0;
    mot_a_stocker[50];
    caractere_actuel = fgetc(fichier_descripteur);
    while (caractere_actuel != EOF)
    {
        while (caratere_actuel != '\n')
        {
            index[j].mot[i] = caractere_actuel;
            i++;
            caractere_actuel = fgetc(fichier_descripteur);
        }
        // mot_a_stocker[i - 1] = '\0';
        caractere_actuel = fgetc(fichier_descripteur);
        index[j].occurences = caractere_actuel;

        j++;
        i = 0;
    }
}
int main(){
    mot_occurences[MAX];

    for (int i = 0; i < nombre_mots; i++)
        {
            printf("%s", index[i].mot);
            printf("%d", index[i].occurences);
        }
}
