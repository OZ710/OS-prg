#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

char label[10],opcode[10],oprand[10];
char mnemonic[][10]={"ADD","ADDF","ADDR","AND","CLEAR","COMP","COMPF","COMPR","DIV","DIVF","DIVR","J","JEQ","JGT","JLT","JSUB","LDA","LDB","LDCH","LDF","LDL","LDS","LDT","LDX","LPS","MUL","MULF","MULR","OR","RD","RMO","RSUB","SHIFTL","SHIFTR","STA","STB","STCH","STF","STL","STS","STSW","STT","STX","SUB","SUBF","SUBR","TD","TIX","TIXR","WD","FIX","FLOAT"};

char *trim(char *string){
    while(isspace(string[0]))
        string++;
    char *final = strdup(string);
    int len = strlen(final);
    while(len>0 && isspace(final[len-1]))
        len--;
    final[len] ='\0';
    return final;
}
int tokeniser(char line_[]){
    char *line = trim(line_);
    char token[3][10],*toc;
    int k = 0;    
    toc = strtok(line," ");
    while(toc){
        strcpy(token[k++],toc);    
        toc = strtok(NULL," ");
    }
    if(k == 3){
        strcpy(label,token[0]);
        strcpy(opcode,token[1]);
        strcpy(oprand,token[2]);
    }
    else if(k == 2){        
        strcpy(opcode,token[0]);
        strcpy(oprand,token[1]);
    }
    else{
        strcpy(opcode,token[0]);
        strcpy(oprand,"-");
    }
    return k;
}
int is_opcode(char op[]){
    for(int i=0;i<sizeof(mnemonic)/10;i++)
        if(!strcmp(op,mnemonic[i])){
                return 1;
            }
	return 0;
}
int find_length(char a[])
{
    if (a[0] == 'c')
        return strlen(a) - 3;
    else
        return (strlen(a) - 3) / 2;
}
int main() 
{ 
    FILE *f,*temp,*fp3,*fp4,*len;
    int i, j,k=0, locctr, start_addr,m,lc=0;
    char line[MAX],sym[100][10];
    
    f = fopen("prg3.txt","r");    
    temp = fopen("temp.txt", "a");
    fp3 = fopen("symtab.txt", "a");
    len = fopen("len.txt","w");
    fgets(line,MAX,f);
    lc++;
     m = tokeniser(line); 
    if (strcmp(opcode, "START") == 0)
    {
        locctr = atoi(oprand);
        start_addr = locctr;
        fprintf(temp, "- %s %04x\n", opcode,start_addr);
        fgets(line,MAX,f);
        lc++;
         m = tokeniser(line); 
    }
    else
    {
        locctr = 0;
        start_addr = locctr;
    }
    while(!feof(f)){
        if (m==3){
        	for(int l=0;l<k;l++)
        		if (strcmp(label,sym[l])==0){
        	    // fprintf(temp,"%s%d\n","Duplicate error on line : ",lc);  //temp
        			printf("Duplicate error on line : %d\n",lc);
                    fgets(line,MAX,f);
                    m = tokeniser(line);
        		}
    		strcpy(sym[k++],label);
            fprintf(fp3, "%s %04x\n", label, locctr); //symtab
        }
        	fprintf(temp, "%04x %s %s\n", locctr, opcode, oprand);  //temp
        if (!strcmp(opcode, "WORD"))
            locctr += 3;
        else if (strcmp(opcode, "BYTE") == 0)
            locctr += find_length(oprand);
        else if (strcmp(opcode, "RESW") == 0)
            locctr += atoi(oprand) * 3;
        else if (strcmp(opcode, "RESB") == 0)
            locctr += atoi(oprand);
        else if(is_opcode(opcode) == 1)
            locctr += 3;
        else if(!strcmp(opcode,"END")){
        	fgets(line,MAX,f);
            lc++;
            m = tokeniser(line);    
        	exit(0);
        }
        else
            printf("Invalid Opcode on line : %d\n",lc);
        fgets(line,MAX,f);
        lc++;
        m = tokeniser(line); 

    }
    // printf("sfdsdfsf");
    // printf("len=%x",locctr);
    // fprintf(len,"%x",locctr);
	return 0; 
} 
