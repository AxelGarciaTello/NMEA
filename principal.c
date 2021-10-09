#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include "servidor.h"
#include "procesos.h"
#include "signal.h"

char tiempo[9],
     latitud[10],
     longitud[11],
     NS[2],
     EW[2];

int sockfd;

void *funHilo(){
  int i;
  char caracteres[75];

  FILE *fp = fopen("nmea.txt","r");
  if(fp==NULL){
    perror("Error en la lectura del archivo\n");
  }

  while(feof(fp)==0){
    fgets(caracteres,100,fp);
    if(caracteres[1]=='G' &&
       caracteres[2]=='P' &&
       caracteres[3]=='G' &&
       caracteres[4]=='G' &&
       caracteres[5]=='A'){
         for(i=0; i<9; i++)
            tiempo[i] = caracteres[i+7];
         for(i=0; i<9; i++)
            latitud[i] = caracteres[i+17];
         NS[0] = caracteres[28];
         NS[1] = ' ';
         for(i=0; i<11; i++)
            longitud[i] = caracteres[i+30];
         EW[0] =caracteres[42];
         EW[1] = ' ';
         break;
       }
  }
  fclose(fp);
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
  pthread_t tid;
  pthread_create(&tid, NULL, funHilo, NULL);
  pthread_join(tid, NULL);

  printf("Tiempo: %s\n",tiempo);
  printf("Latitud: %s\n",latitud);
  printf("N o s: %s\n",NS);
  printf("Longitud: %s\n",longitud);
  printf("E o W: %s\n",EW);

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
