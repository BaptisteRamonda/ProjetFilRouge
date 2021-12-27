
#include "div_fenetre.h"

MA_FILE * Creation_fenetre_analyses(const char *nomfichier,long n,long *d) {
   //Cette fonction permet de faire la creation des fenetre d'analyse

  double point; // nombre de points dans chaque fenetre d'analyse.
  FILE *fichier = NULL; //ouverture du fichier.
  fichier = fopen(nomfichier,"rb");
  if(fichier == NULL){
    fprintf(stderr, "Erreur ouverture fichier\n");
    exit(EXIT_FAILURE);
  }
  
  fseek(fichier,0,SEEK_END);
  *d=ftell(fichier); // d recupere la taille du fichier binaire en octet
   // c permet de savoir le nombre de points que contient le fichier binaire on divise par 8 car tous les points qu'elle contient sont de type double codee sous 8 octets.
  fseek(fichier,0,SEEK_SET);
  *d=*d/(8*n);
   // recupere maintenant le nombre de fenetre d'analyse a cree

  
  MA_FILE *tab_fen; // un tableau de file qui sera renvoyer par cette fonction va contenir toutes les fenetres d'analyse.
  tab_fen=malloc((*d)*sizeof(MA_FILE));
  for(long i=0;i<*d;i++){
    tab_fen[i]=INIT_FILE(); //initialisation de chaque file.
    for(int j=0;j<n;j++){
      fread(&point,sizeof(double),1,fichier); // lecture du fichier binaire qui renvoie 1 a chaque fois qu'il lit un element du fichier ,
       //permet de calculer toutes les fois que le fread a lue une valeur.
      tab_fen[i] = ENFILER(tab_fen[i],point); // verifie si le nombre total de point lu n'est pas supperieur au nombre total de points.
      // enfile le dernier point puis s'arrete pour ne pas enfiler,plus qu'il ne faudrait
      }
    }
  
  fclose(fichier); // fermeture du fichier
  return tab_fen;
}
/*.................................................................*/
// Fonction Creation_hist_analyes(...) pour creer les histogrammes de chaque fenetre d'analyse.
// la variable nomfichier permet de recuperer le nom du fichier a traiter.

MA_FILE * Creation_hist_analyses(const char *nomfichier,long n,int m,long *nbre_hist_analyse){

  MA_FILE * ptr; // Creation d'un pointeur file pour recuperer les fenetres d'analyse.

//  long nbre_fen_ana; // pour recuperer le nombre de fenetre d'analyse qui sera apres le meme nombre d'histogrammes a creer.

  ptr=Creation_fenetre_analyses(nomfichier,n,nbre_hist_analyse); // Recuperation de l'ensemble des fenetre d'analyse;

  MA_FILE *tab_histo; // Creation d'un nouveau tableau de file pour stocker l'ensemble des histogrammes qui seront crees;
  tab_histo=malloc(*nbre_hist_analyse*sizeof(MA_FILE)); // Allocation dynamique pour pouvoir renvoyer le tableau par la fonction;

  cellule * tmp ; // Creation de cellule qui nous permettra de parcourir chaque échantillons de chaque fenetre d'analyse afin de faire les comparaisons;

  double compteur;// Qui va servir a compter le nombre d'échantillons qui respecte les m intervalles de l'histogramme;

    for(int i=0;i<*nbre_hist_analyse;i++){ // boucle pour parcourir toutes fenetre d'analyse et leur histogramme correspondant;

      tab_histo[i] = INIT_FILE(); // initialisation de chaque file nouvellement creer;
      /*bsup et binf sont respectivement la borne superieur et inferieur des m subdivisions de l'histogramme courant 'tab_histo[i]'.
      Subdivisions dans lesquelles la variable 'compteur' releve le nombre d'echatillons de la fenetre d'analyse courante 'ptr[i]'
      qui s'y trouve; */

      for(double bsup=-1+(2/(double)m),binf=-1;bsup<=1;binf = bsup,bsup +=(2/(double)m)){
      //'2/m' est le meme pas (distance) de chacune des m subdivisions entre -1 et 1;

        if(!(FILE_EST_VIDE(ptr[i]))){ // Parcours de chaque file et comparaison;

          tmp = ptr[i].tete;
            while (tmp != NULL) {
              if(tmp->element>=binf &&  tmp->element<bsup){compteur++;}
              tmp = tmp->suiv;
              }

        tab_histo[i] = ENFILER(tab_histo[i],compteur); // Enfillage du compteur;
        compteur=0; // reset du compteur pour la comparaison dans la prochaine subdivision
      }
    }
  }
  return tab_histo; // la fonction retourne l'ensemble des histogrammes creer;
}



Descrip Creation_descripteur_audio(const char *nomfichier,long *k,long n,int m){
  //Cette fonction permet de creer les descripteurs des fichiers audio dont les chemins on été passer en parametre.
  
  MA_FILE *ptr;
  ptr=Creation_hist_analyses(nomfichier,n,m,k); // Creation des histogrammes d'annalyse
  Descrip mon_descripteur;
  mon_descripteur.identifiant = nomfichier; // initialisation de l'identifiant du descripteur 
  mon_descripteur.k = *k; // nombre de ligne de l'histogramme du descripteur
  int **histogramme = (int**)malloc(*k*sizeof(int*)); // Allocation dynamique d'une matrice pour l'histogramme
  cellule * tmp ;
  for(int i=0;i<*k;i++){
    histogramme[i]=(int*) malloc(m*sizeof(int));
      if(!(FILE_EST_VIDE(ptr[i]))){ // Parcours de chaque file des histogrammes d'analyse et remplissage de l'histogramme du descripteur
        int j=0;
        tmp = ptr[i].tete;
          while (tmp != NULL) {
            histogramme[i][j] =(int)tmp->element;
            tmp = tmp->suiv;
            j++;
          }
    }
  }
  mon_descripteur.histo = histogramme; // Affectation de l'histogramme du descripteur
  FILE * fic;
  fic = fopen("base_descripteur_audio.txt","a"); // Ouverture du fichier pour base_descirpteur_audio.txt pour enregistrer les descripteurs crées.
  fprintf(fic, "%s\n",mon_descripteur.identifiant ); // Ecriture de l'identifiant dans le fichier


  for(int i=0;i<*k;i++){
    for(int j=0;j<m;j++){
      fprintf(fic,"%d\t",mon_descripteur.histo[i][j]); // Ecriture de l'histogramme
    }
    fprintf(fic,"\n");
   }
   fprintf(fic,"/*fin_%s*/\n",mon_descripteur.identifiant);
  fclose(fic);
  return mon_descripteur; // renvoi le descripteur créer
}

Descrip * indexation_automatique(Descrip * base_descript_audio,int *nbr_descripteur,int n ,int m){
  // Cette fonction permet de faire l'indexation automatique de tous les fichier audio qui sont dans la data base audio.
   
  if(base_descript_audio==NULL){
    base_descript_audio = (Descrip * )malloc(sizeof(Descrip)*20); //Allocation dynamique du tableau qui va recueillir tous les descripteurs des fichiers audios crées
    if(base_descript_audio==NULL){
      perror("Allocation failed");
      exit(1);
    }
  }
  FILE * fp; 
  FILE * f;
  f=fopen("liste_base_audio.txt","a+"); // Pour creer ou mettre a jour "liste_base_audio.txt" le fichier qui contient la liste des fichiers indexer
  //fp=fopen("audio_paths.txt","r"); //Ouvre le fichier contenant les chemins absolue qui doivent etre indexer
  fp = popen("find $PWD -type f -name \"*.bin\" > findresult ;grep Audio_data_base findresult","r");// Ces deux commandes servent a trouver les fichiers audio .bin dans "Audio_data_base"
  
  char *chaine; 
  size_t len =0;
  const char *tmp;
  while(getline(&chaine, &len,fp) != -1){   //Pour lire les chemins absolues trouver au niveau du pipe
    
    long kl;
    chaine[strlen(chaine)-1]='\0'; //Elimination du caractere "\n"; 
    
    const char * chains = chaine;
    
   if(*nbr_descripteur > 0){
      
      int p=0;
      char * line ;
      size_t length;
      fseek(f,0,SEEK_SET);
      while(getline(&line, &length,f) != -1){ //Lecture du fichier audio_data_base.txt
        line[strlen(line)-1]='\0';
        if(strcmp(chains,line) == 0){
          p = 1 ;
        } //Cette partie consiste a vérifier si le fichier dont le chemin a été lu a déja été indexer. Et cette verification se fait en lisant les fichiers deja indexer dans liste_base_audio.txt

      }
      if(p==0){
        base_descript_audio[*nbr_descripteur]=Creation_descripteur_audio(chains,&kl,n,m);
        fprintf(f,"%s\n",base_descript_audio[*nbr_descripteur].identifiant); // Mise a jour de liste_base_audio
        *nbr_descripteur +=1;
      } //indexation du fichier correspondant.
    }
    else{
      
      base_descript_audio[*nbr_descripteur]=Creation_descripteur_audio(chains,&kl,n,m);//indexation du fichier correspondant
      fprintf(f,"%s\n",base_descript_audio[*nbr_descripteur].identifiant);// Mise a jour de liste_base_audio
      *nbr_descripteur +=1; //Mise a jour du nombre de descripteur creer 
      
      }
  }
  char *fline;
  size_t l;
  getline(&fline, &l,f);
  //fline[strlen(fline)-1]='\0';
  base_descript_audio[0].identifiant = fline;
  fclose(f);
  pclose(fp);
  return base_descript_audio;
}
float recherche_jingle(Descrip corpus , Descrip jingle,int n,int m){
//Cette fonction permet de trouver a partir de quel seconde le jingle apparait dans le corpus 

    long Kc = corpus.k;  // Recuperation du nombre de ligne de l'histogramme du corpus
    long Kj = jingle.k; // Recuperation du nombre de ligne de l'histogramme du jingle
    // Nous avons prefere utiliser ces variable pour alleger les expression dans le programme
    int c=0;
    int debut = 0; // Cette variable va permettre a déplacer la ou commence la lecture de l'histogramme du corpus 
    int  dist_manha[Kc]; // Ce tableau va récupérer l'ensemble des distances de manhatan calculer au cour de la recherche  
    int compteur =0; // compteur du tableau
    while( debut + Kj < Kc  ){
         for(int i=0,lig = debut ;i<Kj;i++,lig++){ 
             for(int j=0;j<m;j++){
              c= c +abs(jingle.histo[i][j]-corpus.histo[lig][j]);
             }
         }
         dist_manha[compteur] = c; // Stockage des distances calculer
         compteur++;
         debut ++;
         c=0;
    } // permet de calculer les distances de manhatan 
    int min = dist_manha[0];
    int indice_min=0;
    for(int l=0;l<compteur;l++){
        if(dist_manha[l]<min){
            min = dist_manha[l];
            indice_min=l;
        } // Permet de trouver le minimum parmis les distances calculées
    }
    float nbre_seconde;
    nbre_seconde = (n/(float)16000)*(indice_min+1); // permet de trouver la seconde a la quelle le jingle apparait dans le corpus.
    
    return nbre_seconde;
}