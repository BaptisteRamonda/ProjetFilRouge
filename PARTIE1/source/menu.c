#include <stdio.h>
#include <stdlib.h>
#include "../headers/menu.h"
#include "../headers/texte/recherche_texte.h"
#include "../headers/texte/comparaison_texte.h"

/*Affichage des menus*/
void afficheMenuPrincipal()
{
    printf("\n-------------------- MENU PRINCIPAL ---------------------\n");
    printf("|                                                       |\n");
    printf("|                   [1] - UTILISATEUR                   |\n");
    printf("|                   [2] - ADMINISTRATEUR                |\n");
    printf("|                   [3] - QUITTER                       |\n");
    printf("|                                                       |\n");
    printf("|                                                       |\n");
    printf("---------------------------------------------------------\n");
    printf("\nQuel est votre profil: ");
}

void afficheMenuUtilisateur()
{
    printf("\n------------------- MENU UTILISATEUR --------------------\n");
    printf("|                                                       |\n");
    printf("|                    [1] - RECHERCHER                   |\n");
    printf("|                    [2] - RETOUR                       |\n");
    printf("|                                                       |\n");
    printf("|                                                       |\n");
    printf("|                                                       |\n");
    printf("---------------------------------------------------------\n");
    printf("\nQue souhaitez-vous faire: ");
}

void afficheMenuAdministrateur()
{
    printf("\n----------------- MENU ADMINISTRATEUR -------------------\n");
    printf("|                                                       |\n");
    printf("|                   [1] - INDEXER                       |\n");
    printf("|                   [2] - CONFIG. INDEX.                |\n");
    printf("|                   [3] - RETOUR                        |\n");
    printf("|                                                       |\n");
    printf("|                                                       |\n");
    printf("---------------------------------------------------------\n");
    printf("\nQue souhaitez-vous faire: ");
}

void afficheMenuIndexation()
{
    printf("\n-------------------- MENU INDEXATION --------------------\n");
    printf("|                                                       |\n");
    printf("|                      [1] - AUDIO                      |\n");
    printf("|                      [2] - IMAGE                      |\n");
    printf("|                      [3] - TEXTE                      |\n");
    printf("|                      [4] - RETOUR                     |\n");
    printf("|                                                       |\n");
    printf("---------------------------------------------------------\n");
    printf("\nQuel type de document souhaitez-vous indexer: ");
}

void afficheMenuRecherche()
{
    printf("\n--------------------- MENU RECHERCHE --------------------\n");
    printf("|                                                       |\n");
    printf("|                      [1] - AUDIO                      |\n");
    printf("|                      [2] - IMAGE                      |\n");
    printf("|                      [3] - TEXTE                      |\n");
    printf("|                      [4] - RETOUR                     |\n");
    printf("|                                                       |\n");
    printf("---------------------------------------------------------\n");
    printf("\nQuel type de document souhaitez-vous rechercher: ");
}

void afficheMenuComparaison()
{
    printf("\n-------------------- MENU COMPARAISON -------------------\n");
    printf("|                                                       |\n");
    printf("|                      [1] - AUDIO                      |\n");
    printf("|                      [2] - IMAGE                      |\n");
    printf("|                      [3] - TEXTE                      |\n");
    printf("|                      [4] - RETOUR                     |\n");
    printf("|                                                       |\n");
    printf("---------------------------------------------------------\n");
    printf("\nQuel type de document souhaitez-vous comparer: ");
}

void afficheMenuRechercheTexte()
{
    printf("\n----------------- MENU RECHERCHE TEXTE ------------------\n");
    printf("|                                                       |\n");
    printf("|                   [1] - PAR MOT-CLE                   |\n");
    printf("|                   [2] - PAR FICHIER                   |\n");
    printf("|                   [3] - RETOUR                        |\n");
    printf("|                                                       |\n");
    printf("|                                                       |\n");
    printf("---------------------------------------------------------\n");
    printf("\nComment souhaitez-vous effectuer cette recherche: ");
}

void afficheMenuIndexationTexte()
{
    printf("\n----------------- MENU INDEXATION TEXTE -----------------\n");
    printf("|                                                       |\n");
    printf("|                   [1] - INDEX. TOTALE                 |\n");
    printf("|                   [2] - INDEX. NOUVEAUX DOC.          |\n");
    printf("|                   [3] - RETOUR                        |\n");
    printf("|                                                       |\n");
    printf("|                                                       |\n");
    printf("---------------------------------------------------------\n");
    printf("\nQue souhaitez-vous indexer: ");
}

/*Fonctions de menus*/
void menuAdministrateur()
{
    char etat;
    afficheMenuAdministrateur();
    scanf("%c", &etat);
    fflush(stdout);
    switch (etat)
    {
    case '1':
        system("clear");
        menuIndexation();
        break;

    case '2':
        /*TODO: configIndex()*/
        break;

    case '3':
        break;

    default:
        system("clear");
        menuAdministrateur();
        break;
    }
}

void menuUtilisateur()
{
    char etat;
    afficheMenuUtilisateur();
    scanf("%c", &etat);
    fflush(stdout);
    switch (etat)
    {
    case '1':
        system("clear");
        menuRecherche();
        break;

    case '2':
        break;

    default:
        system("clear");
        menuUtilisateur();
        break;
    }
}

void menuIndexation()
{
    char etat;
    afficheMenuIndexation();
    scanf("%c", &etat);
    fflush(stdout);
    switch (etat)
    {
    case '1':
        system("cd source/audio/; bash indexation_audio.sh; cd ../..");
        break;

    case '2':
        system("cd source/image; bash indexation_image.sh; cd ../..");
        break;

    case '3':
        menuIndexationTexte();
        break;

    case '4':
        menuAdministrateur();
        break;

    default:
        system("clear");
        menuIndexation();
        break;
    }
}

void menuIndexationTexte()
{   
    char etat;
    afficheMenuIndexationTexte();
    scanf("%c", &etat);
    fflush(stdout);
    switch (etat)
    {
    case '1':
        system("cd source/texte; ./indexation_texte.sh; cd ../..");
        break;

    case '2':
        system("cd source/texte; ./indexation_solo.sh; cd ../..");
        break;

    case '3':
        menuIndexation();
        break;

    default:
        system("clear");
        menuIndexationTexte();
        break;
    }
}

void menuRecherche()
{
    char etat;
    int exit =0;
    afficheMenuRecherche();
    scanf("%c", &etat);
    fflush(stdout);
    switch (etat)
    {
    case '1':
        system("cd source/audio; ./recherche_audio.sh; cd ../..");
        printf("\nSAISIR UN NOMBRE POUR CONTINUER:");
        while (exit == 0)
        {
            scanf("%d", &exit);
        }
        break;
        break;

    case '2':
        break;

    case '3':
        system("clear");
        menuRechercheTexte();
        break;

    case '4':
        menuUtilisateur();
        break;

    default:
        system("clear");
        menuRecherche();
        break;
    }
}

void menuRechercheTexte()
{
    char etat;
    int exit = 0;
    afficheMenuRechercheTexte();
    scanf("%c", &etat);
    fflush(stdout);
    switch (etat)
    {
    case '1':
        system("cd source/texte; ./rechercheParMot.sh; cd ../..");
        printf("\nSAISIR UN NOMBRE POUR CONTINUER:");
        while (exit == 0)
        {
            scanf("%d", &exit);
        }
        break;

    case '2':;
        system("cd documents/texte/corpus; ls; cd ../../..");
        system("cd source/texte; ./comparaison_texte.sh; cd ../..");
        printf("\nSAISIR UN NOMBRE POUR CONTINUER:");
        while (exit == 0)
        {
            scanf("%d", &exit);
        }
        break;

    case '3':
        menuRecherche();
        break;

    default:
        system("clear");
        menuRechercheTexte();
        break;
    }
}