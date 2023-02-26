/* 
	Programa que muestra el cambio de prioridad
	
	Compilar linux:		gcc th4.c -o th4  -lpthread
	
	Ejecutar con: 		./th4
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sched.h>
#define HIGHPRIORITY 10


/* Prototipos de las funciones que ejecutan los threads */
void *func (void *);


/* Declaracion de los threads */
pthread_t thread, thmain;
pthread_attr_t attr;	/*atributos de los threads*/
struct sched_param param;

/* Definicion de las funciones func1 y func2 */
void *func (void *arg)
{
	pthread_t tid = pthread_self();  /*se asigna un identificador de  thread*/

	printf("Soy el thread 1 y voy a ejecutar func1 \n");
	sleep(5);
	printf("Soy el thread 1 y he terminado de ejecutar la funcion 1\n");
	pthread_exit(NULL);	/* Provoca la terminaci�n del thread*/
}


/*Funci�n main*/
int main (void)
{
  
  if (pthread_attr_init(&attr))
  {
	  perror("No puedo inicializar atributos"); 
	  exit(-1);
  }

  if (pthread_create(&thread, &attr, func, NULL))
  { 
	  perror("No puedo crear el thread"); 
	  exit(-1);
  }

  if(pthread_attr_setschedpolicy (&attr, SCHED_FIFO))
		perror("No puedo cambiar el planificador"); 

  if (pthread_attr_getschedparam(&attr, &param))
		perror ("No puedo obtener los parametros");
  else
  {
	param.sched_priority = HIGHPRIORITY;
	if (pthread_attr_setschedparam(&attr, &param))
		perror("No puedo cambiar la prioridad");
  }

	printf("Soy main: he lanzado el thread y termino\n");
	pthread_exit(NULL);

}
