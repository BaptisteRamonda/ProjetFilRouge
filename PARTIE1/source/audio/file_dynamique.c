#include <stdio.h>
#include "../../headers/audio/file_dynamique.h"

MA_FILE INIT_FILE ()
{	
	MA_FILE f;
	f.tete =NULL;
	f.queue =NULL;
	return f;
}

void AFFICHE_FILE(MA_FILE f) {

	cellule * tmp ;
	tmp = f.tete;
	if(!(FILE_EST_VIDE(f))){
		while (tmp != NULL) {
			affiche_ELEMENT( tmp->element);
			tmp = tmp->suiv;
		}
	}
	else printf("Votre file est vide \n");
}
int FILE_EST_VIDE(MA_FILE f){
	int p = 0;
	if(f.queue == NULL && f.tete == NULL){p=1;}
	return p;
}

MA_FILE ENFILER (MA_FILE f,ELEMENT e){
	cellule *cel = (cellule *)malloc(sizeof(cellule));
	if(cel != NULL){
	cel->element = e;
	if(FILE_EST_VIDE(f)){
		f.tete = cel;
		f.queue = cel;
		cel->suiv=NULL;
	}
	else {
		f.queue->suiv = cel;
		f.queue = cel;
		cel->suiv=NULL;
	}
    }
    return f;	
}
MA_FILE DEFILER (MA_FILE f,ELEMENT *e){
	if(FILE_EST_VIDE(f)){ printf ("Votre pile est vide \n");}
	else if(f.tete == f.queue && f.queue!= NULL){ 	
		cellule * tmp ;
		tmp = f.tete;
		*e = tmp->element;
		free(tmp);
		f.tete = NULL;
		f.queue = NULL;
		}
	else {
		cellule * tmp ;
		tmp = f.tete;
		*e = tmp->element;
		f.tete = tmp->suiv;
		free(tmp);
		}
		return f;	
}

MA_FILE SAISIR_FILE(){
	MA_FILE f;
	f = INIT_FILE();
	int n,i;
	printf ("Donner le nombre d'element de votre file : \n");
	scanf("%d",&n);
	for (i=0;i<n;i++){
		printf("Donner l'element n° %d \n",i);
		f=ENFILER(f,(ELEMENT)saisir_ELEMENT());
		
		}
	return f;
}