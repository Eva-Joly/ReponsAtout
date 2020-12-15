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



int main(int argc, char *arg[])
{
    int dp;
    char choix;
    char question[250];
    char Cpid[5];
    char fermeture[250] = "Fermeture du client ";
    char listeMot[250] = "Temps, Duree, Meteo, Match, Anniversaire, Rappel, Heure, Date";
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
		printf("Liste des mots clés...........: 2\n");
		printf("Quitter.......................: 0\n");
		printf("votre choix: ");
		rewind(stdin);
		scanf("%c",&choix);
		getchar();
		switch(choix)
		{		
			
			case '0' :
				dp=open(arg[1],O_WRONLY);
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
				scanf(" %[^\n]",question);
				getchar();
				
				strcat(question,"\t");
				strcat(question,Cpid);		// On ajoute le pid a fin de la question 

				dp=open(arg[1],O_WRONLY);								// Ouverture du PIPE puis ecriture de la question
				nbcarecrit = write(dp, question,sizeof(question));
				
				sleep(1);		// Tempo d'une seconde 
				close(dp);		// Fermeture du PIPE
				break;
				
			case '2' :
				printf("Voici la liste des mots clés : \n%s\n",listeMot);		// Affichage de la liste de mot clé
				break;
				
			default :
				printf("Mauvaise commande, veuillez saisir une nouvelle commande\n");
				break;
	
		}
	}		
}
