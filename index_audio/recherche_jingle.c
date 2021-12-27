#include "div_fenetre.h"

void recherche_jingle(Descrip jingle, Descrip corpus){
    int c=0;
    int debut = 0;
    int  dist_manha[Kc/(kj+5)+1];
    int compteur =0;
    while( debut + kj < Kc ){
         for(int i=0,lig = debut ;i<kj;i++,lig++){
        

             for(int j=0,col=0;j<m;j++,col++){
            c= c +abs(jingle.histo[i][j]-corpus[lig][col]);
             }
         }
         dist_manha[compteur] = c;
         compteur++;
         debut += 5;
    }
    int min = dist_manha[0];
    int indice_min=0;
    for(int l=0;l<compteur+1;l++){
        if(dist_manha[l]<min){
            min = dist_manha[l];
            indice_min=l;
        }
    }
    int nbre_seconde;
    nbre_seconde = (16000/n)*(Kj*(indice_min+1)+5*indice_min);


}