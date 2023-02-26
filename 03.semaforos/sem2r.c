/* ejemplo de uso de semaforos nombrados (seccion critica)

	Seccion de entrada/salida desactivadas

	Compilar linux: 		gcc sem2r.c -o sem2r -pthread
	
	Ejecutar con:		./sem2r
*/


#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <semaphore.h>
#include <sched.h>  /* Para la funcion sched_yield() */
#include <sys/stat.h>
#include <fcntl.h>

#define NUM_PROCESOS	10
#define BUFFER_SIZE	500

char buffer[BUFFER_SIZE];

int main (int argc, char *argv[])
{
	char *c;
	int i, n=NUM_PROCESOS;
	pid_t hijo;
	sem_t *semaforo;
	
	/* Crea el semaforo  nombrado */
	if((semaforo=sem_open("/semaforo", O_CREAT, 0644, 1))==(sem_t *)-1)
	{
		perror("No se puede crear el semaforo");
		exit(1);
	}
	/* Crea los procesos */
	for (i = 1; i<n; ++i)
	{
		hijo = fork();
		if (hijo==-1)
		{
			perror("No se puede crear el proceso");	exit(-1);
		}
		else if (hijo==0)	// si es un hijo terminar el for (solo el padre crea los hijos)
			break;
	}
	/* i actua como identificador del proceso */
	/* en el padre i==n */

	sprintf(buffer, "i:%d  proceso ID:%d  padre ID:%d\n",i, 
			getpid(), getppid());
	c = buffer;

	/********* Seccion de entrada ****
	if (sem_wait(semaforo) == -1)
	{
		perror("Semaforo no valido");
		exit(1);
	}
	**** Principio de la seccion critica *******/
	while (*c != '\0')
	{
		fputc(*c, stderr); fflush(stderr);
		c++;
		sched_yield();	/* liberamos la CPU */

	}
	/********** Fin de la seccion critica *******/
	
	/*********** Seccion de salida ************
	if (sem_post(semaforo) == -1)
	{
		perror("Semaforo no valido");
		exit(1);
	}
	********* Seccion Restante ************/
	sem_close(semaforo);
	// El Padre espera que terminen los hijos
	if(i==n)
	{
		printf("\nSoy el Padre [PID:%d] y voy a esperar que terminen todos los hijos\n", getpid());
		for(i=1;i<n;i++)
			wait(0);
		// Elimina el sem�foro nombrado
		sem_unlink("/semaforo");
	}
	exit(0);
}
