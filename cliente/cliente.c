#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define TAM_BUFFER 100

#define PUERTO  5000
#define DIR_IP "127.0.0.1"

int main(){
  char leer_mensaje[TAM_BUFFER];
  char tiempo[100],
       latitud[100],
       longitud[100],
       NS[100],
       EW[100];

  int sockfd;
  struct sockaddr_in direccion_servidor;

  memset(&direccion_servidor,0,sizeof(direccion_servidor));
  direccion_servidor.sin_family = AF_INET;
  direccion_servidor.sin_port = htons(PUERTO);

  if(inet_pton(AF_INET, DIR_IP, &direccion_servidor.sin_addr) <= 0){
    perror("Ocurrio un error al momento de asignar la dirección IP");
    exit(1);
  }

  printf("Creando Socket...\n");
  if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("Ocurrio un problema en la creación del socket");
    exit(1);
  }

  printf("Estableciendo conexión...\n");
  if(connect(sockfd,(struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor))<0){
    perror("Ocurrio un problema al establecer la conexión");
    exit(1);
  }

  printf("Recibiendo información...\n");

	if( write(sockfd, "Soy el Cliente", 15) < 0 )
	{
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(1);
	}

	if (read (sockfd, tiempo, TAM_BUFFER) < 0)
	{
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
	}
	printf ("Tiempo: %s\n", tiempo);

	if( write(sockfd, "Soy el Cliente", 15) < 0 )
	{
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(1);
	}

	if (read (sockfd, latitud, TAM_BUFFER) < 0)
	{
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
	}
	printf ("latitud: %s\n", latitud);

	if( write(sockfd, "Soy el Cliente", 15) < 0 )
	{
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(1);
	}

	if (read (sockfd, NS, TAM_BUFFER) < 0)
	{
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
	}
	printf ("NS: %s\n", NS);

	if( write(sockfd, "Soy el Cliente", 15) < 0 )
	{
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(1);
	}

	if (read (sockfd, longitud, TAM_BUFFER) < 0)
	{
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
	}
	printf ("Longitud: %s\n", longitud);

	if( write(sockfd, "Soy el Cliente", 15) < 0 )
	{
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(1);
	}

	if (read (sockfd, EW, TAM_BUFFER) < 0)
	{
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
	}
	printf ("EW: %s\n", EW);

  close(sockfd);
  return 0;
}
