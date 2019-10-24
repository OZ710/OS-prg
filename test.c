
   
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
	char hex[10],n[10]="12af";
   
	 sprintf(hex,"%06s",n);       
	printf("%s\n",hex );/* code */
}

