#include <stdio.h>
#include "../../headers/audio/element_P2.h"

void affiche_ELEMENT(ELEMENT e)
{
	printf("%lf \n",e);
}

ELEMENT saisir_ELEMENT()
{
	ELEMENT e;
	scanf("%lf",&e);
	return e;
}

ELEMENT affect_ELEMENT(double valeur) // la valeur pris en parametre est affecter a l'element.
{
	ELEMENT e;
	e = valeur;
	return e;
}

void compare_ELEMENT(ELEMENT e1, ELEMENT e2){
  if (e1==e2) printf("OK IDENTIQUES \n\n");
  else printf("NOK DIFFERENTS \n\n");
}
