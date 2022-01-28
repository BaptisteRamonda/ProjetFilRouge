#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../headers/id.h"

/*Gestion connexion au menu administrateur*/
void verifLogin(char pro[], char user[]){
    while (strcmp(pro,user) != 0){
        system("clear");
        printf("Login : ");
        scanf("%s", user);
    }
}

void verifPassword(char pro[], char user[]){
    while (strcmp(pro,user) != 0){
        printf("Mot de Passe : ");
        scanf("%s", user);   
        system("clear");
    }
}

int read(char* passlog, int longueur ,FILE* fichier){
    char *start = NULL;
    if (fgets(passlog, longueur, fichier) != NULL){
        start = strchr(passlog, '\n');
        /*On remplace le retour à la ligne*/
        if (start != NULL){
            *start = '\0'; 
        }
        else
        	fflush(stdin);
        return 1;
    }
    else {
    	fflush(stdin);
        return 0;
    }
}

void initialiseId(char* log, char* pw){
    FILE* fichierLog = fopen("identifiers/adminLog.txt","r");
    FILE* fichierPw = fopen("identifiers/adminPw.txt","r");

    if (fichierLog != NULL){
        read(log, 30, fichierLog);
        fclose(fichierLog);
    }
    if (fichierPw != NULL){
        read(pw, 30, fichierPw);
        fclose(fichierPw);
    }
}