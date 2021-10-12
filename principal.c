#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include "servidor.h"
#include "procesos.h"
#include "signal.h"
#include "estructura.h"

LOCALIZACION loc;

int sockfd;
pthread_t tid;

void *funHilo(){
  int i;
  char caracteres[75];

  FILE *fp = fopen("nmea.txt","r");
  if(fp==NULL){
    perror("Error en la lectura del archivo\n");
    pthread_exit((void *)-1);
  }

  while(feof(fp)==0){
    fgets(caracteres,100,fp);
    if(caracteres[1]=='G' &&
       caracteres[2]=='P' &&
       caracteres[3]=='G' &&
       caracteres[4]=='G' &&
       caracteres[5]=='A'){
         for(i=0; i<8; i++)
            loc.tiempo[i] = caracteres[i+7];
         for(i=0; i<9; i++)
            loc.latitud[i] = caracteres[i+17];
         loc.NS = caracteres[28];
         for(i=0; i<10; i++)
            loc.longitud[i] = caracteres[i+30];
         loc.EW =caracteres[42];
         break;
       }
  }
  printf("Tiempo: %s\n", loc.tiempo);
  printf("Latitud: %s\n", loc.latitud);
  printf("NS: %c\n", loc.NS);
  printf("Longitud: %s\n", loc.longitud);
  printf("EW: %c\n", loc.EW);

  fclose(fp);
  pthread_exit((void *)0);
}

int main(){
  int cliente_sockfd;
  pid_t pid;

  if(signal(SIGCHLD, ISRsw) == SIG_ERR){
		perror("Error en la señal SIGCHLD\n");
		exit(EXIT_FAILURE);
	}
  if(signal(SIGINT, ISRsw) == SIG_ERR){
		perror("Error en la señal SIGINT\n");
		exit(EXIT_FAILURE);
	}

  printf("Leyendo archivo\n");
  pthread_create(&tid, NULL, funHilo, NULL);

  sockfd = iniServidor();

  while(1){
    printf("En espera de peticiones de conexión...\n");
    if((cliente_sockfd = accept(sockfd,NULL,NULL))<0){
      perror("Ocurrio algun problema al atender a un cliente");
      exit(EXIT_FAILURE);
    }
    pid = fork();
    if(!pid){
      atiendeCliente(cliente_sockfd);
    }
  }

  close(sockfd);

  return 0;
}
