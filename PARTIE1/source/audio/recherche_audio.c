#include <stdio.h>
#include <stdlib.h>
#include "../../headers/audio/div_fenetre.h"

void main(){
// Fonction main qui permet d'executer le programme concernant la partie audio

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
  
     Descrip * descrip_jingle;
     int nb_jingle =0;
     if(descrip_jingle==NULL){
        descrip_jingle= (Descrip * )malloc(sizeof(Descrip)*20); //Allocation dynamique du tableau qui va recueillir tous les descripteurs des jingles deja indexés
    if(descrip_jingle==NULL){
      perror("Allocation failed");
      exit(1);
    }
  }
     Descrip * descrip_corpus;
     int nb_corpus =0;
      if(descrip_corpus==NULL){
        descrip_corpus= (Descrip * )malloc(sizeof(Descrip)*20); //Allocation dynamique du tableau qui va recueillir tous les descripteurs des corpus deja indexés
    if(descrip_corpus==NULL){
      perror("Allocation failed");
      exit(1);
    }
    }
     char identity[BUFSIZ];
     int indice_caractere;
     for(int a=0; a<nbr_descripteur; a++){
         strcpy(identity,base_descript_audio[a].identifiant);
         for(int o = 0; o<strlen(identity); o++){
             if (identity[o] == '/'){
                indice_caractere = o;
             }
         }
         if (identity[indice_caractere + 1] == 'j'){ 
             descrip_jingle[nb_jingle] = base_descript_audio[a];
             nb_jingle ++ ;
         }
         else {
             descrip_corpus[nb_corpus] = base_descript_audio[a];
             nb_corpus++;
             }
     }
    printf("Listes de jingles disponibles dans la base de donnees audio \n");
    for(int i = 0;i<nb_jingle;i++){
        printf("%d- %s \n",i+1,descrip_jingle[i].identifiant);
    }
    printf("\nDonner le numero du jingle que vous voulez recherchez : ");
    int num_jingle ;
    scanf("%d",&num_jingle);
    char commande[BUFSIZ];
    char cmdj[] = "mplayer ";
    for(int i = 0;i<nb_corpus;i++){
        secondes[i] = recherche_jingle( descrip_corpus[i] ,descrip_jingle[num_jingle-1], n, m);
        if(secondes[i] != -1){
            printf("\nLe jingle se trouve dans %s et y apparait a %.2fs.\n",descrip_corpus[i].identifiant,secondes[i]);
            char buf[10];
            gcvt(secondes[i],4,buf);
            char cmd[] = "mplayer -ss ";
            strcat(cmd,buf);
            strcat(cmd," ");
            char chem[BUFSIZ];
            
            strcpy(commande,cmd);
            strcpy(chem,descrip_corpus[i].identifiant);
            int taillec = strlen(descrip_corpus[i].identifiant);
            chem[taillec-3]='w';
            chem[taillec-2]='a';
            chem[taillec-1]='v';
            strcat(commande,chem);
            
           
            // Les lignes de code qui viennent de suivre servent a ecrire la commande permettant d ecouter le corpus a partir du moment auquelle le jingle apparait
            
            char chemin[BUFSIZ];
            strcpy(chemin,descrip_jingle[num_jingle-1].identifiant);
            int taille = strlen(descrip_jingle[num_jingle-1].identifiant);
            chemin[taille-3]='w';
            chemin[taille-2]='a';
            chemin[taille-1]='v';
            strcat(cmdj,chemin);
            
            //Ces lignes servent a ecrire la commande pour jouer le jingle .
             }

        else{
            printf("Le jingle ne se trouve pas dans %s.\n",descrip_corpus[i].identifiant);
            }
    }
     printf("Pour lancer le lecteur tapez 1 sinon tapez un autre chiffre \n");
     int key;
    scanf("%d",&key);
    if(key == 1){ 
        system(cmdj);
        system(commande); 
    }

  

}
