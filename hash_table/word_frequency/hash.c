#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_BUCKETS 1000
#define MULTIPLIER  31
#define MAX_LEN     100


/******************************************************************************
* varaiables declaration                                                      *
******************************************************************************/

  struct wordrec
  {
    char *word;
    unsigned long count;
    struct wordrec *next;
  };
  
  /*hash bucket*/
  struct wordrec *table[MAX_BUCKETS];

/******************************************************************************
* Functions and procedurs declaration and implementation                      *
******************************************************************************/

  /*
    @function walloc
    @desc     produces a new node
  */
  struct wordrec* walloc(const char* str)
  {
    struct wordrec* p = (struct wordrec*)malloc(sizeof(struct wordrec));
    if(p != NULL)
    {
      p->count = 0;
      p->word = strdup(str); /*creates a duplicate*/
      p->next = NULL;
    }
    return p;
  }


  /*
    @function hashstring
    @desc     produces hash code for a string
              multipliers 31,35 have been found to work well
  */
  unsigned long hashstring(const char *str)
  {
    unsigned long hash = 0;
    while(*str)
    {
      hash = hash * MULTIPLIER + *str;
      str++;
    }
    return hash % MAX_BUCKETS;
  }


  /*
    @function lookup
    @desc     returns a pointer to the word or creates
              it if required
  */
  struct wordrec* lookup(const char *str, int create)
  {
    unsigned long hash = hashstring(str); /*starting point*/
    struct wordrec *wp = table[hash];
    
    /* follow the linked list to find str, if found return pointer*/
    while(wp != NULL) 
    {
      if(strcmp(wp->word, str) == 0)
      {
        return wp;
      }
      wp = wp->next;
    } 
  

    /* if not found and create specified */
    if(create)
    {
      /* create new node update linked list */
      wp = walloc(str);
      wp->next = table[hash];
      table[hash] = wp;
    }
    return wp;
  }

  /*
    @function cleartable()
    @desc     reclaims memory
  */
  void cleartable()
  {
    struct wordrec *wp = NULL, *p = NULL;
    int i = 0;
    /* code to reclaim memory */
    for(i = 0; i < MAX_BUCKETS; i++)
    { 
      wp = table[i];
      while(wp)  // not NULL
      {
        p = wp;
        wp = wp->next;
        free(p->word); // because strdup allocate memory
        free(p);
      }
    }
  }


/******************************************************************************
* main function                                                               *
******************************************************************************/

int main(int argc,char* argv[])
{
  FILE* fp = fopen("book.txt","r");
  char  word[1024]; /*big enough*/
  struct wordrec *wp = NULL;
  int i = 0;

  memset(table, 0, sizeof(table)); // initialize the memory with zero
  
  /*read from input*/
  while(1)
  {
    if(fscanf(fp, "%s", word) != 1)
      break;
    wp = lookup(word, 1); /*create if doesn't exist*/
    wp->count++;
  }
  fclose(fp);

  /*
    print all words have frequency > 100
   */
  for(i = 0; i < MAX_BUCKETS; i++)
  {
    for(wp = table[i]; wp != NULL; wp = wp->next)
	  {
	    if(wp->count > 100)
	    {
	      printf("%s-->%ld\n", wp->word, wp->count);
	    }
	  }
  }
  cleartable();
  return 0;
}
