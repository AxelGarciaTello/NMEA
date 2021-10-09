#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define TAM_BUFFER 	100

extern char tiempo[9],
            latitud[10],
            longitud[11],
            NS[2],
            EW[2];

void atiendeCliente(int cliente_sockfd){
   char leer_mensaje[TAM_BUFFER];
   printf("Se aceptó un cliente, atendiendolo \n");
   if( read (cliente_sockfd, leer_mensaje, TAM_BUFFER) < 0 ){
     perror ("Ocurrio algun problema al recibir datos del cliente");
     exit(1);
   }
   if( write (cliente_sockfd, tiempo, 19) < 0 ){
     perror("Ocurrio un problema en el envio de un mensaje al cliente");
     exit(1);
   }
   if( read (cliente_sockfd, leer_mensaje, TAM_BUFFER) < 0 ){
     perror ("Ocurrio algun problema al recibir datos del cliente");
     exit(1);
   }
   if( write (cliente_sockfd, latitud, 19) < 0 ){
     perror("Ocurrio un problema en el envio de un mensaje al cliente");
     exit(1);
   }
   if( read (cliente_sockfd, leer_mensaje, TAM_BUFFER) < 0 ){
     perror ("Ocurrio algun problema al recibir datos del cliente");
     exit(1);
   }
   if( write (cliente_sockfd, NS, 19) < 0 ){
     perror("Ocurrio un problema en el envio de un mensaje al cliente");
     exit(1);
   }
   if( read (cliente_sockfd, leer_mensaje, TAM_BUFFER) < 0 ){
     perror ("Ocurrio algun problema al recibir datos del cliente");
     exit(1);
   }
   if( write (cliente_sockfd, longitud, 19) < 0 ){
     perror("Ocurrio un problema en el envio de un mensaje al cliente");
     exit(1);
   }
   if( read (cliente_sockfd, leer_mensaje, TAM_BUFFER) < 0 ){
     perror ("Ocurrio algun problema al recibir datos del cliente");
     exit(1);
   }
   if( write (cliente_sockfd, EW, 19) < 0 ){
     perror("Ocurrio un problema en el envio de un mensaje al cliente");
     exit(1);
   }
   close(cliente_sockfd);
   exit(0);
}
