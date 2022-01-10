//Fonction supprimant les mots de 2 caractères ou moins
int supprimer_mots_courts(char *chaine) //Problème si le premier mot est à supprimer
{
    int index = 0;
    int i = 0;
    int count = 0;
    char caractere_actuel = chaine[0];

    while (caractere_actuel != '\0') //Tant qu'on est pas à la fin de la chaine
    {
        caractere_actuel = chaine[index];
        count++;                     //On incrémente le compteur de lettres
        if (caractere_actuel == ' ') //lorsqu'on rencontre un espace
        {
            if (count <= 4) // si le mot possède au plus 2 caractères (3 parce qu'on compte l'espace qui succède)
            {

                for (i = index; i < strlen(chaine) - count; i++) //On décale tout la chaine de la taille du mot rencontré
                {
                    chaine[i - count + 1] = chaine[i + 1]; //[i - count -1] crée une segmentation fault
                }
                chaine[strlen(chaine) - count] = '\0';
                index = index - count; //on remet l'index juste après où on vient de décaler
            }

            count = 0; //On remet le compteur de lettres du mot courant à 0
        }

        index++; //On passe au caractère suivant
    }

    return strlen(chaine); //renvoie la longueur de la chaine
}