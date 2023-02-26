/* Ejemplo de creacion de procesos y espera con la funcion wait()

	Compilar con:		gcc p2.c -o p2
	
	Ejecutar con:		./p2
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

int main(void)
{
   pid_t childpid, childdead;
   int i;

  childpid = fork();

  if (childpid == -1)
  {
		perror("fork no pudo crear el hijo");
		exit(1);
  }
  else  if (childpid == 0)
  {
       printf ("Soy el hijo (PID %d) y mi padre es (PID %d), voy a contar hasta 100000 \n", getpid(), getppid());
       for (i=0;i<100000; i++) {}
  }
  else 
  {
	  printf("Soy el padre (PID %d) y voy a esperar a mi hijo (PID %d)\n", getpid(), childpid);
	  if ((childdead = wait(0))==-1) 
			perror("No he podido esperar al hijo");
	  else
			printf("Mi hijo con PID %d, ha muerto\n",childdead);
  }
  
  exit(0);
}
