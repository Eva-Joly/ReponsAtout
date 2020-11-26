#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

int main(void)
{
	int pid,status;
	
	printf("On lance un processus fils\n");
	pid = fork();
	printf("Le PID actuelle est %d\n",pid);
	if(pid == 0)
		{
			printf("1");
			//execv("gcc2",NULL);
			execl("usr/bin/xterm","xterm","-hold","gcc2",NULL,NULL);
			printf("1\n");
		}
		else 
		{
			printf("Je suis le père et j'attends la mort du fils\n");
			wait(&status);
			printf("Vous avez saisi %d\n",status>>8);
			printf("Je suis le père, je me termine\n");
			exit(0);
			return (0);

		}


}
