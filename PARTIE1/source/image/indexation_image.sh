# #!/bin/sh
# echo $(pwd)
# ls ../../documents/image/TEST_IMAGE/ |grep -v .[jpg]>../../documents/image/liste_noms_images_RGB/temp.txt
# sed '$d' ../../documents/image/liste_noms_images_RGB/temp.txt > ../../documents/image/liste_noms_images_RGB/liste_noms_images.txt
# input="../../documents/image/liste_noms_images_RGB/liste_noms_images.txt"
# gcc indexation_image.c -o indexation_image.out
# rm ../../documents/image/descripteurs/base_descripteur_image.txt
# while IFS= read -r line;
# do
#     ./indexation_image.out $line
# done<"../../documents/image/liste_noms_images_RGB/liste_noms_images.txt"
# rm ../../documents/image/liste_noms_images_RGB/temp.txt


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