#ifndef MENU_H
#define MENU_H

/*Prototypes des fonctions*/

/*Fonctions de menus*/
void menuUtilisateur();
void menuAdministrateur();
void menuIndexation();
void menuIndexationTexte();
void menuRecherche();
void menuComparaison();
void menuRechercheTexte();

/*Affichage de menus*/
void afficheMenuPrincipal(); /*Affiche le menu principal*/
void afficheMenuUtilisateur(); /*Affiche le menu utilisateur*/
void afficheMenuAdministrateur(); /* Affiche le menu administrateur*/
void afficheMenuIndexation(); /*Affiche le menu d'indexation*/
void afficheMenuIndexationTexte(); /*Affiche le menu d'indexation texte*/
void afficheMenuRecherche(); /*Affiche le menu de recherche*/
void afficheMenuComparaison(); /*Affiche le menu de comparaison*/
void afficheMenuRechercheTexte(); /*Affiche le menu de recherche texte*/

//Définition du type booléen
typedef enum { false = 0, true = 1}bool;

#endif