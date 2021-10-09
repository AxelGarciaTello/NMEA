#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

#define PUERTO        5000
#define COLA_CLIENTES 5

int iniServidor(){
  struct sockaddr_in direccion_servidor; //Estructura de la familia AF_INET, que almacena direccion
  int sockfd;
  /*
   *  AF_INET - Protocolo de internet IPV4
   *  htons - El ordenamiento de bytes en la red es siempre big-endian, por lo que
   *  en arquitecturas little-endian se deben revertir los bytes
   *  INADDR_ANY - Se elige cualquier interfaz de entrada
   */


   memset (&direccion_servidor, 0, sizeof (direccion_servidor));	//se limpia la estructura con ceros
   direccion_servidor.sin_family 		= AF_INET;
   direccion_servidor.sin_port 		= htons(PUERTO);
   direccion_servidor.sin_addr.s_addr 	= INADDR_ANY;

  /*
   *  Creacion de las estructuras necesarias para el manejo de un socket
   *  SOCK_STREAM - Protocolo orientado a conexión
   */
   printf("Creando Socket ....\n");
   if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 )
   {
     perror("Ocurrio un problema en la creacion del socket");
     exit(EXIT_FAILURE);
   }
  /*
   *  bind - Se utiliza para unir un socket con una dirección de red determinada
   */
   printf("Configurando socket ...\n");
   if( bind(sockfd, (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor)) < 0 )
   {
     perror ("Ocurrio un problema al configurar el socket");
     exit(EXIT_FAILURE);
   }
  /*
   *  listen - Marca al socket indicado por sockfd como un socket pasivo, esto es, como un socket
   *  que será usado para aceptar solicitudes de conexiones de entrada usando "accept"
   *  Habilita una cola asociada la socket para alojar peticiones de conector procedentes
   *  de los procesos clientes
   */
   printf ("Estableciendo la aceptacion de clientes...\n");
   if( listen(sockfd, COLA_CLIENTES) < 0 )
   {
     perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
     exit(EXIT_FAILURE);
   }

      return sockfd;
}
