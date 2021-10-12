#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>

extern int sockfd;
extern pthread_t tid;

void ISRsw(int sig){
  int estado;
  pid_t pid;
  if(sig == SIGCHLD){
    pid = wait(&estado);
    printf("Proceso con pid: %d terminado y retorno %d\n",pid, estado>>8);
  }
  if(sig == SIGINT){
    pthread_join(tid, NULL);
    close (sockfd);
    printf("Apagando servidor\n");
    exit(0);
  }
}
