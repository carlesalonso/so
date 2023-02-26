/* 
	Programa que muestra el paso de parametros en threads
	
	Compilar linux:		gcc th3.c -o th3 -lpthread
	
	Ejecutar con: 		./th3
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Prototipos de las funciones que ejecutan los threads */
void *func1 (void *);

// Estructura que contiene los datos a pasar como par�metros
// Un �nico par�metro se puede pasar directamente con el operador &
typedef struct
{
	int dato1,dato2;
}datos;

/* Declaracion de los threads */
pthread_t thread1, thmain;
pthread_attr_t attr;	/*atributos de los threads*/

/* Definicion de las funciones func1 y func2 */
void *func1 (void *arg)
{
	int a,b;
	datos *p= (datos *) (arg);

	pthread_t tid = pthread_self();  /*se asigna un identificador de  thread*/
	a=(p->dato1);
	b=(p->dato2);
	printf("Soy el thread 1 y voy a ejecutar func1 \n");
	printf("La multiplicacion es %d\n",a*b);
	printf("Soy el thread 1 y he terminado de ejecutar la funcion 1\n");
	pthread_exit(NULL);	/* Provoca la terminaci�n del thread*/
}


/*Funcion main*/
int main(void)
{
	datos param;

	param.dato1=6;
	param.dato2=8;
	
	thmain = pthread_self();   /*La propia funcion main es un thread*/
	pthread_attr_init (&attr);	/*inicializa los par�metros de los	threads por defecto*/
	
	printf("Soy la funcion main y voy a lanzar el thread con parametros %dx%d \n", param.dato1, param.dato2);
	pthread_create (&thread1, &attr, func1, &param);
	
	printf("Soy main: he lanzado el thread y termino\n");
	pthread_exit(NULL);
}

