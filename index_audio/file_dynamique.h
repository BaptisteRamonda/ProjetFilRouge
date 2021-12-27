#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "element_P2.h"

typedef struct cel{
	ELEMENT element;
	struct cel* suiv;
} cellule;
typedef struct FILE{
		cellule * tete;
		cellule * queue;
} MA_FILE;


MA_FILE INIT_FILE();
void AFFICHE_FILE(MA_FILE f);
int FILE_EST_VIDE(MA_FILE f);
MA_FILE ENFILER(MA_FILE f,  ELEMENT e);
MA_FILE DEFILER(MA_FILE f, ELEMENT * e);
MA_FILE SAISIR_FILE();
