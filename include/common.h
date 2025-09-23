#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FPS 0

#define CELL_SIZE 10

#define GRID_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)

#define AMOUNT_OF_CELLS (GRID_WIDTH * GRID_HEIGHT)

//act as our nodes
typedef struct Cell{
  struct Cell *next;
  Vector2 pos;
  Color colour;
}Cell;

typedef struct Start{
  Vector2 pos;
  Color colour;
}Start;

typedef struct End{
  Vector2 pos;
  Color colour;
}End;

typedef struct PriorityQueue{
  Cell *front;
  Cell *rear;
  int size;
}PriorityQueue;

#endif
