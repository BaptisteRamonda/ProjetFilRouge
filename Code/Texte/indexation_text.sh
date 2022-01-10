#!/bin/sh
echo $(pwd)
ls ../../Documents/Textes/Corpus>../../Documents/Textes/Liste_Noms_Textes/Liste_noms_textes.txt
intput="../../Documents/Textes/Liste_Noms_Textes/Liste_noms_textes.txt"
gcc  indexation_texte.c -o indexation_texte.out
while IFS= read -r line;
do
    text_file_path="../../Documents/Textes/Corpus/$line"
    text_file_path2="../../Documents/Textes/Textes_propres/$line"
    input_text_encoding=$(file -b --mime-encoding $text_file_path)
    #iconv -c -f iso-8859-1 -t UTF-8 $text_file_path > $text_file_path2
    #pb de non reconnaissance si on utilise input_text_encoding
    ./indexation_texte.out $line
done<"../../Documents/Textes/Liste_Noms_Textes/Liste_noms_textes.txt"

