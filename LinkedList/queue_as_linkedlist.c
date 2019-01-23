#include <stdio.h>
#include <stdlib.h>

  // Declare a structure
  typedef struct queue_node {
    int               element;
    struct queue_node *next;
  } queue_node_t;
  
  // Create a new node
  queue_node_t* NewNode(int value) {
    queue_node_t *temp = (queue_node_t*) malloc(sizeof(queue_node_t));
    if (temp != NULL) {
      temp->element = value;
      temp->next = NULL;
    } 
    return temp;
  }
  
  // enqueue element to the queue
  void Enqueue(queue_node_t **queue, queue_node_t **queue_rear, int element) {
    queue_node_t *new_element = NewNode(element);
    if (*queue_rear != NULL) {  // queue is not empty
      (*queue_rear)->next = new_element;
    }
    else {  // queue is empty
      *queue = new_element;
    }
    *queue_rear = new_element;  // update the queue rear
  }
  
  // dequeue element from the queue
  int Dequeue(queue_node_t **queue, queue_node_t **queue_rear) {
    if (*queue != NULL) {
      queue_node_t *queue_front = *queue;
      *queue = (*queue)->next;
      int top_element = queue_front->element;
      if (*queue_rear = queue_front) {  // only one node in the queue
        (*queue_rear) = NULL;
      free(queue_front);
      return top_element;
      }
    }
    else {
      return 0;
    }
  }
  
  void DisplayList(queue_node_t *queue) {
    queue_node_t *current = queue;
    while (current->next != NULL) {
      printf("%d , ",current->element);
      current = current->next;
    } 
    printf("%d  ",current->element);
  }  
  
int main() 
{
  
  // Create the head of the list
  queue_node_t *queue = NewNode(0);
  queue_node_t *queue_rear = NULL;
  
  // Enqueue to the queue
  Enqueue(&queue, &queue_rear, 11);
  Enqueue(&queue, &queue_rear, 12);
  Enqueue(&queue, &queue_rear, 13);
  Enqueue(&queue, &queue_rear, 14);
  Enqueue(&queue, &queue_rear, 15);
  
  DisplayList(queue);
  
  printf("\n");
  // Dequeue from the queue
  printf("%d , ",Dequeue(&queue, &queue_rear));
  printf("%d , ",Dequeue(&queue, &queue_rear));
  printf("%d , ",Dequeue(&queue, &queue_rear));
  
  printf("\n");
  DisplayList(queue);
  
  return 1;
}
