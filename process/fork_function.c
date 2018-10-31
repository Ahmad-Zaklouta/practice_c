#include <unistd.h>
#include <stdio.h>

int main()
{
  int x = 1;
  if (fork() == 0) // child prosess
  {
    // only child execute this
    printf("child, x = %d\n", ++x);
  }
  else  // parent prosess
  {
    // only parent execute this
    printf("parent, = %d\n", --x);
  }
  // parent and child execute this
  printf("Exiting with x = %d\n", x);
  return 0;
}
