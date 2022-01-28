#ifndef DIV_FENETRE_H
#define DIV_FENETRE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_dynamique.h"

typedef struct descripteur_audio{
  int ** histo ;
  long k;
  char *identifiant;
} Descrip;

MA_FILE * Creation_fenetre_analyses(const char *nomfichier,long n,long *d);
MA_FILE * Creation_hist_analyses(const char *nomfichier,long n,int m,long *nbre_hist_analyse);
Descrip Creation_descripteur_audio(const char *nomfichier,long *k,long n,int m);
float recherche_jingle(Descrip corpus , Descrip jingle,int n,int m);
Descrip * indexation_automatique(Descrip * base_descript_audio,int *nbr_descripteur,int n ,int m);
#endif