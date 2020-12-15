#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<time.h>
#include<ctype.h>

#define TAILLE 250

int inter = 0;
int NBFILS;
int restart(void);
void reponse(char buf[TAILLE]);
void interupt();
int fork_entree(int n);
char* Conversion(char* buffer);


const char * NomJourSemaine[] = {"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"}; 
  
const char * NomMois[] = {"janvier","fevrier","mars","avril","mai","juin","juillet","aout","septembre","octobre","novembre","decembre"}; 
                          

int main(int argc, char *arg[])
{
    int desc,nb,i;
    char buf[TAILLE];
    int nbFils,pidpere;
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
			execl("/usr/bin/xterm","xterm","-e" ,"./client",arg[1],"set","-o","ingnoreeof",NULL);
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
					
					if (NBFILS > 0)
					{
						desc=open(arg[1],O_RDONLY);
						printf("Passage en mode lecture\n");
						 
						while(NBFILS>0)
						{
							nb=read(desc,buf,TAILLE);
							buf[nb]='\0';
							if(nb != 0)
							{
								printf("\nLecture : %s \n",buf);
								if(strstr(buf,"Fermeture") == NULL)
								{
									reponse(buf);
								}
							}
						}
						close(desc);
						printf("Plus aucun client n'est disponible, fermeture du mode lecture\n");
					}
					else
					{
						printf("Aucun client de connecter, veuillez en creer un\n");
					}
				}
				
				break;
				
			case '2' :
				printf("Creation d'un nouveau fils\n");
				
				if(pid>0)	// Si on est dans le pere on peut creer le fils
				{
					pid = fork();
					if(pid == 0)	// Si on est dans le fils on lance le programme
					{
						
						execl("/usr/bin/xterm","xterm","-e","./client",arg[1],"set","-o","ingnoreeof",NULL);
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


void reponse(char buf[TAILLE])
{
	time_t temps; 
    struct tm * t; 
    
    buf = Conversion(buf);

	 if(strstr(buf,"temps")!=NULL || strstr(buf,"duree")!=NULL)					// Compare si un mot cle correspond 
		{
			printf("Il vous faudra 30 min pour vous rendre à votre domicile car la circulation est dense.\n");

		}
		else if(strstr(buf,"meteo")!=NULL)
		{
			printf("Aujourd'hui le ciel est dégagé, la temprature maximale est de 24° et la minimale est à 2°\n");

		}
		else if(strstr(buf,"match")!=NULL)
		{
			printf("Le RCT à gagner contre le Racing 23 à 19\n");

		}
		else if(strstr(buf,"anniversaire")!=NULL)
		{
			printf("Votre anniversaire est le 24 décembre!\n");

		}
		else if(strstr(buf,"rappel")!=NULL)
		{
			printf("Voici la liste de vos rappels:\nEtendre le linge\nFaire à manger\nRepasser le linge\nDormir\n");

		}
		else if(strstr(buf,"heure")!=NULL || strstr(buf,"date")!=NULL)
		{

			time(&temps);
			t = localtime(&temps);
			printf("Nous sommes %s, ", NomJourSemaine[t->tm_wday]); 
			printf("le %02u %s %04u, ", t->tm_mday, NomMois[t->tm_mon], 1900 + t->tm_year); 
			printf("et il est %02uh %02umin %02usec.\n", t->tm_hour, t->tm_min, t->tm_sec);
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

char* Conversion(char* buffer)
{

	for(int i=0; buffer[i] != '\0' ; i++)
	{
		buffer[i] = tolower(buffer[i]);
	}
	
	return buffer;
}
	

