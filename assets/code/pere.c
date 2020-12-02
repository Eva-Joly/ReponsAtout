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
int restart(void);
void reponse(char buf[TAILLE]);
void interupt();


int main(void)
{
    int pid,desc,nb;
    char buf[TAILLE];
    char *argv[2];
    int boucle;

    signal(SIGCHLD,interupt);
    argv[0]="pipe";

    unlink(argv[0]);
    mkfifo(argv[0],0666);
    
 do
 {   
   pid=fork();
    
    if(pid == 0)
    {
	argv[1]=NULL;
//      execv("FILS", argv);
        execl("/usr/bin/xterm","xterm","-e" ,"./fils",argv[0],argv[1],"set","-o","ingnoreeof",NULL);
    }
    else
    {
		inter = 0;
		desc=open(argv[0],O_RDONLY);
		while(inter == 0)
		{

			nb=read(desc,buf,TAILLE);
			if(nb != 0)
			{
				printf("nb lu : %d\n",nb);
				buf[nb]='\0';
			
				printf("Lecture : %s \n",buf);
				if(strstr(buf,"Fermeture") == NULL)
				{
					reponse(buf);
				}
			}
			
		}
		wait(NULL);
	
	boucle = restart();
    }
}while (boucle == 1);
close(desc);
printf("Fermeture du serveur\n");
return 0;
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
	inter = 1;
}

