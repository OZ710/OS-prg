#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
	FILE *f1,*f2,*f3,*f4,*f5;
	int i=0,j=0,k=0,count=0;
	char inst[100],temp[100],hex[10],len[10],char trec[100][10];
    strcpy(trec[0],"T");   	
	f1 = fopen("temp.txt","r");
	f2 = fopen("obj.txt","w");
	f3 = fopen("SYMTAB.txt","r");
	f4 = fopen("length.txt","r");
   
	while(!feof(f1))
	{
		fgets(inst,100,f1);
		if(inst[j]==' ')
		{
			while(inst[j]==' ')
				j++;
            
            while(inst[j]!=' ')
            {
            	j++;
            } 
            while(inst[j]==' ')
				j++;
			k=0;
			while(inst[j]!='\n')
            {
            	temp[k++]=inst[j++];
            } 
            int n;
            n=atoi(temp);
            sprintf(hex,"%06d",n);
            fscanf(f4,"%s",temp);
            n=atoi(temp);
            sprintf(len,"%06d",n);
            fprintf(f2, "H^------^%s^%s^",hex,len );
            strcpy(trec[1],hex);
        }
        else
        {
            char opc[100],opval[10];
            k=0;
        	while(inst[j]!=' ')
            {
            	temp[k++]=inst[j++];
            } 
            while(inst[j]==' ')
            	j++;
            k=0;
            while(inst[j]!=' ')
            	opc[k++]=inst[j++];
            f5 = fopen("OPTAB.txt","r");
            char line[100],check[10];
            while(!feof(f5))
            {
            	k=0;
            	fgets(line,100,f5);
            	int l=0;
            	while(line[k]!=' ')
                	check[l++]=line[k++];
                while(line[k]==' ')
                	k++;
                l=0;
                if(strcmp(opc,check)==0)
                	while(line[k]!='\n')
                		opval[l++]=line[k++];
            }
            
        }
      j=0;
	}
}