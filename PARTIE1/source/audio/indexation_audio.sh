#!/bin/sh
gcc -c div_fenetre.c -g
gcc -c indexation_audio.c -g
gcc -c file_dynamique.c -g
gcc -c element_P2.c -g
gcc -o indexation_audio.out  div_fenetre.o indexation_audio.o file_dynamique.o element_P2.o
rm ../../documents/audio/*.txt
rm -rf *.o
./indexation_audio.out