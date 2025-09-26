#include "priorityQueue.h"

PriorityQueue createPQ(){
  PriorityQueue pq;
  pq.front = NULL;
  pq.rear = NULL;
  pq.size = 0;
}

void enqueue(PriorityQueue *pq, Cell *cell){
  if(pq->size == 0){
    pq->front = pq->rear = cell;
    pq->size++;
    return;
  }

  if(cell->distance < pq->front->distance){
    cell->next = pq->front;
    pq->front = cell;
    pq->size++;
    return;
  }
  
  Cell *current = pq->front;
  while(current->next != NULL && current->next->distance <= cell->distance){
    current = current->next;
  }
  cell->next = current->next;
  current->next = cell;
  if(cell->next == NULL) pq->rear = cell;
  pq->size++;
}

Cell *dequeue(PriorityQueue *pq){
  if(pq->size == 0){
    return NULL;
  }
  Cell *front = pq->front;
  pq->front = pq->front->next;
  pq->size--;
  printf("id: %d\n", front->id);
  return front;
}

int getSize(PriorityQueue *pq){
  return pq->size;
}
