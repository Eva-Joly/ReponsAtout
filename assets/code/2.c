#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

int main(void)
{
	int nombre;
	printf("Je suis le fils, saisissez un nombre :\n");
	scanf("%d",&nombre);
	printf("Je ferme\n");
	exit(nombre);
	return 0;
}
