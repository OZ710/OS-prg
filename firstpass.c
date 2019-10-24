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
   FILE *f1,*f2,*f3,*f4,*f6;
   int i=0,j=0,k=0,count=0,loctr=0,space=0;//i to traverse the file,j to iterate single line of a file
   char inst[100],temp[100];
   f1 = fopen("firstpass.txt","r");
   f2 = fopen("temp.txt","w"); 
   f4 = fopen("SYMTAB.txt","w");
   while(!feof(f1))
      {
         fgets(inst,100,f1);
         while(j<strlen(inst)-1)// to find the number of fields in each instruction
           {
             if(inst[j]==' ')
               {      
                  while(inst[j]==' ')
                  {
                      j++;
                  } 
                  count++;
                  space++;
                  while(inst[j]!=' ' && j<strlen(inst)-1)
                  {
                     j++;
                  }
                  if(j<strlen(inst)-1)
                    {
                      while(inst[j]==' ' && j<strlen(inst)-1)
                        j++;
                      if(j<strlen(inst)-1)
                      {
                        while(inst[j]!=' ' && j<strlen(inst)-1)
                          j++;
                        count++;
                        if(j<strlen(inst)-1)
                        {
                          while(inst[j]==' ' && j<strlen(inst)-1)
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
              while(inst[j]!=' ' && j<strlen(inst)-1)
                  {
                     j++;
                  }
                  count++;
                  if(j<strlen(inst)-1)
                    {
                      while(inst[j]==' ' && j<strlen(inst)-1)
                        j++;
                      if(j<strlen(inst)-1)
                      {
                        while(inst[j]!=' ' && j<strlen(inst)-1)
                          j++;
                        count++;
                        if(j<strlen(inst)-1)
                        {
                          while(inst[j]==' ' && j<strlen(inst)-1)
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
                    while(inst[j]==' ')
                      j++;
                    while(inst[j]!=' ')
                      tem[k++]=inst[j++];
                }
                else
                {
                      while(inst[j]!=' ')
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
              
                  strcpy(s[i].operand,"-\n");
               if(space==1)             
                 { 
                      while(inst[j]==' ')
                        {
                          j++;
                        }
                      int p=j;   
                      while(p<=strlen(inst) && inst[p]!=' ')
                       {
                        temp[k++]=inst[p++];
                       }   
                      k=0;
                      if(strcmp(temp,"END")==0)
                       {
                        while(j<strlen(inst) && inst[j]!=' ')
                         {
                           s[i].opcode[k++]=inst[j];
                           j++;
                         }   
                       } 
                      else
                       {
                        while(j<strlen(inst) && inst[j]!=' ')
                        {
                         s[i].opcode[k++]=inst[j];
                         j++;
                        }   
                       }   
                 } 
               else
                 {
                     int p=j;   
                     while(p<=strlen(inst)-1)
                      {
                        temp[k++]=inst[p++];
                      }   
                      k=0;
                     if(strcmp(temp,"END")==0)
                      {
                        while(j<strlen(inst) && inst[j]!=' ')
                        {
                           s[i].opcode[k++]=inst[j];
                           j++;
                        }   
                      } 
                     else
                     {
                      while(j<strlen(inst) && inst[j]!=' ')
                        {
                           s[i].opcode[k++]=inst[j];
                           j++;
                        }   
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
                 while(inst[j]==' ')
                  {
                      j++;
                  }
                  
              while(inst[j]!=' ')
                  {
                     s[i].opcode[k++]=inst[j];
                     j++;
                  }     
              while(inst[j]==' ')
                  {
                      j++;
                  }
                  k=0;
              while(j<strlen(inst) && inst[j]!=' ')
                  {
                     s[i].operand[k++]=inst[j];
                     j++;
                  }  
                 if(inst[j]==' ')
                   s[i].operand[k++]='\n';      
                  
              }
              else
              {
                 while(inst[j]!=' ')
                  {
                     s[i].opcode[k++]=inst[j];
                     j++;
                  }     
                 while(inst[j]==' ')
                  {
                      j++;
                  }
                  k=0;
               while(j<strlen(inst) && inst[j]!=' ')
                  {
                     s[i].operand[k++]=inst[j];
                     j++;
                  }  
                if(inst[j]==' ')
                   s[i].operand[k++]='\n';         
              }
           }   
        else // 3 fields(label,opcode,operand)
          {
             j=0;
             k=0;
             if(space!=1)
             {
                  while(inst[j]!=' ')
                      {
                         s[i].label[k++]=inst[j];
                         j++;
                      }  
                 while(inst[j]==' ')
                      {
                          j++;
                      } 
                      k=0; 
                 while(inst[j]!=' ')
                      {
                         s[i].opcode[k++]=inst[j];
                         j++;
                      }          
                 while(inst[j]==' ')
                      {
                          j++;
                      } 
                      k=0;
                  while(j<strlen(inst) && inst[j]!=' ')
                      {
                         s[i].operand[k++]=inst[j];
                         j++;
                      }   
                   if(inst[j]==' ')
                   s[i].operand[k++]='\n';    
             }
            else
            {
               while(inst[j]==' ')
                j++;
               while(inst[j]!=' ')
                  {
                     s[i].label[k++]=inst[j];
                     j++;
                  }  
               while(inst[j]==' ')
                  {
                      j++;
                  } 
                  k=0; 
               while(inst[j]!=' ')
                  {
                     s[i].opcode[k++]=inst[j];
                     j++;
                  }          
               while(inst[j]==' ')
                  {
                      j++;
                  } 
                  k=0;
                while(j<strlen(inst) && inst[j]!=' ')
                  {
                     s[i].operand[k++]=inst[j];
                     j++;
                  }
                  if(inst[j]==' ')
                   s[i].operand[k++]='\n';    
            } 
                     

          }        
         i++;
         j=0;
         count=0;    
         space=0;
      }
   for(int x=0;x<=i;x++)
   {
     printf("%s %s %s\n",s[x].label,s[x].opcode,s[x].operand);
    // printf("%s\n",s[x].operand);
   }
   fclose(f1);


   //first pass 
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
   else
    loctr=0;// start is not present
  while(strcmp(s[i].opcode,"END")!=0)// to traverse remaining instructions till END
    {
         f3 = fopen("OPTAB.txt","r");
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
        while(!feof(f3))
         {
          char op[20],mne[10];
          fscanf(f3,"%s%s",op,mne);
          if(strcmp(s[i].opcode,op)==0)
            {
              flag=1;
              break;
            }
         }  
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
          int m=2,co=0;
          while(s[i].operand[m]!='\'')
          {
             co++;
             m++;
          }
          if(s[i].operand[0]=='c')
          {
             loctr+=co;
          }
          else
            loctr+=(co/2);
        }
        else
          printf("Invalid operation code");
        fprintf(f2,"%s %s %s",hex,s[i].opcode,s[i].operand);
        i++;
        sprintf(hex,"%x",loctr);
        fclose(f3);
    }
    fprintf(f2,"%s %s %s",hex,s[i].opcode,s[i].operand);
    int plen=loctr-stad;
    FILE *f5;
    f5 = fopen("length.txt","w");
    fprintf(f5,"%x",plen );
    fclose(f1);
    fclose(f2);
    fclose(f4);
    fclose(f5);
 }      
