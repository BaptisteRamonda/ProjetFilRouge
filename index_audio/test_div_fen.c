#include "div_fenetre.h"




void main(void){
// Fonction main qui permet d'executer le programme concernant la partie audio

    FILE *fic;
    int config[2]; // Tableau qui contient les parametres de configuration
    char *t;
    size_t len;
    fic = fopen("Audio.config","r"); // Ouverture du fichier .config dans lequel l'admin peut changer les valeurs de n(le nombre d'echantillons de chaque fenetre d'analyse) et de m(nbre d'intervalle pour chaque histogramme)
    int i =0;
    while(getline(&t,&len,fic)!=-1 && i<2){
        sscanf(t,"%d",&config[i]);
        i++;
    } //Lecture du fichier .config
    int n = config[0], m = config[1];
    fclose(fic);
    remove("liste_base_audio.txt"); 
    remove("base_descripteur_audio.txt");
    //Ces deux fonctions remove au debut permet de supprimer les deux fonctions dont les noms sont en parametre . Cette suppression sert a garder une certaine sécuruité (renitialiser tous les fichier creer a l'issu de l'indexation automatique si on vien a redémarer le programme depuis le début )
    //Dans le cas contraire l'indexation ne poura pas se faire ainsi que la vérification au niveau du fichier liste_base_audio
     
     // Ce qui suit sert juste a tester l'indexation automatique  et la recheche du jingle
     Descrip * base_descript_audio = NULL; //Tableau qui va contenir la liste des descripteurs
     int nbr_descripteur = 0;
     float secondes ;
     base_descript_audio = indexation_automatique( base_descript_audio, &nbr_descripteur,n,m);
     secondes = recherche_jingle( base_descript_audio[0] ,base_descript_audio[1], n, m); // Recherche de la seconde a laquelle le jingle apparait
     printf("\n%f\n",secondes);
     char buf[10];
     gcvt(secondes,4,buf);
     char cmd[] = "mplayer -ss ";
     strcat(cmd,buf);
     strcat(cmd," ");
     char chem[BUFSIZ];
     char commande[BUFSIZ];
     strcpy(commande,cmd);
     strcpy(chem,base_descript_audio[0].identifiant);
     int taillec = strlen(base_descript_audio[0].identifiant);
     chem[taillec-3]='w';
     chem[taillec-2]='a';
     chem[taillec-1]='v';
     strcat(commande,chem);
     system(commande);
     printf("%s\n",commande);
    // Les lignes de code qui viennent de suivre servent a ecrire la commande permettant d ecouter le corpus a partir du moment auquelle le jingle apparait
    
     char chemin[BUFSIZ];
     strcpy(chemin,base_descript_audio[1].identifiant);
     int taille = strlen(base_descript_audio[1].identifiant);
     chemin[taille-3]='w';
     chemin[taille-2]='a';
     chemin[taille-1]='v';
       
     char cmdj[] = "mplayer ";
     strcat(cmdj,chemin);
     printf("%s\n",cmdj);  
     system(cmdj);
     //Ces lignes servent a jouer le jingle .
     base_descript_audio = indexation_automatique( base_descript_audio, &nbr_descripteur,n,m);
     //base_descript_audio = indexation_automatique( base_descript_audio, &nbr_descripteur,n,m);

}
