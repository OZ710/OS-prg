#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int hexadecimalToDecimal(char hexVal[]) 
{    
    int len = strlen(hexVal); 
    int base = 1; 
    int dec_val = 0;  
    for (int i=len-1; i>=0; i--) 
    {     
        if (hexVal[i]>='0' && hexVal[i]<='9') 
        { 
            dec_val += (hexVal[i] - 48)*base; 
            base = base * 16; 
        } 
        else if (hexVal[i]>='A' && hexVal[i]<='F') 
        { 
            dec_val += (hexVal[i] - 55)*base;  
            base = base*16; 
        } 
    } 
      
    return dec_val; 
} 
void main()
{
	FILE *f1,*f2,*f3,*f4,*f5,*f6;
	int i=2,j=0,k=0,count=0,p=0,flag=0;
	char inst[100],temp[100],hex[10],leng[10],trec[100][10],len[10][10],pname[100];
    strcpy(trec[0],"T");   	
	f1 = fopen("temp.txt","r");
	f2 = fopen("obj.txt","w");
    f6 = fopen("prg.txt","r");
	f4 = fopen("length.txt","r");
    fscanf(f6,"%s",pname);
	while(!feof(f1))
	{
        fgets(inst,100,f1);
        if (inst[j]=='\n')
        {
           break;
        }
		if(flag==0)
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
                temp[k]='\0';
                fscanf(f4,"%s",leng);
                fprintf(f2, "H^%s^%06s^%06s^\n",pname,temp,leng );
                sprintf(hex,"%06s",temp);
                strcpy(trec[1],hex);
                flag=1;  
        }
        else
        {
            char opc[100],opval[10],adr[20],opr[100],opradr[10],tlen[100];
            k=0;
        	while(inst[j]!=' ')
            {
            	adr[k++]=inst[j++];
            } 
            adr[k]='\0';
            while(inst[j]==' ')
            	j++;
            k=0;
            while(inst[j]!=' ')
            	opc[k++]=inst[j++];
            opc[k]='\0';

            f5 = fopen("OPTAB.txt","r");
            char line[100],check[10];

            while(!feof(f5))
            {
            	k=0;
            	fgets(line,100,f5);
                
            	int l=0;
            	while(line[k]!=' ')
                	check[l++]=line[k++];
                check[l]='\0';
               
                while(line[k]==' ')
                	k++;
                l=0;
                if(strcmp(opc,check)==0)
                {
                    while(line[k]!='\n')
                        { 
                        opval[l++]=line[k++];
                        }
                       opval[l]='\0';  
                }
                	
                  

            }
              
            while(inst[j]==' ')
            	j++;
            k=0;	
            while(inst[j]!='\n')
            {
            	opr[k++]=inst[j++];
            } 
            opr[k]='\0';
            if(strcmp(opc,"RESB")==0 || strcmp(opc,"RESW")==0)
            {
                int n;
                if(strcmp(trec[i-1],"|")!=0)
                {
                    strcpy(trec[i++],"|");
                    strcpy(trec[i++],"T");
                    int val=hexadecimalToDecimal(adr);
                    n=atoi(opr);
                    val=val+3*n;
                    char con[10];
                    sprintf(con,"%x",val);
                    sprintf(hex,"%06s",con);
                    strcpy(trec[i++],hex);
                    itoa(count,len[p++],10);
                    count=0;
                }    
                
            }
            else if(strcmp(opc,"BYTE")==0)
            {
                if(opr[0]=='c')
                {
                    k=2;
                    char x[10][10];
                    while(opr[k]!='\'')
                    {
                        sprintf(x[k-2],"%x",opr[k]);
                        k++;
                    }
                    if((count+(k-2))>30)
                    {
                        strcpy(trec[i++],"|");
                        strcpy(trec[i++],"T");
                        sprintf(hex,"%06s",adr);
                        strcpy(trec[i++],hex);
                        itoa(count,len[p++],10);
                        count=0;
                    }
                    int l=0,m=0;
                    while(m<k-2)
                    {
                        trec[i][l]=x[m][0];
                        l++;
                        trec[i][l]=x[m][1];
                        l++;
                        m++;     
                    }
                    trec[i][l]='\0';
                    i++;
                    count=count+(k-2);
                }
                else
                {
                    char h[10];
                    k=2;
                    int l=0;
                    while(opr[k]!='\'')
                    {
                        h[l++]=opr[k++];
                        
                    }
                    if((count+(strlen(h)/2))>30)
                    {
                        strcpy(trec[i++],"|");
                        strcpy(trec[i++],"T");
                        sprintf(hex,"%06s",adr);
                        strcpy(trec[i++],hex);
                        itoa(count,len[p++],10);
                        count=0;
                    }

                    strcpy(trec[i++],h);
                    count=count+(strlen(h)/2);
                }
                
            }
            else if(strcmp(opc,"WORD")==0)
            {
                if((count+3)>30)
                {
                    strcpy(trec[i++],"|");
                    strcpy(trec[i++],"T");
                    sprintf(hex,"%06s",adr);
                    strcpy(trec[i++],hex);
                    itoa(count,len[p++],10);
                    count=0;
                }  
                int n;
                n=atoi(opr);
                sprintf(hex,"%06d",n);  
                strcpy(trec[i++],hex);
                count=count+3;
            }
            else if(strcmp(opc,"RSUB")==0)
            {
                if((count+3)>30)
                {
                    strcpy(trec[i++],"|");
                    strcpy(trec[i++],"T");
                    sprintf(hex,"%06s",adr);
                    strcpy(trec[i++],hex);
                    itoa(count,len[p++],10);
                    count=0;
                }  
                strcpy(trec[i++],"4c0000");
                count=count+3;
            }
            else if(strcmp(opc,"END")==0)
            {
                    strcpy(trec[i++],"|");
                    itoa(count,len[p++],10);
                    count=0;
                    break;
            }
            
            else
            {
                char opr1[100];
                f3 = fopen("SYMTAB.txt","r");
                    if(opr[strlen(opr)-1]=='X' && opr[strlen(opr)-2]==',')
                    {
                       strcpy(opr1,opr);
                       opr1[strcspn(opr1,",")]='\0';
                       while(!feof(f3))
                       {
                            k=0;
                            fgets(line,100,f3);
                            int l=0;
                            while(line[k]!=' ')
                                check[l++]=line[k++];
                            check[l]='\0';
                            while(line[k]==' ')
                                k++;
                            l=0;
                            if(strcmp(opr1,check)==0)
                                {
                                    while(line[k]!='\n')
                                    {
                                        opradr[l++]=line[k++];
                                    }
                                    opradr[l]='\0'; 
                                }
                       }
                    }
                    while(!feof(f3))
                    {
                        k=0;
                        fgets(line,100,f3);
                        int l=0;
                        while(line[k]!=' ')
                            check[l++]=line[k++];
                        check[l]='\0';
                        while(line[k]==' ')
                            k++;
                        l=0;
                        if(strcmp(opr,check)==0)
                            {
                                while(line[k]!='\n')
                                {
                                    opradr[l++]=line[k++];
                                }
                                opradr[l]='\0'; 
                            }
                    }
                    if((count+3)>30)
                    {
                    strcpy(trec[i++],"|");
                    strcpy(trec[i++],"T");
                    sprintf(hex,"%06s",adr);
                    strcpy(trec[i++],hex);
                    itoa(count,len[p++],10);
                    count=0;
                    }  
                    if(opr[strlen(opr)-1]=='X' && opr[strlen(opr)-2]==',')
                    {
                        char ind[10],rval[10];
                        ind[0]=opradr[0];
                        ind[1]='\0';
                        int n=atoi(ind);
                        int z=n^8;
                        itoa(z,ind,16); 
                        opradr[0]=ind[0];
                        int l=0,r=0;
                        k=0;
                        sprintf(rval,"%04s",opradr);
                        while(l<strlen(opval))
                        {
                            trec[i][l]=opval[l];
                            l++;
                        }
                        while(r<strlen(rval))
                        {
                            trec[i][l]=rval[r]; 
                            l++;
                            r++;
                        }
                        trec[i][l]='\0';
                        i++;
                        count=count+3;
                    }
                    else
                    {
                        char rval[10];
                        int l=0,r=0;
                        k=0;
                        sprintf(rval,"%04s",opradr);
                        while(l<strlen(opval))
                        {
                            trec[i][l]=opval[l];
                            l++;
                        }
                        while(r<strlen(rval))
                        {
                            trec[i][l]=rval[r]; 
                            l++;
                            r++;
                        }
                        trec[i][l]='\0';
                        i++;
                        count=count+3;
                    }
            }
           
            
        }
      j=0;
      
	}
    count=0,k=0;
    for (int q = 0; q <i; ++q)
    {
        if(strcmp(trec[q],"|")==0)
        {
            fprintf(f2, "\n" );
            count=0;
        }
        else
        {
            fprintf(f2,"%s^",trec[q] );
            count++;
            if(count==2)
            {
                int n=atoi(len[k++]);
                fprintf(f2,"%02x^",n);
            }    
            
        }
            
    }
    fprintf(f2, "E^%s^",trec[1] );
}
