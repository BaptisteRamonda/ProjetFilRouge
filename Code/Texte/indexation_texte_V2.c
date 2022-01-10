#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "indexation_texte.h"
#define MAX 1000

//Fonction pour enlever tous les espaces doubles d'une chaine de caractères (passage par paramètre pour récupérer le tableau, la fonction renvoie la taille du tableau)
int enlever_espaces_doubles(char *chaine)
{
    int nombre_caracteres_dans_tableau = strlen(chaine);
    int i, j;
    for (i = 0; i < nombre_caracteres_dans_tableau; i++)
    {
        while (chaine[i] == ' ' && chaine[i + 1] == ' ')
        {
            for (j = i; j < nombre_caracteres_dans_tableau; j++)
            {
                chaine[j] = chaine[j + 1];
            }
            nombre_caracteres_dans_tableau--;
        }
    }
    return nombre_caracteres_dans_tableau;
}
//Fonction pour enlever tous les espaces au début d'une chaine de caractères (passage par paramètre pour récupérer le tableau, la fonction renvoie la taille du tableau)
int enlever_espaces_debut(char *chaine)
{
    int nombre_caracteres_dans_tableau = strlen(chaine);
    int i;
    while (chaine[0] == ' ')
    {
        for (i = 0; i < nombre_caracteres_dans_tableau; i++)
        {
            chaine[i] = chaine[i + 1];
        }
        nombre_caracteres_dans_tableau--;
    }
    return nombre_caracteres_dans_tableau;
}

//Fonction pour enlever tous les tab au début d'une chaine de caractères (passage par paramètre pour récupérer le tableau, la fonction renvoie la taille du tableau)
int enlever_tab_debut(char *chaine)
{
    int nombre_caracteres_dans_tableau = strlen(chaine);
    while (chaine[0] == '\t')
    {
        for (int i = 0; i < nombre_caracteres_dans_tableau; i++)
        {
            chaine[i] = chaine[i + 1];
        }
        nombre_caracteres_dans_tableau--;
    }
    return nombre_caracteres_dans_tableau;
}

//POSSIBILITE DE FAIRE UNE FONCTION enlever_retour_ligne_debut SI BESOIN

//Fonction pour supprimer toutes les occurences d'une chaine de caractères dans une autre
int supprimer_occurences(char *texte, char *a_supprimer, int nombre_caracteres_tab)
{
    int i, j, taille_a_suppr;
    int found;
    taille_a_suppr = strlen(a_supprimer);
    for (i = 0; i <= nombre_caracteres_tab; i++)
    {
        //On regarde si les combinaisons de longueur de la taille du mot marchent pour chaque lettre
        found = 1;
        for (j = 0; j < taille_a_suppr; j++)
        {
            if (texte[i + j] != a_supprimer[j])
            {
                found = 0;
                break;
            }
            //Si le caractère précédent n'est pas un caractère de séparation, on considère qu'on est à la fin d'un mot (il reste donc le premier mot qui peut être un article)
            if (texte[i - 1] != ' ' && texte[i - 1] != '\t' && texte[i - 1] != '\n')
            {
                found = 0;
                break;
            }
        }
        //Si le caractère qui suit le mot n'est pas un caractère de séparation(ou la fin du fichier), ça veut dire que ce n'est pas un mot
        if (texte[i + j] != ' ' && texte[i + j] != '\t' && texte[i + j] != '\n' && texte[i + j] != '\0')
        {
            found = 0;
        }
        //Si le mot est trouvé, on décale tout le tableau de la taille du mot pour le "recouvrir"
        if (found == 1)
        {
            for (j = i; j <= nombre_caracteres_tab - taille_a_suppr; j++)
            {
                texte[j] = texte[j + taille_a_suppr];
            }
            nombre_caracteres_tab = nombre_caracteres_tab - taille_a_suppr;
            //On décale l'index pour rechercher les occurences suivantes
            i--;
        }
    }
    return nombre_caracteres_tab;
}

//Fonction qui calcule le nombre de caractères d'une chaine de caractères
int nombre_caracteres(char *fichier)
{
    int compteur = 0;
    FILE *fichier_a_compter;
    fichier_a_compter = fopen(fichier, "r");
    while (fgetc(fichier_a_compter) != EOF)
    {
        compteur++; // incrémentation du compteur
    }
    fclose(fichier_a_compter);
    return compteur;
}

//Fonction supprimant les mots inutiles (listés dans un txt)
int supprimer_mots_inutiles(char *chaine)
{
    FILE *liste_a_supprimer = NULL;
    liste_a_supprimer = fopen("../../Documents/Exceptions/mots_a_supprimer.txt", "r");
    int taille_mot;
    char mot_a_stocker[MAX];
    char cToStr[2];
    cToStr[1] = '\0';
    int nombre_caracteres_dans_tableau = strlen(chaine);
    do
    {
        cToStr[0] = fgetc(liste_a_supprimer);
        if (cToStr[0] != '\n')
        {
            strcat(mot_a_stocker, cToStr);
        }

        if (cToStr[0] == '\n')
        {
            mot_a_stocker[strlen(mot_a_stocker) - 1] = '\0';

            taille_mot = enlever_espaces_debut(mot_a_stocker);
            taille_mot = enlever_tab_debut(mot_a_stocker);

            nombre_caracteres_dans_tableau = supprimer_occurences(chaine, mot_a_stocker, nombre_caracteres_dans_tableau);
            strcpy(mot_a_stocker, "\0");
        }

    } while (cToStr[0] != EOF);
    return nombre_caracteres_dans_tableau;
}

//Fonction qui nettoie un fichier (enlève tous les mots qui ne sont pas à indéxer)
int indexation(char *fichier_a_ouvrir, mot_occurences *indexed)
{

    int nombre_mots = 0;

    //Les 3 lignes suivantes donnent le PATH courant à partir du nom du fichier
    char *chemin_dossier_xml = "../../Documents/Textes_propres/";
    char chemin_fichier_xml[MAX];
    strcat(strcpy(chemin_fichier_xml, chemin_dossier_xml), fichier_a_ouvrir);

    //Ouverture du fichier
    FILE *fichier_xml = NULL;
    fichier_xml = fopen(chemin_fichier_xml, "r");

    //Variables utilisées
    int i = 0;
    int nombre_caracteres_dans_tableau = 0;
    char propre[nombre_caracteres(chemin_fichier_xml)];
    char caractereActuel = 0;
    if (fichier_xml != NULL)
    {
        // Boucle de lecture des caractères un à un
        do
        {
            caractereActuel = fgetc(fichier_xml); // On lit le caractère

            while (caractereActuel == '<') //Tant que le caractère et le début d'une balise
            {
                do
                {
                    caractereActuel = fgetc(fichier_xml); //on passe au caractère suivant
                } while (caractereActuel != '>');         //tant que ce n'est pas la fin de la balise
                caractereActuel = fgetc(fichier_xml);     //on passe au caractère d'après le '>' de fin de balise
            }

            while (caractereActuel == ':' || caractereActuel == '\n' || caractereActuel == ',' || caractereActuel == '.' || caractereActuel == '\'' || caractereActuel == '(' || caractereActuel == ')' || caractereActuel == '\t' || caractereActuel == '/' || caractereActuel == '!' || caractereActuel == '?' || caractereActuel == '"') //problème avec le caractère U+00AD qui n'est pas reconnu comme un caractère
            {
                caractereActuel = ' ';
            }

            propre[i] = caractereActuel; // On l'ajoute au tableau propre
            i = i + 1;
            nombre_caracteres_dans_tableau = nombre_caracteres_dans_tableau + 1;

        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

        nombre_caracteres_dans_tableau = enlever_espaces_debut(propre);
        nombre_caracteres_dans_tableau = enlever_espaces_doubles(propre);

        //On remplace les majuscules par des minuscules
        for (i = 0; i < nombre_caracteres_dans_tableau; i++)
        {
            propre[i] = tolower(propre[i]);
        }
        //On enlève les mots inutiles spécifiés dans le .txt
        nombre_caracteres_dans_tableau = supprimer_mots_inutiles(propre);

        //On enlève les espaces doubles
        nombre_caracteres_dans_tableau = enlever_espaces_doubles(propre);

        propre[strlen(propre) - 1] = '\0';
        //On pourrait faire une fonction spécifique du code ci dessous si besoin de le réutiliser, pour ce faire on a besoin de faire 2 passages par paramètres

        char liste_mots[MAX][MAX_MOT];

        int occurences[MAX];
        for (i = 0; i < MAX; i++)
            occurences[i] = 0;

        char mot_a_stocker[MAX_MOT];

        char caractere_actuel;
        int longueur_mot = 0;
        int i = 0;
        caractere_actuel = propre[i];
        while (caractere_actuel != '\0')
        {
            {
                mot_a_stocker[longueur_mot++] = caractere_actuel;
                mot_a_stocker[longueur_mot] = '\0';
                if (caractere_actuel == ' ')
                {

                    // printf("[DEBUT]%s[FIN]\n", mot_a_stocker);
                    int unique = 1; //Est unique
                    for (int i = 0; i < nombre_mots && unique; i++)
                    {
                        if (strcmp(mot_a_stocker, liste_mots[i]) == 0) //Si les deux chaines sont égales
                        {
                            occurences[i]++;
                            unique = 0; //n'est pas unique
                        }
                    }
                    if (unique) //Si après parcours toujours unique
                    {
                        strcpy(liste_mots[nombre_mots], mot_a_stocker);
                        occurences[nombre_mots]++;
                        nombre_mots++;
                    }

                    longueur_mot = 0;
                }
                i++;
                caractere_actuel = propre[i];
            }
        }

        // mot_occurences index[nombre_mots];
        for (i = 0; i < nombre_mots; i++)
        {
            strcpy(indexed[i].mot, liste_mots[i]);
            indexed[i].occurences = occurences[i];
        }
        //On trie le tableau dans l'ordre décroissant
        mot_occurences temp;
        for (i = 0; i < nombre_mots - 1; i++)
        {
            for (int j = i + 1; j < nombre_mots; j++)
            {
                if (indexed[i].occurences < indexed[j].occurences)
                {
                    strcpy(temp.mot, indexed[i].mot);
                    temp.occurences = indexed[i].occurences;

                    strcpy(indexed[i].mot, indexed[j].mot);
                    indexed[i].occurences = indexed[j].occurences;

                    strcpy(indexed[j].mot, temp.mot);
                    indexed[j].occurences = temp.occurences;
                }
            }
        }

        for (int i = 0; i < nombre_mots; i++)
        {

            printf("%d: %s\n", indexed[i].occurences, indexed[i].mot);
        }
        fclose(fichier_xml);
    }

    return nombre_mots;
}

void tab_in_file(mot_occurences *indexed, char *nom_fichier_destination, int taille_tableau)
{
    //Les 3 lignes suivantes donnent le PATH courant à partir du nom du fichier
    char *chemin_dossier_tableaux = "../../Documents/Descripteurs_Textes/";
    char chemin_fichier_tableau[MAX];
    strcat(strcpy(chemin_fichier_tableau, chemin_dossier_tableaux), nom_fichier_destination);

    //Ouverture du fichier
    FILE *fichier_tableau = NULL;
    fichier_tableau = fopen(chemin_fichier_tableau, "w");
    for (int i = 0; i < taille_tableau; i++)
    {
        fprintf(fichier_tableau, "%s", indexed[i].mot);
        fprintf(fichier_tableau, "%d\n", indexed[i].occurences);
    }
    fclose(fichier_tableau);
}

int main(int argc, char *argv[])
{
    int taille;
    char *file_to_open = argv[1];
    mot_occurences indexed[MAX];

    taille = indexation(file_to_open, indexed);


    char *descripteurs = "Descripteurs_V2_";
    char nom_fichier_descripteurs[250];
    strcat(strcpy(nom_fichier_descripteurs, descripteurs), file_to_open);
    tab_in_file(indexed, nom_fichier_descripteurs, taille);

    return 0;
}