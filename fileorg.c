#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct node
{
    char name[32];
    char type;
    struct node *child[5];
    struct node *parent;
    int c_count;
    char *data;
}node;
node *root = NULL;
node *pwd = NULL;

void red () {
  printf("\033[1;31m");
}
void reset(){
      printf("\033[0m");
}
void cyan(){
      printf("\033[1;33m");
}
void green(){
      printf("\033[0;32m");
}

void blue(){
      printf("\033[0;34m");
}

void help()
{
	 printf("Available commands:");
     cyan();
	 printf("\npwd:");  printf("\tTo print location of present working directory");
	 printf("\nls:");  printf("\tTo print contents of pwd");
     printf("\ncd:");  printf("\tTo move to a paticular directory");  printf("\t[cd <dirname>");
	 printf("\nmkdir:");  printf("\tTo create new directory in pwd");   printf("\t[mkdir <dirname>]");
	 printf("\nrmdir:");  printf("\tTo remove directory in pwd");  printf("\t[rmdir <dirname>]");
     printf("\nrm:");  printf("\tTo remove file");  printf("\t[rm <filename>]");
	 printf("\ntouch:");  printf("\tTo create new file in pwd");   printf("\t[touch <filename>]");
     printf("\nmv:"); printf("\tTo rename a file");  printf("\t[mv <filename1> <filename2>");
	 printf("\nquit:");  printf("\tQuit the program");
	printf("\n");
    reset();
}


void mkdir()
{
    int i;
    char name[32];
    scanf("%s",name);
    if(pwd->c_count >= 5)
        printf("Child limit exceeded\n");
    else{
        for(i=0;i < pwd->c_count;i++)
            if(strcmp(name,pwd->child[i]->name)==0 && pwd->child[i]->type == 'd'){
                printf("Directory already exists\n");
                return;
            }    
        node *new = (node *)malloc(sizeof(node));
        strcpy(new->name,name);
        for(i=0;i<5;i++)
            new->child[i] = NULL;
        new->parent = pwd;
        new->type = 'd';
        new->c_count = 0;
        pwd->child[pwd->c_count] = new;
        pwd->c_count++;
    }
}
void touch()
{
    int i;
    char name[32],data[100];
    if(pwd->c_count > 5){
        printf("Child limit exceeds\n");
        return;
    }
    scanf("%s",name);
    for(i=0;i < pwd->c_count;i++)
        if(strcmp(name,pwd->child[i]->name)==0 && pwd->child[i]->type == 'f'){
            printf("File already exists\n");
            return;
        }    
    node *new = (node *)malloc(sizeof(node));
    strcpy(new->name,name);
    new->type = 'f';
    pwd->child[pwd->c_count] = new;
    pwd->c_count++;
}
void ls()
{
    if(pwd->c_count == 0)
        printf("Empty directory\n");
    else{
        for(int i=0;i<pwd->c_count;i++)
        {
        if(pwd->child[i]->type == 'd')
        {
            green();
            printf("%s\t",pwd->child[i]->name);
            reset();
        }
            
        else
        {
            blue();
            printf("%s\t",pwd->child[i]->name);
            reset();
        }
            
        }
    }
    printf("\n");
}
void cd(){
    char arg[32];
    scanf("%s",arg);
    if(strcmp(arg,"..")==0)
    {
        if(strcmp(pwd->name,"root")==0)
            printf("Currently in root directory..\n");
        else
            pwd = pwd->parent;
    }
    else if(strcmp(arg,"root")==0)
        pwd = root;
    else{
        for(int i=0;i<pwd->c_count;i++)
            if(strcmp(arg,pwd->child[i]->name)==0){
                pwd = pwd->child[i];
                return;
            }
        printf("Directory not found\n");
    }
}
void rmdir()
{
    char name[32];
    int i,j,flag=0;
    scanf("%s",name);
    for(i=0;i < pwd->c_count;i++)
    {
        if(strcmp(name,pwd->child[i]->name)==0 && pwd->child[i]->type == 'd')
        {
            if(pwd->child[i]->c_count != 0)
            {
                printf("Cannot delete [directory not empty]\n");    
                flag =1;           
                break;
            }
            else
            {
                for(j=i;j<pwd->c_count-1;j++)
                {
                    strcpy(pwd->child[j]->name,pwd->child[j+1]->name);
                    pwd->child[j]->type=pwd->child[j+1]->type;
                }
                strcpy(pwd->child[j]->name,"");
                pwd->c_count--;
                flag=1;
                break;  
                
            }
        }
        else if(strcmp(name,pwd->name)==0)
        {
        	printf("Cannot delete pwd\n");
            flag=1;
        	break;
        }
       
    }  
     if(flag==0)
        {
        	printf("Directory not found\n");
        }     	
}

void dis_pwd()
{
    char path[100][100];
    int k=0;
    node *temp=pwd;
    while(1)
    {
        strcpy(path[k++],temp->name);
        strcpy(path[k++],"/");
        temp=temp->parent;
        if(temp==NULL)
        {
            break;
        }
    }
    cyan();
    for(int i=k-1;i>=0;i--)
        printf("%s",path[i]);
    printf("\n");
    reset();
}

void rm()
{
    char name[32];
    int i,j,flag=0;
    scanf("%s",name);
    for(i=0;i < pwd->c_count;i++)
    {
        if(strcmp(name,pwd->child[i]->name)==0 && pwd->child[i]->type == 'f')
        {
                for(j=i;j<pwd->c_count-1;j++)
                {
                    strcpy(pwd->child[j]->name,pwd->child[j+1]->name);
                    pwd->child[j]->type=pwd->child[j+1]->type;
                }
                strcpy(pwd->child[j]->name,"");
                pwd->c_count--;
                flag=1;
                break;  
                
        }
       
    }  
     if(flag==0)
        {
        	printf("File not found\n");
        }     	
}

void mv()
{
    char fname1[100],fname2[100];
    int i,j,flag=0;
    scanf("%s",fname1);
    scanf("%s",fname2);
    for(i=0;i < pwd->c_count;i++)
    {
        if(strcmp(fname2,pwd->child[i]->name)==0 && pwd->child[i]->type == 'f')
        {
            printf("Filename already exists\n");
            goto label;
        }
    }
    for(i=0;i < pwd->c_count;i++)
    {
        if(strcmp(fname1,pwd->child[i]->name)==0 && pwd->child[i]->type == 'f')
        {
               
                strcpy(pwd->child[i]->name,fname2);
                flag=1;
                break;  
                
        }
       
    }  
     if(flag==0)
        {
        	printf("File not found\n");
        }  
        label:;

}

void main()
{
    char cmd[20];
    int i;
    root = (node *)malloc(sizeof(node));
    strcpy(root->name,"root");
    for(i=0;i<5;i++)
        root->child[i] = NULL;
    root->parent = NULL;
    root->type = 'd';
    root->c_count = 0;
    pwd = root;
    printf("TYPE 'help' TO GET INFO ON AVAILABLE COMMANDS\n");
    while(1)
    {
        red();
        printf("%s>> ",pwd->name);
        reset();
        scanf("%s",cmd);
        if(strcmp(cmd,"help")==0)
            help();
        else if(strcmp(cmd,"mkdir")==0)
            mkdir();
        else if(strcmp(cmd,"ls")==0)
            ls();
        else if(strcmp(cmd,"cd")==0)
            cd();
        else if(strcmp(cmd,"touch")==0)
            touch();
        else if(strcmp(cmd,"rmdir")==0)
            rmdir();
        else if(strcmp(cmd,"quit")==0)
            exit(0);
        else if(strcmp(cmd,"pwd")==0)
            dis_pwd();
        else if(strcmp(cmd,"rm")==0)
            rm();
        else if(strcmp(cmd,"mv")==0)
            mv();    
        else
            printf("invalid cmd\n");
    }
}
