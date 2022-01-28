#!/bin/sh
echo $(pwd)
ls ../../documents/texte/corpus>../../documents/texte/liste_noms_textes/liste_noms_textes.txt
input="../../documents/texte/liste_noms_textes/liste_noms_textes.txt"
gcc  indexation_texte.c -o indexation_texte.out
while IFS= read -r line;
do
    text_file_path="../../documents/texte/corpus/$line"
    text_file_path2="../../documents/texte/textes_propres/$line"
    input_text_encoding=$(file -b --mime-encoding $text_file_path)
    iconv -c -f iso-8859-1 -t UTF-8 $text_file_path > $text_file_path2
    #pb de non reconnaissance si on utilise input_text_encoding, sinon utiliser $input_text_encoding
    ./indexation_texte.out $line
done<"../../documents/texte/liste_noms_textes/liste_noms_textes.txt"