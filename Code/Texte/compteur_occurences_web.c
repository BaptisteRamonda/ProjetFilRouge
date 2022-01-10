#include <ctype.h>
#include <stdio.h>
#include <string.h>
enum
{
    MAX = 1000,
    MAX_MOT = 50
};

int main(void)
{
    char liste_mots[MAX][MAX_MOT];
    int occurences[MAX] = {0};
    int nombre_mots = 0;
    char mot_a_stocker[MAX_MOT];
    int caractere_actuel;
    int longueur_mot = 0;
    int i = 0;
    caractere_actuel = propre[i];
    while (caractere_actuel != EOF)
    {
        {
            mot_a_stocker[longueur_mot++] = caractere_actuel;
            mot_a_stocker[longueur_mot] = '\0';
            if (caractere_actuel == ' ')
            {
                int found = 0; //Pas trouvé
                for (int i = 0; i < nombre_mots; i++)
                {
                    if (strcmp(mot_a_stocker, liste_mots[i]) == 0) //Si les deux haines sont égales
                    {
                        occurences[i]++;
                        found = 1; //Trouvé
                        break;
                    }
                }
                if (!found) //Si après parcours toujours pas trouvé
                {
                    strcpy(liste_mots[nombre_mots], mot_a_stocker);
                    occurences[nombre_mots++] = 1;
                }
                longueur_mot = 0;
                i++;
                caractere_actuel = propre[i];
            }
        }
    }

    for (int i = 0; i < nombre_mots; i++)
        printf("%3d: %s\n", occurences[i], liste_mots[i]);

    return 0;
}

void tri_decroissant(mot_occurences *tab)
{
    mot_occurences temp;
    for (i = 0; i < nombre_mots - 1; i++)
    {
        for (int j = i + 1; j < nombre_mots; j++)
        {
            if (tab[i].occurences < tab[j].occurences)
            {
                strcpy(temp.mot, tab[i].mot);
                temp.occurences = tab[i].occurences;

                strcpy(tab[i].mot, tab[j].mot);
                tab[i].occurences = tab[j].occurences;

                strcpy(tab[j].mot, temp.mot);
                tab[j].occurences = temp.occurences;
            }
        }
    }
}