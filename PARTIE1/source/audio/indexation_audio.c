#include <stdio.h>
#include <stdlib.h>
#include "../../headers/audio/div_fenetre.h"

int main(){
    FILE *fic;
    int config[2]; // Tableau qui contient les parametres de configuration
    char *t;
    size_t len;
    fic = fopen("../../config/Audio.config","r"); // Ouverture du fichier .config dans lequel l'admin peut changer les valeurs de n(le nombre d'echantillons de chaque fenetre d'analyse) et de m(nbre d'intervalle pour chaque histogramme)
    int i =0;
    while(getline(&t,&len,fic)!=-1 && i<2){
        sscanf(t,"%d",&config[i]);
        i++;
    } //Lecture du fichier .config
    int n = config[0], m = config[1];
    fclose(fic);
    
     // Ce qui suit sert juste a tester l'indexation automatique  et la recheche du jingle
     Descrip * base_descript_audio = NULL; //Tableau qui va contenir la liste des descripteurs
     int  nbr_descripteur= 0;
     float secondes[20] ;
     base_descript_audio = indexation_automatique( base_descript_audio, &nbr_descripteur,n,m);
     printf("Indexation terminer\n");
     return 0;
}
