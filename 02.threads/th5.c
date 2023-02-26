/* 
	Programa que muestra el uso de pthread_cancel
	
	
	Compilar linux:		gcc th5.c -o th5  -lpthread
	
	Ejecutar con: 		./th5
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


/* Prototipos de las funciones que ejecutan los threads */
void *func1 (void *);


/* Declaracion de los threads */
pthread_t thread1, thmain;
pthread_attr_t attr;	/*atributos de los threads*/

/* Definicion de las funciones */
void *func1 (void *arg)
{
	pthread_t tid;
	int i;
		
	tid=pthread_self();  //se asigna un identificador de  thread

 	// permite la cancelacion del thread
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

	printf("Soy el thread 1 [TID:%u] y voy a esperar\n",tid);
	
	sleep(10);				// punto de cancelacion
	pthread_testcancel();	// punto de cancelacion
	
	printf("Soy el thread 1 [TID:%u] y he terminado\n", tid);
	pthread_exit(NULL);	
}


/*Funcion main*/
int main(void)
{

	thmain = pthread_self();   /*La propia funcion main es un thread*/
	pthread_attr_init (&attr);	/*inicializa los parametros de los	threads por defecto*/
	
	printf("Soy main [TID: %u] y voy a lanzar el thread\n", thmain);
	pthread_create (&thread1, &attr, func1, NULL);
	
	sleep(2);
	if (pthread_cancel(thread1)!=0)
        	perror("Error cancelando thread");
	else
		printf("Soy main [TID: %u] he cancelado el thread [TID: %d] y termino\n", thmain, thread1);
	
	pthread_exit(NULL);
}

