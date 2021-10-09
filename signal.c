#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

extern int sockfd;

void ISRsw(int sig){
  int estado;
  pid_t pid;
  if(sig == SIGCHLD){
    pid = wait(&estado);
    printf("Proceso con pid: %d terminado y retorno %d\n",pid, estado>>8);
  }
  if(sig == SIGINT){
    close (sockfd);
    printf("Apagando servidor\n");
    exit(0);
  }
}
