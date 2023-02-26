/* Ejemplo Ejemplo de uso de la funcion  execl()
	Cambia la imagen en memoria de un proceso 

	Compilar con:		gcc p3.c -o p3
	
	Ejecutar con:		./p3
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

int main (void)
{
  pid_t childpid;
  childpid = fork();

  if (childpid == -1)
  {
	perror("Error al crear el hijo");
	exit(1);
  }
  else if (childpid ==0)
  {
	printf("Soy el hijo y voy a ejecutar ls -l\n");
	if (execl("/bin/ls", "ls", "-l", NULL) <0)
	{
	  perror("Error al ejecutar ls\n");
	  exit (1);
	}
  }
  else
  {
	printf("Soy el padre, espero al hijo y termino\n");
	wait(0); 
  }
  exit(0);
}
