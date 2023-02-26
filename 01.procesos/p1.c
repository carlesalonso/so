/* Ejemplo de creacion de procesos 

	Compilar con:		gcc p1.c -o p1
	
	Ejecutar con:		./p1
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main (void)
{
	pid_t pid;
	
	pid = fork();
	switch (pid)
	{
		case -1: perror ("No se ha podido crear el hijo");
			break;

		case 0: printf("Soy el hijo, mi PID es %d y mi PPID es %d\n", getpid(), getppid());
				break;

		default: printf ("Soy el padre, mi PID es %d y el PID de mi	hijo es %d\n", getpid(), pid);
	}
	exit(0);
}
