#include "cell.h"

Cell createCell(int posX, int posY){
  Cell cell;
  cell.pos = (Vector2){ posX, posY };
  cell.next = NULL;
  cell.colour = BLUE;
  return cell;
}

void initCellArr(Cell *cellArr){
  int index = 0;
  for(int y = 0; y < GRID_HEIGHT; y++){
    for(int x = 0; x < GRID_WIDTH; x++){
      cellArr[index] = createCell(x * CELL_SIZE, y * CELL_SIZE);
      index++;
    }
  }
}

void drawCells(Cell *cellArr){
  for(int i = 0; i < AMOUNT_OF_CELLS; i++){
    DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, cellArr[i].colour);
  }
}

void updateCells(Cell *cellArr){
  drawCells(cellArr);
}
