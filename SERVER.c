#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctype.h>
#include <linux/stat.h>

#define USN_PIPE	 "USN"  /*pipe for request from client */
#define DATA_PIPE	 "DATA" /* pipe for response to client */ 
#define MAXT 100    		/* maximum number of clients  that server can handle */

int count=0; 	/* keeping track of clients */
int usnfd,datafd;  /* file descriptors for pipes */
struct student{
	char usn[10];
	char name[20];
	int sem;
	char branch[10];
	float GPA;	
} S;

void *write_data(void  *sp)
{	
	struct student SS,*key;
	key=(struct student *)sp;
	char s1[10],s2[10];
	FILE *fp;
	fp=fopen("maindatabase.txt","r");
	int i,f;
	for(i=0;i<10;i++){
		fread(&SS,sizeof(struct student),1,fp);
		strcpy(s1,SS.usn);
		strcpy(s2,key->usn);
		if(strcmp(s1,s2)==0){
			f=1;
			break;
		}
		
	}
	if(f==1)
	{
		datafd = open(DATA_PIPE,O_WRONLY);
		write(datafd,&SS,sizeof(struct student));
		close(datafd);
		close(usnfd);	
	}
	else{
		strcpy(SS.usn,"---");
		datafd = open(DATA_PIPE,O_WRONLY);
		write(datafd,&SS,sizeof(struct student));
		close(datafd);
		close(usnfd);	
	}
	fclose(fp);
	pthread_exit(0);
}
	
int main()
{
       
        char susn[10];
	
	pthread_t td[MAXT]; /* declaring the thread ids */ 
	
        umask(0);
        mkfifo(USN_PIPE, S_IFIFO|0666);
	mkfifo(DATA_PIPE, S_IFIFO|0666);
        while(1)    /* server will listen always */
    	{
                
		printf(" \n ---------------------- \n waiting for request . . . \n"); 
		
		if((usnfd = open(USN_PIPE,O_RDONLY))<0) 
		{
         	     perror("open");			/* error in opening the usn pipe */
          	     exit(1);
       		}
		
	       	read(usnfd,susn,10);
		printf("\n Connected client is %s",susn);
		count++;
		strcpy(S.usn,susn);
		strcpy(S.name,"\0");
		if(count>MAXT)
		{	
			printf("\n Max limit is reached .. shuting down the server .. \n");
			exit(0);
		}
		else
		{
			pthread_create(&td[count],NULL,write_data,&S);	 /* creating the thread for the request */
			printf("\n The thread id is %u\n",(unsigned int)td[count]);
			printf(" This is thread %d \n ",count); 
	        }
	}

        return(0);
}
