#ifndef __RECHERCHE_TEXTE_H__
#define __RECHERCHE_TEXTE_H__

/*
Fonction : pour récupérer un tableau de mot_occurences depuis
un fichier .txt (ou autre extension) étant une indexation.
Paramètres : (1) la chaine de caractères étant le path du fichier 
.txt. (2) passage par paramètres du tableau de mot_occurences.
Renvoie : le nombre de mots dans le tableau.
*/
int file_to_tab(char *, mot_occurences *);

/*
Fonction : pour enlever tous les espaces doubles d'une chaine de
caractères (passage par paramètre pour récupérer le tableau).
Paramètres : (1) nom du fichier. (2) passage par paramètre du path.
Renvoie : rien (void).
*/
void name_to_path_descripteurs(char *, char *);

/*
Fonction : pour rechercher un mot dans les fichiers indéxés.
Paramètres : (1) passage par paramètre d'un tableau de fre_mot_texte.
(2) mot recherché.
Renvoie : le nombre d'objets dans le tableau de freq_mot_texte.
*/
int recherche(freq_mot_texte *, char *);

/*
Fonction : pour trier par ordre décroissant un tableau de freq_mot_texte.
Paramètres : (1) passage par paramètres du tableau de freq_mot_texte.
(2) nombre d'objets dans freq_mot_texte.
Renvoie : rien (void).
*/
void tri_frequences(freq_mot_texte *, int);

#endif