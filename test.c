
   
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
	/*FILE *f1,*f2,*f3;
   	char inst[100],temp[100];
   	f1 = fopen("temp.txt","r");
   	while(!feof(f1)){
   		fscanf(f1,"%s",inst);
		printf("%s\n",inst );
	}
fclose(f1);*/
	        char temp[20][10]={"1234","sd","sagy"};
            printf("%s\n",temp[0],temp[1],temp[2]);
            temp[0]='\0';
            if(temp[0]=='\0')
            	printf("null\n");

            
}
