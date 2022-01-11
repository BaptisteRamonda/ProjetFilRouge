#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
#define MAX_MOT 50

typedef struct s_mot_occ
{
    char mot[MAX_MOT];
    int occurences;
} mot_occurences;



int file_to_tab(char *path, mot_occurences *index)
{

    FILE *fichier_descripteur = NULL;
    fichier_descripteur = fopen(path, "r");
    int j = 0;
    int i = 0;
    char mot_a_stocker[50];
    int occurences;
    char buff[MAX];
    char *useless;
    // long occurences;
    while (fscanf(fichier_descripteur, "%s", buff) != EOF)
    {
        if (j % 2 == 0)
            // index[i].mot = buff;
            strcpy(index[i].mot, buff);
        if (j % 2 != 0)
            index[i].occurences = strtol(buff, &useless, 10);
        // printf("%d", occurences);

        j++;
        if (j % 2 == 0)
            i++;
    }
    fclose(fichier_descripteur);
    return i;
}
int main()
{
    mot_occurences index[MAX];
    int taille;
    taille =file_to_tab("../../Documents/Textes/Descripteurs_Textes/Descripteurs_03-Des_chercheurs_parviennent_à_régénérer.xml", index);
    for (int i = 0; i < taille; i++)
    {
        printf("%s ", index[i].mot);
        printf("%d\n", index[i].occurences);
    }
}
