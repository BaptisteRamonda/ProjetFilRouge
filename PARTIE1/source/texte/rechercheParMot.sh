#!/bin/sh
gcc -Wall recherche_texte.c -o recherche_texte.out
read -p "Entrez le mot de recherche : " mot
echo "\n"
./recherche_texte.out $mot