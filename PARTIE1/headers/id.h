#ifndef ID_H
#define ID_H

/*Initialisation des identifiants admin*/
char loginAdmin[50];
char passwordAdmin[50];
char loginUser[50];
char passwordUser[50];

/*Gestion identifiants administrateur*/
void verifLogin(char pro[], char user[]); /*Vérifie le login*/
void verifPassword(char pro[], char user[]); /*Vérifie le mot de passe*/
void initialiseId(char* log, char* pw); /*Initialise les identifiants administrateur*/
int read(char* passlog, int longueur ,FILE* fichier); /*Lit dans un fichier*/

#endif