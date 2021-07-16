/*
2.	La Municipalidad de Chiclayo desea que usted elabore un programa que
permita llevar el control de las infracciones de tránsito siendo los datos
a registrar:
-Placa del auto (5 dígitos alfanuméricos)
-Número de la papeleta (9 dígitos alfanuméricos)
-Año de la infracción
-Tipo de infracción (considere: sobrepasar límites de velocidad, pasar una luz roja,
no respetar las señales de tránsito, conducir en estado etílico,conducir sin
licencia)
-Deuda total
-Nombre del infractor
-Estado (pendiente o cancelado)

Realizar:

a.	Registrar una nueva infracción de tránsito.
b.	Realizar el pago de las infracciones de tránsito. 
c.	Mostrar el número de infracciones por tipo que ocurrieron en el año 2018.
d.	Mostrar ordenado ascendente por placa del auto.
e.	Dado el nombre del infractor mostrar que infracciones aun con deuda tiene
y cuál es su promedio de deuda.
f.	Quién es el infractor que registra la mayor deuda aun no cancelada.
g.	Mostrar el número de infracciones pendientes y canceladas cuya deuda
supere un valor ingresado.*/

#include "basicas.cpp"
#define MAXPLACA 6
#define MAXPAPELETA 10
#define MAXTIPO 5
#define MAXESTADO 2
struct Infraccion
{
 char placa[MAXPLACA];
 char numpapeleta[MAXPAPELETA];
 int fecha;
 int tipoinfraccion;
 float deuda;
 char nombre[LIM];
 int estado;
};
char TTipoinfraccion[MAXTIPO][LIM]={"Sobrepasar limites de velocidad", "Pasar una luz roja", "No respetar las señales de transito", "Conducir en estado etilico", "Conducir sin licencia"};
char TEstado[MAXESTADO][LIM]={"Pendiente", "Cancelado"};
//operaciones basicas para infraccion
void iniciainfraccion(Infraccion &I)
{
 I.placa[0]=NULL;
 I.numpapeleta[0]=NULL;
 I.fecha=0;
 I.tipoinfraccion=0;
 I.deuda=0.0;
 I.nombre[0]=NULL;
 I.estado=0;
}


void mostrarinfraccion(Infraccion &I)
{
 printf("\n Placa del auto: %s",I.placa);
 printf("\n Numero de papeleta: %s", I.numpapeleta);
 printf("\n Anio de la infraccion: %d",I.fecha);
 printf("\n Tipo de infraccion: %s",TTipoinfraccion[I.tipoinfraccion-1]);
 printf("\n Deuda Total: %.2f",I.deuda);
 printf("\n Nombre: %s",I.nombre);
 printf("\n Estado: %s",TEstado[I.estado-1]);
}

struct Controlinfracciones
{
  Infraccion *pI;
  int N;
};
 //operaciones basicass
void inicia( Controlinfracciones &CI)
{
	CI.pI= new Infraccion[MAX];
   CI.N=0;
}

void leeinfraccion(Infraccion &I,Controlinfracciones &CI)
{
	int flagpapeleta;
   do{
     printf("\n Ingrese placa (5 digitos): ");
     fflush(stdin);
     gets(I.placa);
    }while(!(strlen(I.placa)==MAXPLACA-1));

   do
   {
   	do{
    		printf("\n Ingrese numero de papeleta (9 digitos): ");
    		fflush(stdin);
    		gets(I.numpapeleta);
 		}while(!(strlen( I.numpapeleta)==MAXPAPELETA-1));
      flagpapeleta=0;
      for(int i=0;i<CI.N;i++)
      {
      	if(strcmp(I.numpapeleta, CI.pI[i].numpapeleta)==0)
         {
         	flagpapeleta=1;
         }
      }
      if(flagpapeleta==1)
      	printf(" Error, el numero de papeleta se repite\n");
   }while(!(flagpapeleta==0));

	I.fecha=leeEntero("\n Ingrese anio[1900-2018]: ", 1900, 2018);
   I.tipoinfraccion=validaTabla("\n Ingrese tipo de infraccion: ", TTipoinfraccion, MAXTIPO);
   I.deuda=leeReal("\n Ingrese deuda(soles): ", 0.0, 2000000.0);
   printf("\n Ingrese nombre: ");
   fflush(stdin);
   gets(I.nombre);
   I.estado=validaTabla("\n Ingrese: ", TEstado, MAXESTADO);
}

 void inserta( Controlinfracciones &CI, Infraccion &I){

  if(CI.N<MAX){
     CI.pI[CI.N]=I;
     CI.N++;
  }
  else
      printf("\n No hay espacio.....");
}
void leer(Controlinfracciones &CI)
{
  Infraccion I;

  iniciainfraccion(I);
  leeinfraccion(I,CI);
  inserta(CI,I);

}

void mostrar(Controlinfracciones &CI)
{
	if(CI.N>0)
   {
   	for(int i=0;i<CI.N;i++){
      	printf("\n\nInfractor Nro[%d]",i+1);
      	mostrarinfraccion(CI.pI[i]);
      }
   }else
   	printf("\nNo hay Datos");
         getch();
}
void liberar(Controlinfracciones &CI)
{
 delete[] CI.pI;
}

//reportes

void pago(Controlinfracciones &CI)
{
	int flag;
	char p[LIM];
   if(CI.N>0)
 	{
   	do
      {
    		printf("\n Ingrese numero de papeleta (9 digitos): ");
    		fflush(stdin);
    		gets(p);
      }while(!(strlen(p)==MAXPAPELETA-1));
      for(int i=0;i<CI.N;i++)
      {
      	if(strcmp(CI.pI[i].numpapeleta,p)==0)
         {
         	mostrarinfraccion(CI.pI[i]);
            flag=1;
            if(CI.pI[i].estado==1)
            {
            	if(continuar("\n Desea cancelar esta deuda?[S o N]: ")=='S')
               {
               	CI.pI[i].estado=2;
               }
            }
            else
            {
            	printf("\n\n La deuda se ha cancelado previamente.");
            }
         }
      }
      if(flag==0)
      printf("\n No existe la infraccion...");
   }
  else
    printf("\nNo hay datos.........");
 getch();
}

void infportipo(Controlinfracciones &CI)
{
	int c;
   if(CI.N>0)
   {
   	for(int i=0;i<5;i++)
      {
      	c=0;
      	printf("\n%s\n",TTipoinfraccion[i]);
         for(int j=0;j<CI.N;j++)
         {
         	if(CI.pI[j].tipoinfraccion-1==i)
            {
            	if(CI.pI[j].fecha==2018)
               {
               	c++;
               }
            }
         }
         printf("\Numero de veces que ocurrio en el 2018: %d\n",c);
      }
   }
   else
   	printf("\nNo hay datos...");
   getch();
}

void ordenarasc(Controlinfracciones &CI)
{
 	Infraccion aux;
   if(CI.N>0)
 	{

      for(int i=0;i<CI.N-1;i++)
        for(int j=i+1;j<CI.N;j++)
				if(strcmp(CI.pI[i].placa, CI.pI[j].placa)>0)
        		{
            	aux=CI.pI[i];
            	CI.pI[i]=CI.pI[j];
            	CI.pI[j]=aux;
        		}

      printf("\nInfracciones ordenadas ascendentemente por nro de placa.");
      mostrar(CI);
   }
   else
		printf("\nNo hay datos.........");
 	getch();
}

void consulta (Controlinfracciones &CI)
{
	int n=0;
	float sum;
	char nomb[LIM];
	nomb[0]=NULL;
	if(CI.N>0)
   {
   	printf("\nIngrese nombre: ");
      fflush(stdin);
      gets(nomb);
      for(int i=0;i<CI.N;i++)
      {
      	if(strcmp(CI.pI[i].nombre,nomb)==0)
         {
         	if(CI.pI[i].estado==1)
            {
            	mostrarinfraccion(CI.pI[i]);
               printf("\n");
            	sum+=CI.pI[i].deuda;
               n++; 
         	}
         }
      }
      if(n>0)
	  {
      	printf("\n El promedio de la deuda total es: %.2f",sum/n);
	  }
      else
	  {
      	printf("\n No tiene deudas.");
	  }
   }
  	else
   	printf("\nNo hay datos.........");
 	getch();
}

void mayordeuda(Controlinfracciones &CI)
{
	int pos,flag=0;
	float mayor=0.0;
	if(CI.N>0)
 	{
      for(int i=0;i<CI.N;i++)
         if(CI.pI[i].estado==1)
         {
         	 flag=1;
         	 if(CI.pI[i].deuda>mayor)
             {
             	mayor=CI.pI[i].deuda;
             	pos=i;
             }
         }
      if(flag==1)
      {
      	printf("\n Deuda mayor aun no cancelada es: %.2f",mayor);
      	printf("\n Nombre del infractor: %s",CI.pI[pos].nombre);
      }
      else
      {
      	printf("\n No hay deudas sin cancelar.");
      }
   }
	else
   printf("\nNo hay datos.........");
 getch();
}

void infmayorque(Controlinfracciones &CI)
{
	int v,x,y;
   if(CI.N>0)
   {
   	v=leeReal("\n Ingrese deuda minima: ", 0.0, 2000000.0);
      x=0;
      y=0;
      for(int i=0;i<CI.N;i++)
      {
      	if(CI.pI[i].deuda>v)
         {
         	if(CI.pI[i].estado==1)
            {
            	x+=1;
            }
            else
            {
            	y+=1;
            }
         }
      }
      printf("\n\nInfracciones pendientes: %d",x);
      printf("\nInfracciones canceladas: %d",y);
   }
   else
   	printf("\nNo hay datos...");
   getch();
}

void menu(Controlinfracciones &CI)
{
 int opc;
  do{
     //clrscr();
     printf("\n\n\n******* MUNICIPALIDAD DE CHICLAYO ************");
     printf("\n1.Registrar nueva infraccion");
     printf("\n2.Mostrar");
     printf("\n3.Pago");
     printf("\n4.Numero de infracciones por tipo - Anio 2018");
     printf("\n5.Ordenado ascendente(placa de auto)");
     printf("\n6.Consulta");
     printf("\n7.Infractor con mayor deuda no cancelada");
     printf("\n8.Infracciones pendientes y canceladas con deuda mayor a un valor");
     printf("\n9.Salir");
     opc=leeEntero("\nIngrese opcion: ",1,9);
     switch(opc)
     {
      case 1: leer(CI);
              break;
      case 2: mostrar(CI);
              break;
      case 3: pago(CI);
              break;
      case 4: infportipo(CI);
              break;
      case 5: ordenarasc(CI);
              break;
      case 6: consulta(CI);
              break;
      case 7: mayordeuda(CI);
              break;
      case 8: infmayorque(CI);
      		  break;
      case 9: liberar(CI);
              break;

     }
  }while(opc!=9);
}

int main()
{
  Controlinfracciones CI;
   inicia(CI);

   menu(CI);
   return 1;
}
