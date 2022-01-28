#include <stdio.h>
#include <stdlib.h>
#include "../headers/menu.h"
#include "../headers/id.h"

int main(){
    char etat = '0';
    bool exit = false;
    initialiseId(loginAdmin, passwordAdmin);

    while(exit == false){
        switch (etat)
        {
        case '0':
            system("clear");
            afficheMenuPrincipal();
            scanf("%c",&etat);
            fflush(stdout);
            break;
        
        case '1':
            system("clear");
            etat = 0;
            menuUtilisateur();
            break;
        
        case '2':
            system("clear");
            /*Accessibilité menu admin*/
            verifLogin(loginAdmin, loginUser);
            verifPassword(passwordAdmin, passwordUser);
            etat=0;
            menuAdministrateur();
            break;

        case '3':
            exit = true;
            break;

        default:
            etat = '0';
            break;
        }
    }
    system("clear");
    return 0;
}