#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>

#define TAILLE 250

int inter = 0;
int NBFILS;
int restart(void);
void reponse(char buf[TAILLE]);
void interupt();
int fork_entree(int n);


int main(int argc, char *arg[])
{
    int desc,nb,i;
    char buf[TAILLE];
    int boucle=1,nbFils,pidpere;
	char choix,Cpidpere[5];
    
    
    nbFils = atoi(arg[2]);	// On converti de string vers int le nb de fils
	NBFILS = nbFils;
    
	signal(SIGINT,SIG_IGN);  // Protection pour control C
    signal(SIGCHLD,interupt);	// On cable le signal de retour du fils sur la fct interupt

    unlink(arg[1]);
    mkfifo(arg[1],0666);	// On s'assure que le pipe n'existe pas puis on le cree
    
    // Initialistaion des n processus
	pid_t pid = 1;	// On le set à 1 pour le premier tour de boucle
	for(i=0 ; i<nbFils && pid>0 ; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			execl("/usr/bin/xterm","xterm","-e" ,"./fils",arg[1],"set","-o","ingnoreeof",NULL);
		}

	}	
if(pid==0)
{
	//rien
}
else
{
	desc=open(arg[1],O_RDONLY);
	pidpere = getpid();
	sprintf(Cpidpere,"%d",pidpere);
do
 { 
	
	printf("\n\tBienvenue sur notre serveur ReponsAtout !!!");
	printf("\n\nMode de lecture client............: 1\n");
	printf("Creer un nouveau client...........: 2\n");
	printf("Connaitre le nombre de client.....: 3\n");
	printf("Quitter...........................: 0\n");
	printf("votre choix: ");
	rewind(stdin);
	scanf(" %c",&choix);
	getchar();
	switch(choix)
	{		
			
		case '0' :
				printf("Fermeture du serveur et de tous les clients\n");
				kill(0,SIGTERM);
				wait(NULL);
				return 0;
				break;
				
			case '1' :
				if(pid == 0)
				{
					//On attend de passer dans le père
				}
				else
				{
					desc=open(arg[1],O_RDONLY);
					if (NBFILS != 0)
					{
						 
						while(NBFILS>0)
						{
							nb=read(desc,buf,TAILLE);
							buf[nb]='\0';
							if(nb != 0)
							{
								printf("Lecture : %s \n",buf);
								if(strstr(buf,"Fermeture") == NULL)
								{
									reponse(buf);
								}
							}
						}
					}
					else
					{
						printf("Aucun client de connecter, veuillez en creer un\n");
					}
				}
				close(desc);
				break;
				
			case '2' :
				printf("Creation d'un nouveau fils\n");
				
				if(pid>0)	// Si on est dans le pere on peut creer le fils
				{
					pid = fork();
					if(pid == 0)	// Si on est dans le fils on lance le programme
					{
						
						execl("/usr/bin/xterm","xterm","-e" ,"./fils",arg[1],NULL,"set","-o","ingnoreeof",NULL);
					}
				}
				printf("Le fils a ete cree\n");
				NBFILS = NBFILS +1;
				break;
				
			case '3' :
				printf("Il y a actullement %d client(s) de connecter au serveur\n",NBFILS);
				//execl("/usr/bin/pstree","pstree","-H PID","Cpidpere",NULL);
				break;
				
			default :
				printf("Mauvaise commande, veuillez saisir une nouvelle commande\n");
				break;
	
		}
	}while(1);	
}
}


int restart(void)
{
	char lettre;
	int boucle = 0;
	do
	{
		printf("Voulez creer un nouveau client? Y ou N\n");
		scanf(" %c",&lettre);
	
		switch(lettre)
		{
			case 'y' :
				return 1;
				break;
				
			case 'Y' :
				return 1;
				break;
				
			case 'N' :
				return 0;
				break;
				
			case 'n' :
				return 0;
				break;
				
			default :
				printf("Mauvaise comande, veuillez recommencer\n");
				break;
		}
	}while(boucle == 0);
}

void reponse(char buf[TAILLE])
{

	 if(strstr(buf,"temps")!=NULL || strstr(buf,"TEMPS")!=NULL || strstr(buf,"duree")!=NULL || strstr(buf,"DUREE")!=NULL)					// Compare si un mot cle correspond 
		{
			printf("Il vous faudra 30 min pour vous rendre à votre domicile car la circulation est dense.\n");

		}
		else if(strstr(buf,"meteo")!=NULL || strstr(buf,"METEO")!=NULL)
		{
			printf("Aujourd'hui le ciel est dégagé, la temprature maximale est de 24° et la minimale est à 2°\n");

		}
		else
		{
			printf("Veuillez nous excuser, nous ne pouvons pas répondre à votre question\n");
		}

}

void interupt()
{
	NBFILS = NBFILS -1;
}


	

