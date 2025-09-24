#include "priorityQueue.h"

PriorityQueue createPQ(){
  PriorityQueue pq;
  pq.front = NULL;
  pq.rear = NULL;
  pq.size = 0;
  return pq;
}

void enqueue(PriorityQueue *pq, Cell *cell){
  if(pq->front == NULL){
    pq->front = pq->rear = cell;
    pq->size++;
    return;
  }

  if(pq->front->distance > cell->distance){
    cell->next = pq->front;
    pq->front = cell;
    pq->size++;
    return;
  }

  Cell *temp = pq->front;
  while(temp->next != NULL && cell->distance >= temp->next->distance){
    temp = temp->next;
  }

  cell->next = temp->next;
  temp->next = cell;

  if(cell->next == NULL){
    pq->rear = cell;
  }
  pq->size++;
}


void dequeue(PriorityQueue *pq){
  if(pq->front == NULL){
    return;
  }

  pq->front = pq->front->next;
  if(pq->front == NULL){
    pq->rear = NULL;
  }
  pq->size--;
}

int peek(PriorityQueue *pq){
  return pq->front->distance;
}

int getSize(PriorityQueue *pq){
 return pq->size;
}

void printQueue(PriorityQueue *pq){
  if(pq->front == NULL){
    return;
  }

  Cell *temp = pq->front;
  while(temp != NULL){
    printf("%d -> ", temp->distance);
    temp = temp->next;
  }
}
