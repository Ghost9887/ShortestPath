#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "common.h"

  PriorityQueue createPQ();
  void enqueue(PriorityQueue *pq, Cell *cell);
  void dequeue(PriorityQueue *pq);
  void getSize(PriorityQueue *pq);
  void printQueue(PriorityQueue *pq);

#endif
