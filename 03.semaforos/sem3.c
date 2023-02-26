/* ejemplo de uso de semaforos no nombrados para sincronizar la ejecucion de dos procesos 

	Compilar linux: 		gcc sem3.c -o sem3 -pthread
	
	Ejecutar con:		./sem3
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

sem_t *sem_1, *sem_2;	// declaramos un puntero para el identificador de los sem�foros

int main(void)
{
	int i;
	pid_t hijo;
	
	printf("Creando semaforos .....\n");

	/* comprueba si ya existe el semaforo del padre y sino lo crea desbloqueado (1)*/
	sem_1=sem_open("/sem_1", O_CREAT, 0644, 1);
	if (sem_1==(sem_t *)-1)
		perror("Error creando semaforo 1");

		/* comprueba si ya existe el semaforo del hijo y sino lo crea ya bloqueado (0)*/
	sem_2=sem_open("/sem_2", O_CREAT, 0644, 0);
	if (sem_2==(sem_t *)-1)
		perror("Error creando semaforo 2");

	printf("Creando proceso hijo .....\n");

	/* creamos el hijo */
	hijo=fork() ;

	switch(hijo)
	{
		case -1:
			
			printf("error creando proceso hijo\n");
			exit(0);
			
		case 0:	/* estamos en el hijo, valores pares */
			printf("Soy el hijo con PID:%d\n", getpid());
			
			for (i=2;i<=20;i+=2)
			{
				sem_wait(sem_2);	/* espera que el padre libere su sem�foro */
				printf("hijo  valor:%d\n",i);
				sleep(1);
				sem_post(sem_1); /* activa al padre */
			}

			/* libero sem�foros */
			sem_close(sem_1);
			sem_close(sem_2);

			printf("Soy el hijo y termino.....\n");
		break;

		default: /*estamos en el padre, valores impares */
			printf("Soy el padre con PID:%d\n", getpid());
			for(i=1;i<=20;i+=2)
			{
				sem_wait(sem_1);	/* espera que el hijo libere su sem�foro */
				printf("padre valor:%d\n",i);
				sleep(1);
				sem_post(sem_2); /* activa al hijo */
			}

			/* libero sem�foros */
			sem_close(sem_1);
			sem_close(sem_2);

			printf("Soy el padre espero que termine el hijo .....\n");
			wait(0); /* Esperar que acabe el hijo */

			printf("Soy el padre destruyo los semaforos y termino.....\n");
			sem_unlink("/sem_2");
			sem_unlink("/sem_1");

		
	}
	exit(0);
}

