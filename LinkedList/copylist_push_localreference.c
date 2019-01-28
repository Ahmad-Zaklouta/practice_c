/* Consider a CopyList() function that takes a list and returns a complete copy 
of that list. One pointer can iterate over the original list in the usual way. 
Two other pointers can keep track of the new list: one head pointer, and one 
tail pointer which always points to the last node in the new list. The first 
node is done as a special case, and then the tail pointer is used in the 
standard way for the others... */

#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
* varaiables declaration                                                      *
******************************************************************************/

  // Declare a structure
  typedef struct node {
    int         data;
    struct node *next;
  } node_t;
  
  
/******************************************************************************
* Functions and procedurs declaration                                         *
******************************************************************************/

  // Build — Local References
  node_t* BuildWithLocalRef();
  
  // CopyList function
  node_t *CopyList(node_t *head);
  
  // DisplayList function
  void DisplayList(node_t *head);
  
/******************************************************************************
* main function                                                               *
******************************************************************************/
int main(void) 
{
  node_t *head = NULL;
  node_t *newList = NULL;
  // build tnewListhe list
  head = BuildWithLocalRef();
  
  // copy the list
  newList = CopyList(head);
  
  printf("original list \n");
  DisplayList(head);
  printf("\n new list \n");
  DisplayList(newList);
  
  return 0;
}


/******************************************************************************
* Functions and procedurs implementaion                                       *
******************************************************************************/
  // Push
  void Push(node_t** headRef, int data) 
  {
    node_t *newNode = malloc(sizeof(node_t));
    newNode->data = data;
    newNode->next = *headRef; // The '*' to dereferences back to the real head
    *headRef = newNode; // ditto
  }

  // Build — Local References
  node_t* BuildWithLocalRef() 
  {
    node_t *head = NULL;  
    node_t **lastPtrRef = &head; // Start out pointing to the head pointer
    int i;
    for (i = 1; i < 6; i++) 
    {
      Push(lastPtrRef, i); // Add node at the last pointer in the list
      lastPtrRef = &((*lastPtrRef)->next); // Advance to point to the
      // new last pointer
    }
    // head == {1, 2, 3, 4, 5};
    return(head);
  }

  // CopyList function
  node_t *CopyList(node_t *head) 
  {
    node_t *current = head; // used to iterate over the original list
    node_t *newList = NULL;
    node_t **lastPtr;
    
    lastPtr = &newList; // start off pointing to the head itself
    
    while (current != NULL) 
    {
      Push(lastPtr, current->data);  // add each node at the lastPtr
      lastPtr = &((*lastPtr)->next); // advance lastPtr
      current = current->next;
    }
    return(newList);
  }
  
  void DisplayList(node_t *head) 
  {
    node_t *current = head;
    while (current->next != NULL) {
      printf("%d , ",current->data);
      current = current->next;
    } 
    printf("%d  ",current->data);
  }  