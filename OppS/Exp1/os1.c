#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>
#include<string.h>
int main(void) {
int pipefd[2];
int i;
char s[1000];
char s2[80];

pid_t pid,cpid;
if(pipe(pipefd)<0)
{ printf("\n error");
}

pid = fork();

if (pid == 0) {
sleep(5);
printf("\n Hello from the child process, ID: %d",getpid());
   close(pipefd[1]);
i=read(pipefd[0],s,11);

  printf("\n Read %d bytes from the pipe: %s ",i,s);
  printf("\nBye from child");


}

 else if (pid != -1) {

  sleep(2);
printf("\n Hello from the parent. I’ve forked process: %d.", getpid());

  strcpy(s2,"CSEESection");
  printf("\n %s",s2);
close(pipefd[0]);
  write(pipefd[1],s2,strlen(s2));


  printf("\nBye from parent");
}

else {
printf("There was an error with forking.\n");
}
}
