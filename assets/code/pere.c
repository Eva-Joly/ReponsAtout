#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    int pid,desc,nb, pidClient;
    char buf[80];
    char *argv[2];
   
    argv[0]="pipe";

    unlink(argv[0]);
    mkfifo(argv[0],0666);
    
    pid=fork();
    
    if(pid == 0)
    {
	argv[1]=NULL;
        execv("FILS", argv);
    }
    else{
    	desc=open(argv[0],O_RDONLY);
    	nb=read(desc,buf,80);
    	buf[nb]='\0';
    	printf(" message: %s\n ",buf);
    	close(desc);
    	wait(NULL);
    }
  exit(0);
}



