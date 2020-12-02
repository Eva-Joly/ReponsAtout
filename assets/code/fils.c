#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<fcntl.h>
#include<string.h>
#include <string.h>
#include <stdio.h>

//int lire(char*chaine, int longueur);


int main(int argc, char *arg[])
{
    int dp;
    char choix;
    char question[250];
    char Cpid[5];
    char fermeture[250] = "Fermeture du client ";
    int status = 0;
    int boucle = 1;
    int nbcarecrit;

    status = getpid();
    sprintf(Cpid,"%d",status);		//Converti le pid en string pour ecrire dans le pipe

	dp=open(arg[1],O_WRONLY);	// On ecrit la question dans le pipe
	
	while(1)
	{
		printf("\n\tBienvenue sur notre service ReponsAtout !!!");
		printf("\n\nTaper une question............: 1\n");
		printf("Quitter.......................: 0\n");
		printf("votre choix: ");
		rewind(stdin);
		scanf("%c",&choix);
		getchar();
		switch(choix)
		{		
			
			case '0' :
				strcat(fermeture,Cpid);
				write(dp, fermeture,250);
				close(dp);	// On ferme le pipe
				printf("Fermeture du pipe\n");
				while(boucle == 1)
				{
					printf("Appuyer sur CTR+D pour fermer le fils\n");
					char buffer[1];
					
					if(fgets(buffer,10,stdin) == NULL)
					{
						boucle = 0;
					}
					else
					{
						printf("Veuillez saisir la bonne commande afin de quitter\n");
					}
				}
	
				printf("Fermeture du fils\n");
				exit(0);
				break;
				
			case '1' :
				printf("tapez votre question :\n");
				//lire(question,250);
				
				scanf(" %[^\n]",question);
				getchar();
				
				strcat(question,"\t");
				strcat(question,Cpid);		// On ajoute le pid a fin de la question 

				dp=open(arg[1],O_WRONLY);
				nbcarecrit = write(dp, question,sizeof(question));
				
				sleep(1);
				close(dp);
				break;
				
			default :
				printf("Mauvaise commande, veuillez saisir une nouvelle commande\n");
				break;
	
		}
	}		
}

//int lire(char *chaine, int longueur)
//{
    //char *positionEntree = NULL;

    //// On lit le texte saisi au clavier
    //if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    //{
        //positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        //if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        //{
            //*positionEntree = '\0'; // On remplace ce caractère par \0
        //}
        //return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    //}
    //else
    //{
  ////     return 0; // On renvoie 0 s'il y a eu une erreur

    //}
//}
