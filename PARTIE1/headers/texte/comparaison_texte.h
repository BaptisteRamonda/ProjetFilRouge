#ifndef __COMPARAISON_TEXTE_H__
#define __COMPARAISON_TEXTE_H__

int file_to_tab(char *, mot_occurences *);
void name_to_path_descripteurs(char *, char *);
int comparison(comp_textes *, mot_occurences *, int);
#endif