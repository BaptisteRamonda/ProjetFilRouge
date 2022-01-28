/*  AUTEUR :    SAURAT DORIAN                                                                               */
/*                                                                                                          */
/*  NOM :   indexation_image.sh                                                                             */
/*                                                                                                          */
/*  Fonction :  Ce script a pour but de réaliser l'indexation de la totalité des fichiers texte du dossier  */
/*              TEST_IMAGE par l'appel successif pour chacun des noms de fichiers de l'axécutable de        */
/*              l'indexation                                                                                */


#!/bin/sh
echo $(pwd)
ls ../../documents/image/TEST_IMAGE/ |grep -v .[jpg] |grep -v .[bmp]>../../documents/image/liste_noms_images/liste_noms_images.txt
input="../../documents/image/liste_noms_images/liste_noms_images.txt"
gcc  indexation_image.c -o indexation_image.out
rm ../../documents/image/descripteurs/base_descripteur_image.txt
while IFS= read -r line;
do
    ./indexation_image.out $line
done<"../../documents/image/liste_noms_images/liste_noms_images.txt"
