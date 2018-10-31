#include <sys/types.h>  //pid_t
#include <unistd.h>    //fork
#include <stdio.h>
#include <stdlib.h>    //exit
#include <sys/wait.h>  //wait

int main()
{
  pid_t ChildPID_or_Zero = fork();
  if (ChildPID_or_Zero < 0)  //error
  {
    perror("fork() error");
    exit(-1);
  }

  if (ChildPID_or_Zero != 0)  //Parent process
  {
    printf("i'm the parent %d, my child is %d\n", getpid(), ChildPID_or_Zero);
    wait(NULL);
  }
  else  //Child process
  {
    printf("i'm the child %d, my parent is %d\n", getpid(), getppid());
    execl("/bin/echo", "echo", "Hello, World", NULL);
  }
  return 0;
}
