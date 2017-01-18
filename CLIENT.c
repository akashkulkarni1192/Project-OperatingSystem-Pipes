#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

#define USN_PIPE "USN"     /* pipe for request to server */
#define DATA_PIPE "DATA"   /* pipe for response from server */

int main()
{
       	char usn[15],name[80];
	int cfd,dfd;	/* file descriptors for the pipes */ 
	int choice=1;  
	struct student{
		char usn[10];
		char name[20];
		int sem;
		char branch[10];
		float GPA;	
	}sc;

	do{		
		if(choice==1){ 
			fflush(stdin);
	
			printf("\n Enter USN : ");  /* requesting with usn */
	 		scanf("%s",usn);
			if((cfd = open(USN_PIPE,O_WRONLY))<0){
		        	perror("open");			  /* error in opening the pipe */
		        	exit(1);
			}

			write(cfd,usn,10); 			/* write the request to the usn pipe */ 
			close(cfd);
			dfd = open(DATA_PIPE,O_RDONLY);        
			read(dfd,&sc,sizeof(struct student));	/* fetching the data from the data pipe */
			printf("\n\tRequested Service:\n");
			if(strcmp(sc.usn,"---")==0)
				printf("\n\t--File Not Found--\n\n");
			else{
				printf("\n---------------------------------\n");
				printf("Name\t:\t%s\nUsn\t:\t%s\nSemester:\t%d\nBranch\t:\t%s\nGPA\t:\t%f\n",sc.name,sc.usn,sc.sem,sc.branch,sc.GPA);
				printf("\n---------------------------------\n");
			}	
			close(dfd);
	  	}
		else{
			printf("\nDisconnected\n");
			exit(0); /* to abort */
		}
		printf("\n\t1.Next Request(1 for Yes) : ");
		scanf("%d",&choice);

      	}while(1);
	
        return(0);
}
