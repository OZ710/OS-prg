#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct fp
 {
   char label[20],opcode[20],operand[20];
 }s[100];  

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
        else if ((hexVal[i]>='A' && hexVal[i]<='F') ||(hexVal[i]>='A' && hexVal[i]<='F') ) 
        { 
            dec_val += (hexVal[i] - 55)*base;  
            base = base*16; 
        } 
    } 
      
    return dec_val; 
} 
void main()
 {
  char optab[32][100]={"ADD","ADDF","AND","COMP","DIV",
                  "J","JEQ","JGT","JLT","JSUB","LDA",
                  "LDB","LDCH","LDL","LDX","LPS","MUL",
                  "RD","OR","RSUB","SSK","STA","STB","STCH",
                  "STI","STL","STSW","STX","SUB","TD",
                  "TIX","WD"},
       op_values[32][100]={"18","58","40","28","24","3C","30","34",
                   "38","48","00","68","50","08","04","D0",
                   "20","D8","44","4C","EC","0C","78","54",
                   "D4","14","E8","10","1C","E0","2C","DC"};

   int op_size=32;              
   FILE *f1,*f2,*f4,*f6;
   int i=0,j=0,k=0,count=0,loctr=0,space=0;//i to traverse the file,j to iterate single line of a file
   char inst[100],temp[100],out[100]="";
   f1 = fopen("program2.txt","r");
   f2 = fopen("temp.txt","w"); 
   f4 = fopen("SYMTAB.txt","w");

   while(!feof(f1))
      {
         fgets(inst,100,f1);
        
         if(strcmp(out,inst)==0)
          break;
         strcpy(out,inst);
         while(j<strlen(inst)-1)// to find the number of fields in each instruction
           {
             if(inst[j]==' ' )
               {   
                     
                  while(inst[j]==' ' )
                  {
                      j++;
                  } 
                  count++;
                  space++;
                  while((inst[j]!=' ' ) && j<strlen(inst)-1)
                  {
                     j++;
                  }
                  if(j<strlen(inst)-1)
                    {
                      while((inst[j]==' ' ) && j<strlen(inst)-1)
                        j++;
                      if(j<strlen(inst)-1)
                      {
                        while((inst[j]!=' ' ) && j<strlen(inst)-1)
                          j++;
                        count++;
                        if(j<strlen(inst)-1)
                        {
                          while((inst[j]==' ' ) && j<strlen(inst)-1)
                            j++;
                          if(j<strlen(inst)-1)
                            {
                              count++;
                              break;
                            }  
                        }
                      }
                    }
                  
               }  
             else
             {
              
              while((inst[j]!=' ' ) && j<strlen(inst)-1)
                  { 
                     j++;
                  }
               
                  count++;
                  if(j<strlen(inst)-1)
                    {
                      while((inst[j]==' ' ) && j<strlen(inst)-1)
                        j++;
                      if(j<strlen(inst)-1)
                      {
                        while((inst[j]!=' ' ) && j<strlen(inst)-1)
                          j++;
                        count++;
                        if(j<strlen(inst)-1)
                        {
                          while((inst[j]==' ' ) && j<strlen(inst)-1)
                            j++;
                          if(j<strlen(inst)-1)
                            {
                              count++;
                              break;
                            }  
                        }
                      }
                    }
                   // printf("%d ",count);
             }
           }
         if(i==0)
         {
            f6=fopen("prg.txt","w");
            j=0,k=0;
            char tem[100];
            if(count==3)
            {
                if(space==1)
                {
                    while(inst[j]==' ' )
                      j++;
                    while(inst[j]!=' ' )
                      tem[k++]=inst[j++];
                }
                else
                {
                      while(inst[j]!=' ' )
                      tem[k++]=inst[j++];
                }
                tem[k]='\0';
                
                fprintf(f6,"%s",tem);
            }
            else
            {
                fprintf(f6,"------");
            }
         } 
         
         if(count==1)// single field(only opcode)
             {
               k=0;
               j=0;
               strcpy(s[i].label,"-");
              
                  
               if(space==1)             
                 { 
                      while(inst[j]==' ' )
                        {
                          j++;
                        }
                      int p=j;   
                      while(p<=strlen(inst)-1 && inst[p]!=' ' && inst[p]!='\n')
                       {
                        temp[k++]=inst[p++];
                       }   
                       temp[k]='\0';
                      k=0;
                      
                      if(strcmp(temp,"END")==0)
                       {
                        while(j<strlen(inst) && inst[j]!=' ' && inst[j]!='\n')
                         {
                           s[i].opcode[k++]=inst[j];
                          
                           j++;
                         }  
                          s[i].opcode[k]='\0';
                         strcpy(s[i].operand,"-"); 
                        
                       } 
                      else
                       {
                        while(j<strlen(inst) && inst[j]!=' '  && inst[j]!='\n')
                        {
                         s[i].opcode[k++]=inst[j];
                         j++;
                        } 
                        s[i].opcode[k]='\0';
                        strcpy(s[i].operand,"-\n");  
                       }   
                 } 
               else
                 {
                     int p=j;   
                      while(p<=strlen(inst)-1 && inst[p]!=' ' && inst[p]!='\n')
                      {
                        temp[k++]=inst[p++];
                      }   
                      k=0;
                     if(strcmp(temp,"END")==0)
                       {
                        while(j<strlen(inst) && inst[j]!=' '  && inst[j]!='\n' )
                         {
                           s[i].opcode[k++]=inst[j];
                           
                           j++;
                         }  
                         s[i].opcode[k]='\0';
                         strcpy(s[i].operand,"-"); 
                         
                       } 
                     
                      else
                       {
                        while(j<strlen(inst) && inst[j]!=' '  && inst[j]!='\n')
                        {
                         s[i].opcode[k++]=inst[j];
                         j++;
                        } 
                        s[i].opcode[k]='\0';
                        strcpy(s[i].operand,"-\n");  
                       }   
                 }   
              

             } 
         else if(count==2)// 2 fields(opcode,operand)
           {
              k=0;
              j=0;
              strcpy(s[i].label,"-");
              if(space==1)
              {
                 while(inst[j]==' ' )
                  {
                      j++;
                  }
                  
              while(inst[j]!=' ' )
                  {
                     s[i].opcode[k++]=inst[j];
                     j++;
                  }     
              while(inst[j]==' ' )
                  {
                      j++;
                  }
                  k=0;
              while(j<strlen(inst) && inst[j]!=' ')
                  {
                     s[i].operand[k++]=inst[j];
                     j++;
                  }  
                 if(inst[j]==' ' )
                   s[i].operand[k++]='\n';      
                  
              }
              else
              {
                 while(inst[j]!=' ' )
                  {
                     s[i].opcode[k++]=inst[j];
                     j++;
                  }     
                 while(inst[j]==' ' )
                  {
                      j++;
                  }
                  k=0;
               while(j<strlen(inst) && inst[j]!=' ')
                  {
                     s[i].operand[k++]=inst[j];
                     j++;
                  }  
                if(inst[j]==' ' )
                   s[i].operand[k++]='\n';         
              }
           }   
        else // 3 fields(label,opcode,operand)
          {
             j=0;
             k=0;
             if(space!=1)
             {
              
                  while(inst[j]!=' ' )
                      {
                         s[i].label[k++]=inst[j];
                         j++;
                      }  
                 while(inst[j]==' ' )
                      {
                          j++;
                      } 
                      k=0; 
                 while(inst[j]!=' ' )
                      {
                         s[i].opcode[k++]=inst[j];
                         j++;
                      }          
                 while(inst[j]==' ' )
                      {
                          j++;
                      } 
                      k=0;
                  while(j<strlen(inst) && inst[j]!=' ')
                      {
                         s[i].operand[k++]=inst[j];
                         j++;
                      }   
                   if(inst[j]==' ' )
                    s[i].operand[k++]='\n';  
                 //printf("%s %s %s\n",s[i].label,s[i].opcode,s[i].operand);
             }
            else
            {
               while(inst[j]==' ' )
                j++;
               while(inst[j]!=' ' )
                  {
                     s[i].label[k++]=inst[j];
                     j++;
                  }  
               while(inst[j]==' ' )
                  {
                      j++;
                  } 
                  k=0; 
               while(inst[j]!=' ' )
                  {
                     s[i].opcode[k++]=inst[j];
                     j++;
                  }          
               while(inst[j]==' ' )
                  {
                      j++;
                  } 
                  k=0;
                while(j<strlen(inst) && inst[j]!=' ')
                  {
                     s[i].operand[k++]=inst[j];
                     j++;
                  }
                  if(inst[j]==' ' )
                   s[i].operand[k++]='\n';    
                  
            } 
                     

          }        
         i++;
         j=0;
         count=0;    
         space=0;
      }
  /*for(int x=0;x<=i;x++)
   {
     printf("%s %s %s\n",s[x].label,s[x].opcode,s[x].operand);
   }*/
   fclose(f1);


   //first pass 
   int tot=i;
   i=0;
   int stad,flag=0;
   char sym[20][20]={""},hex[5];
   k=0;
   if(strcmp(s[i].opcode,"START")==0) //opcode is start
   {
      loctr=hexadecimalToDecimal(s[i].operand);
      stad=loctr;
      sprintf(hex,"%x",loctr);
      fprintf(f2,"%s %s %s"," ",s[i].opcode,s[i].operand);
      i++;
   }
   else// start is not present
    {
      loctr=0;
      stad=loctr;
      sprintf(hex,"%x",loctr);
      fprintf(f2,"%s %s %s\n"," ","START",hex);
    }  
  while(i<tot-1)// to traverse remaining instructions till END
    {
        if(strcmp(s[i].label,"-")!=0)
          {
            
              if(k==0)
                {
                  strcpy(sym[k],s[i].label);
                  k++;
                  fprintf(f4,"%s %s\n",s[i].label,hex);
                   
                }
             else
               {
                 flag=0;
                 for (int m=0; m <k ; ++m)
                  {
                    if(strcmp(s[i].label,sym[m])==0)
                     {
                       flag=1;
                       break;
                     }
                  }
                 if(flag==1)
                 {
                  printf("Error in line %d",i+1);
                 }
                 else
                 {
                    strcpy(sym[k],s[i].label);
                    k++;
                    fprintf(f4,"%s %s\n",s[i].label,hex);
                 }
               } 
          }
         
        flag=0;
        int z=0;
        while(z<32)
         {
          if(strcmp(s[i].opcode,optab[z])==0)
            {
              flag=1;
              break;
            }
            z++;
         }  
         int fl=0;
        if(flag==1)
        {
           loctr+=3;
        }
        else if(strcmp(s[i].opcode,"WORD")==0)
        {
          loctr+=3;
        }
        else if(strcmp(s[i].opcode,"RESW")==0)
        {
          loctr=loctr+(3*atoi(s[i].operand));
        }
        else if(strcmp(s[i].opcode,"RESB")==0)
        {
          loctr=loctr+atoi(s[i].operand);
        }
       
        else if(strcmp(s[i].opcode,"BYTE")==0)
        {
          if(s[i].operand[0]=='c' || s[i].operand[0]=='C')
          {
             loctr+=(strlen(s[i].operand)-4);
          }
          else
            loctr+=((strlen(s[i].operand)-4)/2);
        }
        else
        {
           printf("%s ",s[i].opcode);
           printf("Invalid operation code\n");
        }
         
        fprintf(f2,"%s %s %s",hex,s[i].opcode,s[i].operand);
        i++;
         sprintf(hex,"%x",loctr);
      }
      if(s[i].operand[strlen(s[i].operand)-1]=='\n')
          s[i].operand[strlen(s[i].operand)-1]='\0';
      fprintf(f2,"%s %s %s",hex,s[i].opcode,s[i].operand);
     
    int plen=loctr-stad;
    FILE *f5;
    f5 = fopen("length.txt","w");
    fprintf(f5,"%x",plen );
    fclose(f2);
    fclose(f4);
    fclose(f5);
 }      
