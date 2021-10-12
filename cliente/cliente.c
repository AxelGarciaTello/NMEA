#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "estructura.h"

#define PUERTO  5000
#define DIR_IP "127.0.0.1"

int main(){
  LOCALIZACION loc;

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

	if (read (sockfd, &loc, sizeof(LOCALIZACION)) < 0)
	{
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
	}
	printf("Tiempo: %s\n", loc.tiempo);
	printf("Latitud: %s\n", loc.latitud);
	printf("NS: %c\n", loc.NS);
	printf("Longitud: %s\n", loc.longitud);
	printf("EW: %c\n", loc.EW);

  close(sockfd);
  return 0;
}
