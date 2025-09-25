#include "queue.h"

Queue createQ(){
  Queue q;
  q.front = NULL;
  q.rear = NULL;
  q.size = 0;
  return q;
}

void enqueue(Queue *q, Cell *cell){
  if(q->front == NULL){
    q->front = q->rear = cell;
    q->size++;
    return;
  }

  Cell *temp = q->front;
  while(temp->next != NULL){
    temp = temp->next;
  }

  cell->next = temp->next;
  temp->next = cell;

  if(cell->next == NULL){
    q->rear = cell;
  }
  q->size++;
}


Cell *dequeue(Queue *q){
  if(q->front == NULL){
    return NULL;
  }

  Cell *temp = q->front;
  q->front = q->front->next;
  if(q->front == NULL){
    q->rear = NULL;
  }
  q->size--;
  return temp;
}

int getSize(Queue *q){
 return q->size;
}
