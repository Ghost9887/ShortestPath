#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FPS 0

#define CELL_SIZE 20
#define GRID_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)

#define AMOUNT_OF_CELLS (GRID_WIDTH * GRID_HEIGHT)

typedef enum Mode{
  START,
  END,
  SOLID
}Mode;

typedef struct Cell{
  int id;
  Vector2 pos;
  struct Cell *next;
  bool start;
  bool end;
  bool solid;
}Cell;

typedef struct User{
  Mode mode;
}User;

#endif
