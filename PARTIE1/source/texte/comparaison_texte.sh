#!/bin/sh
gcc -Wall recherche_texte.c -o recherche_texte.out
read -p "TAPER LE NOM DU FICHIER A OUVRIR:" mot
echo "\n"
./comparaison_texte.out $mot