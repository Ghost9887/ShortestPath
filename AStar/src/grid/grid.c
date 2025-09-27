#include "grid.h"

void drawGrid(){
  for (int x = 0; x <= GRID_WIDTH; x++) {
    DrawLine(x * CELL_SIZE, 0, x * CELL_SIZE, GRID_HEIGHT * CELL_SIZE, BLACK);
  }
  for (int y = 0; y <= GRID_HEIGHT; y++) {
    DrawLine(0, y * CELL_SIZE, GRID_WIDTH * CELL_SIZE, y * CELL_SIZE, BLACK);
  }
}
