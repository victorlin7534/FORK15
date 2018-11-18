#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

void act(int p){
  printf("FORKING...\n");
  srand(time(NULL));
  printf("child pid: %d\n",getpid());
  int slept = rand()%15 + 5;
  sleep(slept);
  printf("child process complete\n");
  exit(slept);
}

void care(){
  int status;
  int pid = wait(&status);
  int exit = WEXITSTATUS(status);
  printf("complete child pid: %d slept for : %d s\n\n",pid,exit);
}

int main(){
  int p,slept;
  if(!(p = fork()))
    act(p);
  else{
    care();
    if(!(p = fork()))
      act(p);
    else{
      care();
      printf("parent process complete\n");
    }
  }
  return 0;
}

