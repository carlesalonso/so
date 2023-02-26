/* mutex2.c: Programa que muestra el empleo de mutex con threads 
 	version incorrecta sin seccion de entrada/salida

	Compilar linux:		gcc -o mutexth2 mutexth2.c -lpthread 
	
	Ejecutar con: 		./mutexth2
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>  /* Para la funcion sched_yield() */

#define MAXLONG 100

/* Prototipos de funciones que ejecutan los threads */
void *func1 (void*); 
void *func2 (void*); 

/* Declaracion de los threads */
pthread_t thread1, thread2;

/* Declaracion del objeto atributo */
pthread_attr_t attr;

/* Declaracion del mutex */
pthread_mutex_t exmut;

/* Definicion de la funcion func1 */
void *func1 (void *arg)
{
	char buffer[MAXLONG];
	char *c;

	sprintf (buffer, "Soy el thread 1 y estoy escribiendo un mensaje en pantalla");
	c = buffer;
	
	/* Seccion de entrada: operacion P(S) */
	//pthread_mutex_lock (&exmut);
	
	/* Seccion critica: Escritura en pantalla */
	while (*c != '\0')
	{
		fputc (*c, stdout);
		c++;
		/* Forzamos la expulsion de la CPU con sched_yield */
		sched_yield();
	}
	fputc('\n', stdout);
	/* Fin de la seccion critica*/
	
	/* Seccion de salida: operacion V(S) */
	//pthread_mutex_unlock (&exmut);

	pthread_exit (NULL);
}

/* Definicion de la funcion func2 */
void *func2 (void *arg)
{
	char buffer[MAXLONG];
	char *d;

	sprintf (buffer, "Soy el thread 2 y estoy escribiendo un mensaje en pantalla");
	d = buffer;
	
	/* Seccion de entrada: operacion P(S) */
	//pthread_mutex_lock (&exmut);
	
	/* Seccion critica: Escritura en pantalla */
	while (*d != '\0')
	{
		fputc (*d, stdout);
		d++;
		/* Forzamos la expulsion de la CPU con sched_yield */
		sched_yield();
	}
	fputc('\n', stdout);
	/* Fin de la seccion critica*/
	
	/* Seccion de salida: operacion V(S) */
	//pthread_mutex_unlock (&exmut);

	pthread_exit (NULL);
}

int main(int argc, char *argv[])
{
	/* Inicializacion del objeto atributo */
	pthread_attr_init (&attr);

	/* Inicializacion del mutex */
	pthread_mutex_init (&exmut, NULL);

	printf ("Soy la funcion main y voy a lanzar los dos threads \n");
	pthread_create (&thread1, &attr, func1, NULL);
	pthread_create (&thread2, &attr, func2, NULL);
	printf ("Soy main: he lanzado los threads y termino \n");

	pthread_exit (NULL);

}
