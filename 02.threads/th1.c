/* 
	Programa que muestra como crear threads
	
	compilar con:		gcc th1.c -o th1 -lposix4 -lpthread
	Compilar linux:		gcc th1.c -o th1 -lrt -lpthread
	
	Ejecutar con: 		./th1
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Prototipos de las funciones que ejecutan los threads */
void *func1 (void *);
void *func2 (void *);

/* Declaracion de los threads */
pthread_t thread1, thread2, thmain;
pthread_attr_t attr;	/*atributos de los threads*/

/* Definicion de las funciones func1 y func2 */
void *func1 (void *arg)
{
	pthread_t tid = pthread_self();  /*se asigna un identificador de thread*/
	printf("Soy el thread 1 y voy a ejecutar func1 \n");
	sleep(2);
	printf("Soy el thread 1 y he terminado de ejecutar la funcion 1\n");
	pthread_exit(NULL);	/* Provoca la terminaci¢n del thread*/
}

void *func2 (void *arg)
{
	pthread_t tid = pthread_self();  /*se asigna un identificador de thread*/
	printf("Soy el thread 2 y voy a ejecutar func2 \n");
	sleep(5);
	printf("Soy el thread 2 y he terminado de ejecutar la funcion 2\n");
	pthread_exit(NULL);	/* Provoca la terminaci¢n del thread*/

}

/* Funci¢n main */
int main(void)
{
	thmain = pthread_self(); /*La propia funci¢n main es un thread*/

	pthread_attr_init (&attr);	/*inicializa los par metros de los threads por defecto*/

	printf("Soy la funcion main y voy a lanzar los dos threads \n");
	pthread_create (&thread1, &attr, func1, NULL);
	pthread_create (&thread2, &attr, func2, NULL);

	printf("Soy main: he lanzado los dos threads y termino\n");

	pthread_exit(NULL);
}

