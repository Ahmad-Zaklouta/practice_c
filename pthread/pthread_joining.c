#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 5


void* work(void *t)
{
  int i;
  long tid;
  double result=0.0;
  tid = (long)t;
  printf("Thread %ld starting...\n",tid);
  for( i = 0; i < 1000000; i++)
  {
    result = result + sin(i) * tan(i);
  }
  printf("Thread %ld done. Result = %e\n", tid, result);
  pthread_exit((void*)t);
}

int main(int argc, char *argv[])
{

  pthread_t thread[NUM_THREADS];
  pthread_attr_t attr;
  int rc; 
  long t; 
  void *status;

  /* 1. Declare a pthread attribute variable of the pthread_attr_t data type
     2. Initialize the attribute variable with pthread_attr_init()
     3. Set the attribute detached status with pthread_attr_setdetachstate()
     4. When done, free library resources used by the attribute with 
        pthread_attr_destroy() */

  /* Initialize and set thread detached attribute */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  for (t = 0; t < NUM_THREADS; t++) 
  {
    printf("Main : creating thread %ld \n", t);
    rc = pthread_create(&thread[t], &attr, work, (void*)t);
    if(rc) 
    {   
      printf("ERROR; return code from pthread_create() is %d \n", rc);
      exit(-1);
    }
  }

  /* Free attribute and wait for the other threads */
  pthread_attr_destroy(&attr);
  for (t = 0; t < NUM_THREADS; t++) 
  {
    /* If status is not null, it will contain the return status of the
       called thread */
    // block main until all threads finished
    rc = pthread_join(thread[t], &status);
    if(rc) 
    {
      printf("ERROR; return code from pthread_create() is %d \n", rc);
      exit(-1);
    }
    printf("Main: completed join with thread %ld having a status "
           "of %ld\n", t, (long)status);
  }
  
  printf("Main: program completed . Exiting. \n");
  return 0;
}