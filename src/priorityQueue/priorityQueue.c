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
    return;
  }
}

void dequeue(PriorityQueue *pq){

}

int getSize(PriorityQueue *pq){
 return pq->size;
}

void printQueue(PriorityQueue *pq){

}
