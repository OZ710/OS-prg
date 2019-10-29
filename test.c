#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
 {
   FILE *f1;
   int i=0,j=0,k=0,count=0,loctr=0,space=0;//i to traverse the file,j to iterate single line of a file
   char inst[100],temp[100]="";
   f1 = fopen("test.txt","r");
   while(!feof(f1))
      {
          if(strcmp(temp,inst)==0)
            break;
         fgets(inst,100,f1);
         strcpy(temp,inst);
         printf("%s %ld\n",inst,strlen(inst));
         if(inst[0]=='\0')
          break;
      }
 }         