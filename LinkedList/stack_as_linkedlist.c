#include <stdio.h>
#include <stdlib.h>

  // Declare a structure
  typedef struct stack_node {
    int               element;
    struct stack_node *next;
  } stack_node_t;
  
  // Create a new node
  stack_node_t* NewNode(int value) {
    stack_node_t *temp = (stack_node_t*) malloc(sizeof(stack_node_t));
    if (temp != NULL) {
      temp->element = value;
      temp->next = NULL;
    } 
    return temp;
  }
  
  // Add a node at the top of the stack
  void Push(stack_node_t **stack, int value) {  // Two ** because the stack pointer needs to be changed
    stack_node_t *current = NewNode(value);
    if (current != NULL) {
      current->next = *stack;
      *stack = current;
    }
  }
  
  // Remove a node from the top of the stack
  int Pop(stack_node_t **stack) {
    if (*stack != NULL) {
      stack_node_t *current = *stack;
      *stack = (*stack)->next;
      int ele = current->element;
      free(current);
      return ele;
    }
    else {
      return 0;
    }
  }
  
  void DisplayList(stack_node_t *stack) {
    stack_node_t *current = stack;
    while (current->next != NULL) {
      printf("%d , ",current->element);
      current = current->next;
    } 
    printf("%d  ",current->element);
  }  
  
int main() 
{
  
  // Create the head of the list
  stack_node_t *stack = NewNode(0);
  
  // push to the stack
  Push(&stack, 11);
  Push(&stack, 12);
  Push(&stack, 13);
  Push(&stack, 14);
  Push(&stack, 15);
  
  DisplayList(stack);
  
  printf("\n");
  // pop from the stack
  printf("%d , ",Pop(&stack));
  printf("%d , ",Pop(&stack));
  printf("%d , ",Pop(&stack));
  
  printf("\n");
  DisplayList(stack);
  
  return 1;
}
