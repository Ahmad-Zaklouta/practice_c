/*

https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-087-practical-programming-in-c-january-iap-2010/assignments/MIT6_087IAP10_assn06a.pdf
https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-087-practical-programming-in-c-january-iap-2010/assignments/assn06a.zip

/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/******************************************************************************
* varaiables declaration                                                      *
******************************************************************************/

  /* the trie node data structure */
  struct s_trie_node
  {
    char *translation; /* NULL if node not a word */
    /* UCHAR_MAX: the maximum value for an unsigned char. */
    struct s_trie_node *children[UCHAR_MAX+1]; /* pointer array to child nodes */
  };

  /* pointer to the root node of the trie structure */
  static struct s_trie_node *proot = NULL;

/******************************************************************************
* Functions and procedurs declaration                                         *
******************************************************************************/

  /* helper functions for trie structure */

  /* allocate new node on the heap
     output: pointer to new node (must be freed) */
  struct s_trie_node *new_node(void);

  /* delete node and all its children
     input: pointer to node to delete
     postcondition: node and children are freed */
  void delete_node(struct s_trie_node *pnode);

  /* add word to trie, with translation
     input: word and translation
     output: non-zero if new node added, zero otherwise
     postcondition: word exists in trie */
  int add_word(const char *word, char *translation);

  /* read dictionary file into trie structure */
  unsigned int load_dictionary(const char *filename);

  /* search trie structure for word and return translations
     input: word to search
     output: translation, or NULL if not found */
  char* lookup_word(const char *word);

  /* maximum number of characters for word to search */
  #define WORD_MAX 256

  /* maximum number of characters in line */
  #ifndef LINE_MAX
  #define LINE_MAX 2048
  #endif

/******************************************************************************
* main function                                                               *
******************************************************************************/

/* main function */
int main(int argc, char *argv[]) {
	char word[WORD_MAX], *translation;
	int len;

	if (argc <= 1)
		return 0; /* no dictionary specified */

	/* load dictionary */
	proot = new_node();
	load_dictionary(argv[1]);

	do {
		printf("Enter word to translate: ");
		fflush(stdout);
		if (!fgets(word, WORD_MAX, stdin))
			abort();

		/* strip trailing newline */
		len = strlen(word);
		if (len > 0 && word[len-1] == '\n') {
			word[len-1] = '\0';
			--len;
		}

		/* exit on empty string */
		if (len == 0)
			break;

		/* lookup word */
		translation = lookup_word(word);

		if (translation)
			printf("%s -> %s\n", word, translation);
		else
			printf("\"%s\" not found\n", word);
	} while (1);

	/* clean up trie structure */
	delete_node(proot);

	return 0;
}

/******************************************************************************
* Functions and procedurs implementaion                                       *
******************************************************************************/

  /* allocate new node on the heap
     output: pointer to new node (must be freed) */
  struct s_trie_node *new_node(void) 
  {
    /* TODO: allocate a new node on the heap, and
       initialize all fields to default values */
    struct s_trie_node *pnode = (struct s_trie_node*) malloc(sizeof(struct s_trie_node));
    int i;
    pnode->translation = NULL;
    for (i = 0; i < UCHAR_MAX+1; i++)
      pnode->children[i] = NULL;
    
    return pnode;
  }

  /* delete node and all its children
     input: pointer to node to delete
     postcondition: node and children are freed */
  void delete_node(struct s_trie_node *pnode) 
  {
    /* TODO: delete node and all its children
       Be sure to free non-null translations!
       Hint: use recursion
     */
    int i;
    if (pnode->translation)
      free(pnode->translation);
    for (i = 0; i < UCHAR_MAX+1; i++)
      if (pnode->children[i])
        delete_node(pnode->children[i]);
      
    free(pnode);
  }

  /* add word to trie, with translation
     input: word and translation
     output: non-zero if new node added, zero otherwise
     postcondition: word exists in trie */
  int add_word(const char *word, char *translation) 
  {
    /* TODO: add word to trie structure
       If word exists, append translation to existing
       string
       Be sure to store a copy of translation, since
       the string is reused by load_dictionary()
     */
     
    struct s_trie_node *pnode = proot;
    int i, len = strlen(word), inew = 0;
    unsigned char j;
    
    // go throw the word and add each letter to a node 
    for (i = 0; i < len ; i++) 
    {
      j = word[i];
      if ( (inew = !pnode->children[j]) )  // true when pnode->children[j] is zero (empty node)
        pnode->children[j] = new_node();
      pnode = pnode->children[j];
    }
    
    if (pnode->translation)  // node has a translation
    {     
      /* concatenate strings */
      char *oldtranslation = pnode->translation;
      int oldlen = strlen(oldtranslation);
      int newlen = strlen(translation); 
      pnode->translation = malloc(oldlen + newlen + 2); 
      strcpy(pnode->translation, oldtranslation); 
      strcpy(pnode->translation + oldlen, ","); 
      strcpy(pnode->translation + oldlen + 1, translation); 
      free(oldtranslation);
    } 
    else
    {
      pnode->translation = strcpy(malloc(strlen(translation) + 1), translation);
    }
      
    return inew ;
  }

  /* delimiter for dictionary */
  #define DELIMS "\t"

  /* read dictionary file into trie structure */
  unsigned int load_dictionary(const char *filename) 
  {
    FILE *pfile;
    char line[LINE_MAX], *word, *translation;
    unsigned int icount = 0;

    /* ensure file can be opened */
    if ( !(pfile = fopen(filename,"r")) )
      return icount;

    /* read lines */
    while ( (fgets(line, LINE_MAX, pfile)) ) 
    {
      /* strip trailing newline */
      int len = strlen(line);
      if (len > 0 && line[len-1] == '\n') 
      {
        line[len-1] = '\0';
        --len;
      }

      if (len == 0 || line[0] == '#')
        continue; /* ignore comment/empty lines */

      /* separate word and translation */
      /* strspn: Get span of character set in string */
      word = line + strspn(line, DELIMS);
      if ( !word[0] )
        continue; /* no word in line */
      
      /* strcspn: Get span until character in string */
      translation = word + strcspn(word, DELIMS);
      *translation++ = '\0';  // dereference and then increment
      translation += strspn(translation, DELIMS);

      /* add word to trie */
      if (add_word(word, translation))
        icount++;
    }

    /* finish */
    fclose(pfile);
    return icount;
  }

  /* search trie structure for word and return translations
     input: word to search
     output: translation, or NULL if not found */
  char * lookup_word(const char *word) 
  {
    /* TODO: search trie structure for word
       return NULL if word is not found */
       
    struct s_trie_node *pnode = proot;
    int i, len = strlen(word);
    unsigned char j;
    for (i = 0; i < len; i++) 
    {
      j = word[i];
      if (!pnode->children[j])
        return NULL;
      pnode = pnode->children[j];
    }
    return pnode->translation;
  }
