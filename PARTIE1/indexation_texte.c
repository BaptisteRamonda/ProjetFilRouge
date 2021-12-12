#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
        compteur++; /* incrémentation du compteur */
    }
    fclose(fichier_a_compter);
    return compteur;
}

//Fonction qui nettoie un fichier (enlève tous les mots qui ne sont pas à indéxer)
void nettoyage_fichier(char *fichier_a_ouvrir)
{
    //Les 3 lignes suivantes donnent le PATH courant à partir du nom du fichier
    char *chemin_dossier_xml = "../../Documents/Textes_propres/";
    char chemin_fichier_xml[MAX];
    strcat(strcpy(chemin_fichier_xml, chemin_dossier_xml), fichier_a_ouvrir);

    //Ouverture du fichier
    FILE *fichier_xml = NULL;
    fichier_xml = fopen(chemin_fichier_xml, "r");

    //Variables utilisées
    int i = 0;
    int j;
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

            while (caractereActuel == ':' || caractereActuel == '\n' || caractereActuel == ',' || caractereActuel == '.' || caractereActuel == '\'' || caractereActuel == '(' || caractereActuel == ')') //problème avec le caractère U+00AD qui n'est pas reconnu comme un caractère
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

        //DEBUT TRANSFO FONCTION
        //Ouverture du fichier de mots à supprimer
        FILE *liste_a_supprimer = NULL;
        liste_a_supprimer = fopen("../../Documents/Exceptions/mots_a_supprimer.txt", "r");
        int taille_mot;
        char mot_a_stocker[MAX];
        char cToStr[2];
        cToStr[1] = '\0';
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
                nombre_caracteres_dans_tableau = supprimer_occurences(propre, mot_a_stocker, nombre_caracteres_dans_tableau);
                strcpy(mot_a_stocker, "\0");
            }

        } while (cToStr[0] != EOF);
        //FIN TRANSFO FONCTION

        nombre_caracteres_dans_tableau=enlever_espaces_doubles(propre);
        propre[strlen(propre)-1]=EOF; //Pas bien compris pourquoi il prend un caractère de trop(à revoir)

        //On affiche le texte propre (à enlever)
        printf("[DEBUT TEXTE]");
        printf("%s", propre);
        printf("[FIN TEXTE]");
        printf("\n");
        fclose(fichier_xml);
    }
}

int main()
{
    char *file_to_open = "03-Des_chercheurs_parviennent_à_régénérer.xml";
    nettoyage_fichier(file_to_open);
    return 0;
}