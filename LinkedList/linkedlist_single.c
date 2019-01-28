
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
  
  // Create a new node
  node_t* NewNode(int value) {
    node_t *temp = (node_t*) malloc(sizeof(node_t));
    if (temp != NULL) {
      temp->data = value;
      temp->next = NULL;
    } 
    return temp;
  }
  
  // Add a node at the front
  void AddFront(node_t **head, int value) {  // Two ** because the head needs to be changed
    node_t *current = NewNode(value);
    if (current != NULL) {
      current->next = *head;
      *head = current;
    }
  }

  // Add a node at the end
  void AddEnd(node_t *head, int value) {
    node_t *current = head;
    while (current->next != NULL) {
      current = current->next;
    }   
    current->next = NewNode(value);
  }   
  
  void DisplayList(node_t *head) {
    node_t *current = head;
    while (current->next != NULL) {
      printf("%d , ",current->data);
      current = current->next;
    } 
    printf("%d  ",current->data);
  }  
  
  node_t* FindNode(node_t* head, int value){
    node_t *current = head;
    for (current; current->next != NULL; current = current->next) {
      if (current->data == value) {
        return current;
      }        
    }
    return NULL;
  }
 
  void DeleteNode(node_t **head, node_t* pnode){
    node_t *previous = *head;
    if (pnode == *head) {  // The node is the head
      *head = (*head)->next;
      free(pnode);
    }
    else {
      while (previous->next != pnode) {
        previous = previous->next;
      }
      if (pnode->next == NULL) {  // The node is the end
        previous->next = NULL;
        free(pnode);
      }
      else {  
        previous->next = pnode->next;
        free(pnode);
      }
    }
  }
  
int main() 
{
  
  // Create the head of the list
  node_t *head = NewNode(0);
  
  // Add to the front
  AddFront(&head, 11);
  AddFront(&head, 12);
  // Add to the end
  AddEnd(head, 21);
  AddEnd(head, 22);
  
  DisplayList(head);
  
  printf("\n");
  // Find a node
  node_t *current = FindNode(head, 0);
  printf("%d",current->data);
  
  printf("\n");
  // Delete a node
  DeleteNode(&head, current);
  DisplayList(head);
  
  printf("\n");
  // Delete the head
  DeleteNode(&head, head);
  DisplayList(head);

  printf("\n");
  // Delete the end
  current = FindNode(head, 22);
  DeleteNode(&head, head);
  DisplayList(head);  
  
return 0;

}
