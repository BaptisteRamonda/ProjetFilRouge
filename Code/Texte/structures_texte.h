#ifndef __STRUCTURES_TEXTE_H__
#define __STRUCTURES_TEXTE_H__
#define MAX_MOT 50

/* .h contenant les structures utilisées pour l'indexation et la recherche texte*/

//Structure associant un mot à son nombre d'occurences, utilisé pour l'indexation d'un texte
typedef struct s_mot_occ
{
    char mot[MAX_MOT];
    int occurences;
} mot_occurences;

//Structurer associant un nombre d'occurences d'un certain mot avec un nom de fichier, utilisé pour la recherche par mot
typedef struct s_textes_freq
{
    struct s_mot_occ mot_recherche;
    char nom_fichier[250];
} freq_mot_texte;

#endif