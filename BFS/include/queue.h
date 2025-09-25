#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

  Queue createQ();
  void enqueue(Queue *q, Cell *cell);
  Cell *dequeue(Queue *q);
  int getSize(Queue *q);

#endif
