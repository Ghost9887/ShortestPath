#include "queue.h"

Queue createQ(){
  Queue q;
  q.front = NULL;
  q.rear = NULL;
  q.size = 0;
  return q;
}

void enqueue(Queue *q, Cell *cell){
  if(q->size == 0){
    q->front = q->rear = cell;
    q->size++;
    return;
  }

  Cell *current = q->front;
  while(current->next != NULL){
    current = current->next;
  }
  cell->next = current->next;
  current->next = cell;
  if(cell->next == NULL) q->rear = cell;
  q->size++;
}

Cell *dequeue(Queue *q){
  if(q->size == 0){
    return NULL;
  }
  Cell *front = q->front;
  q->front = q->front->next;
  q->size--;
  return front;
}

int getSize(Queue *q){
  return q->size;
}
