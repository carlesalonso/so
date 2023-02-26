/* 
	Ejemplo de uso de pthread_join
	
	
	Compilar linux:		gcc th2.c -o th2  -lpthread
	
	Ejecutar con: 		./th2
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

/* Definicion de las funciones f1 y f2 */
void *func1 (void *arg)
{
	printf("Soy el thread1 y estoy ejecutando func1 \n");
	sleep(4);
	printf("Soy el thread1 termino \n");
	pthread_exit(NULL);	
}

void *func2 (void *arg)
{
	int err;
	printf("Soy el thread2 y voy a esperar que thread1 termine \n");
	if (err =  pthread_join(thread1, NULL))
		printf ("Error al espear a th1 \n");
	else
	{
		printf("Soy th2, th1 ha terminado y estoy ejecutando func2 \n");
		sleep(2);
    }
	pthread_exit(NULL); 	
}

/* Funcion main */
int main(void)
{
	thmain = pthread_self();
	
	pthread_attr_init (&attr);	

	printf("Soy la funci�n main y voy a lanzar los dos threads \n");
	pthread_create (&thread1, &attr, func1, NULL);
	pthread_create (&thread2, &attr, func2, NULL);

	printf("Soy main: he lanzado los dos threads y termino\n");
	pthread_exit(NULL);
}

