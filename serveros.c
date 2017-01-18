#include<stdio.h>
#include<string.h>
struct student{
	char usn[10];
	char name[20];
	int sem;
	char branch[10];
	float GPA;	
};
void input();
void display();
void search();	
int main(){
	
	int i,ch;
	while(1){
		printf("\n\tMENU\n1.create database\n2.display all\n3.search\n4.exit");
		scanf("%d",&ch);
		switch(ch){
			case 1:printf("\n---------INPUT------\n");
				input();
				break;
			case 2:printf("\n---------OUTPUT------\n");
				display();
				break;
			case 3:printf("\n---------SEARCH------\n");
				search();
				break;
			case 4:return 0;
			default:printf("\nInvalid choice\n");
		}
	}
}
void input(){
	struct student S;
	int i;
	FILE *fp;
	fp=fopen("maindatabase.txt","w");
	for(i=0;i<10;i++){
		printf("\nEnter usn :");
		scanf("%s",S.usn);
		printf("\nEnter name: ");
		scanf("%s",S.name);
		printf("\nEnter sem : ");
		scanf("%d",&S.sem);
		printf("\nEnter branch :");
		scanf("%s",S.branch);
		printf("\nEnter GPA:");
		scanf("%f",&S.GPA);
		fwrite(&S,sizeof(S),1,fp);
	}
	fclose(fp);
}
void display(){
	struct student S;
	int i;
	FILE *fp;
	fp=fopen("maindatabase.txt","r");
	for(i=0;i<10;i++){
		fread(&S,sizeof(S),1,fp);
		printf("\nusn :");
		printf("%s",S.usn);
		printf("\nname: ");
		printf("%s",S.name);
		printf("\nEnter sem : ");
		printf("%d",S.sem);
		printf("\nEnter branch :");
		printf("%s",S.branch);
		printf("\nEnter GPA:");
		printf("%f",S.GPA);
		
	}
	fclose(fp);
}
void search(){
	struct student S;
	int i,f=0;
	char key[10];
	FILE *fp;
	fp=fopen("maindatabase.txt","r");
	printf("\nEnter key usn: ");
	scanf("%s",key);
	for(i=0;i<10;i++){
		fread(&S,sizeof(S),1,fp);
		printf("\n%s matching/not matching",S.usn);
		if(strcmp(key,S.usn)==0){
			f=1;
			break;
		}
		
	}
	if(f==1){
		printf("\nusn :");
		printf("%s",S.usn);
		printf("\nname: ");
		printf("%s",S.name);
		printf("\nEnter sem : ");
		printf("%d",S.sem);
		printf("\nEnter branch :");
		printf("%s",S.branch);
		printf("\nEnter GPA:");
		printf("%f",S.GPA);
	}
	else
		printf("\nNot found");
	fclose(fp);
}
