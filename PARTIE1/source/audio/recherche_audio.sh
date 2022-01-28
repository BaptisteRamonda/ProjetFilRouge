#!/bin/sh
gcc -c div_fenetre.c -g
gcc -c recherche_audio.c -g
gcc -c file_dynamique.c -g
gcc -c element_P2.c -g
gcc -o recherche_audio.out  div_fenetre.o recherche_audio.o file_dynamique.o element_P2.o
rm ../../documents/audio/*.txt
rm -rf *.o
./recherche_audio.out