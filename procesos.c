#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "estructura.h"

extern LOCALIZACION loc;

void atiendeCliente(int cliente_sockfd){
   printf("Se aceptó un cliente, atendiendolo \n");
   if( write (cliente_sockfd, &loc, sizeof(LOCALIZACION)) < 0 ){
     perror("Ocurrio un problema en el envio de un mensaje al cliente");
     exit(1);
   }

   close(cliente_sockfd);
   exit(0);
}
