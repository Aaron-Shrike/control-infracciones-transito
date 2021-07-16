#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>

#define MAX 20
#define LIM 50


// operacions basicas de datos simples

int leeEntero(char msje[], int min, int max)
{ int num;
  do{
     printf("%s", msje);
     scanf("%d", &num);
  }while(!(num>=min && num<=max));
  return num;
}

float leeReal(char msje[], float min, float max)
{ float num;
  do{
     printf("%s", msje);
     scanf("%f", &num);
  }while(!(num>=min && num<=max));
  return num;
}




//operaciones de vector enteros

void iniciaVE(int V[], int m)
{
 for(int i=0; i<m; i++)
 	V[i]=0;
}



//operaciones de vector reales
void iniciaVR(float V[], int m)
{
 for(int i=0; i<m; i++)
 	V[i]=0.0;
}


////operaciones de Tablas

void iniciaTabla(char T[][LIM], int m)
{
 for(int i=0; i<m; i++)
 	T[i][0]=NULL;
}

int validaTabla(char msje[], char T[][LIM], int tam)
{
 int opc;
 for(int i=0; i<tam; i++)
    printf("\n%d: %s",i+1, T[i]);

  opc=leeEntero(msje, 1, tam);
  return opc;

}

 char continuar (char msje[])
{
	char rpta;
   do{
   	printf("\n%s", msje);
      fflush(stdin);            
      scanf("%c",&rpta);
      rpta= toupper(rpta);
   }while(!(rpta=='S' || rpta== 'N'));
   return rpta;
}
