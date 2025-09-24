#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FPS 0

#define CELL_SIZE 10

#define GRID_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)

#define AMOUNT_OF_CELLS (GRID_WIDTH * GRID_HEIGHT)

typedef enum Mode{
  START,
  END,
  SOLID
}Mode;

//act as our nodes
typedef struct Cell{
  struct Cell *next;
  Vector2 pos;
  Color colour;
  int weight;
  int distance;
  bool solid;
  bool start;
  bool end;
}Cell;

typedef struct User{
  Mode mode;
}User;

typedef struct PriorityQueue{
  Cell *front;
  Cell *rear;
  int size;
}PriorityQueue;

#endif
