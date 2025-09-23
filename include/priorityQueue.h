#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "common.h"

  PriorityQueue createPQ();
  void enqueue(PriorityQueue *pq, Cell *cell);
  void dequeue(PriorityQueue *pq);
  int getSize(PriorityQueue *pq);
  void printQueue(PriorityQueue *pq);

#endif
