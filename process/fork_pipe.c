
/* C program to demonstrate use of fork() and pipe()
Write Linux C program to create two processes P1 and P2. P1 takes a string and
passes it to P2. P2 concatenates the received string with another string without
using string function and sends it back to P1 for printing.
https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
https://www.geeksforgeeks.org/pipe-system-call/

- a pipe is a connection between two processes.
- Pipe is one-way communication only i.e we can use a pipe such that One process
  write to the pipe, and the other process reads from the pipe. It opens a pipe,
  which is an area of main memory that is treated as a “virtual file”.
- The pipe can be used by the creating process, as well as all its child
  processes, for reading and writing. One process can write to this “virtual file”
  or pipe and another related process can read from it.
- If a process tries to read before something is written to the pipe, the process
  is suspended until something is written.
- The pipe system call finds the first two available positions in the process’s
  open file table and allocates them for the read and write ends of the pipe.
- When we use fork in any process, file descriptors remain open across child
  process and also parent process. If we call fork after creating a pipe,
  then the parent and child can communicate via the pipe.
- If pipe is empty and we call read system call then Reads on the pipe will
  return EOF (return value 0) if no process has the write end open.
- If some other process has the pipe open for writing, read will block in
  anticipation of new data so this code output hangs because here write ends
  parent process and also child process doesn’t close.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    // We use two pipes
    // First pipe to send input string from parent
    // Second pipe to send concatenated string from child

    // File discreptor
    int fd1[2];  // Used to store two ends of first pipe
    int fd2[2];  // Used to store two ends of second pipe

    char fixed_str[] = "forgeeks.org";
    char input_str[100];
    pid_t process;

    if (pipe(fd1) == -1) // creating pipe failed
    {
        perror("Pipe Failed");
        exit (1);
    }
    if (pipe(fd2) == -1) // creating pipe failed
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    // Read string from user
    printf("Please Enter a string: ");
    scanf("%s", input_str);

    process = fork(); // Create a process

    if (process < 0) // creating process failed
    {
        fprintf(stderr, "fork Failed");
        exit (1);
    }
    else if (process > 0) // Parent process
    {
        char concat_str[100];

        close(fd1[0]);  // Close reading end of first pipe

        // Write input string and close writing end of first
        // pipe.
        write(fd1[1], input_str, strlen(input_str)+1);
        close(fd1[1]);

        // Wait for child to send a string
        wait(NULL);

        close(fd2[1]); // Close writing end of second pipe

        // Read string from child, print it and close
        // reading end.
        read(fd2[0], concat_str, 100);
        printf("Concatenated string %s\n", concat_str);
        close(fd2[0]);
    }

    // child process
    else
    {
        close(fd1[1]);  // Close writing end of first pipe

        // Read a string using first pipe
        char concat_str[100];
        read(fd1[0], concat_str, 100);

        // Concatenate a fixed string with it
        int k = strlen(concat_str);
        for (int i=0; i<strlen(fixed_str); i++)
          concat_str[k++] = fixed_str[i];

        concat_str[k] = '\0';   // string ends with '\0'

        // Close both reading ends
        close(fd1[0]);
        close(fd2[0]);

        // Write concatenated string and close writing end
        write(fd2[1], concat_str, strlen(concat_str)+1);
        close(fd2[1]);

        exit(0);
    }
}
