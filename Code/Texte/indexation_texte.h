#ifndef __INDEXATION_TEXTE_H__
#define __INDEXATION_TEXTE_H__

/*
Fonction : pour enlever tous les espaces doubles d'une chaine de
caractères (passage par paramètre pour récupérer le tableau).
Paramètres : la chaine de caractères où enlever les espaces.
Renvoie : le nombre de caractères de la chaine après traitement.
*/
int enlever_espaces_doubles(char *);

/*
Fonction : pour enlever tous les espaces au début d'une chaine de 
caractères (passage par paramètre pour récupérer le tableau).
Paramètres : la chaine de caractères où enlever les espaces.
Renvoie : le nombre de caractères de la chaine après traitement.
*/
int enlever_espaces_debut(char *);

/*
Fonction : pour enlever tous les tab au début d'une chaine de 
caractères (passage par paramètre pour récupérer le tableau).
Paramètres : la chaine de caractères où enlever les espaces.
Renvoie : le nombre de caractères de la chaine après traitement.
*/
int enlever_tab_debut(char *);

/*
Fonction : pour supprimer toutes les occurences d'une chaine de
caractères dans une autre.(passage par paramètre pour récupérer
le tableau)
Paramètres : (1) la chaine de caractères où enlever les occurences.
(2) la chaine de caractères à enlever. (3) La taille de la chaine 
de caractères départ
Renvoie : le nombre de caractères de la chaine après traitement.
*/
int supprimer_occurences(char *, char *, int);

/*Fonction : calcule le nombre de caractères d'une chaine de 
caractères.
Paramètres : la chaine de caractères à décompter.
Renvoie : le nombre de caractères de la chaine.
*/
int nombre_caracteres(char *);

/*
Fonction : supprimer les mots inutiles (listés dans un txt).
Paramètres : la chaine où supprimer les mots inutiles.
Renvoie : le nombre de caractères de la chaine après traitement.
*/
int supprimer_mots_inutiles(char *);

/*
Fonction : écrit dans un fichier du même type que celui donné (ici
.xml) sur une ligne le mot suivi d'un espace puis de son nombre d'occurences.
Paramètres : chaîne de caractères correspondant au nom du fichier
Renvoie : rien, écrit dans le fichier
*/
void indexation(char *);

#endif
