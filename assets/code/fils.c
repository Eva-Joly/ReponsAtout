#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<fcntl.h>
#include <string.h>
#include <stdio.h>

int lire(char*chaine, int longueur);

int main(int argc, char *arg[])
{
    int dp;
    char commande[100];
    char *buff[100];

    printf("tapez votre commande :\n");
    lire(commande,100);

    sleep(8);
    dp=open(arg[0],O_WRONLY);
    write(dp, commande,100) ;
  
    close(dp);

  exit(0);
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

