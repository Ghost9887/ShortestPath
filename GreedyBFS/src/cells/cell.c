#include "cell.h"

Cell createCell(int posX, int posY, int id){
  Cell cell;
  cell.id = id;
  cell.pos = (Vector2){ posX, posY };
  cell.next = NULL;
  cell.start = true;
  cell.end = false;
  cell.solid = false;
  return cell;
}

void initCellArr(Cell *cellArr){
  int index = 0;
  for(int y = 0; y < GRID_HEIGHT; y++){
    for(int x = 0; x < GRID_WIDTH; x++){
      cellArr[index] = createCell(x * CELL_SIZE, y * CELL_SIZE, index);
      index++;
    }
  }
}

void drawCells(Cell *cellArr){
  for(int i = 0; i < AMOUNT_OF_CELLS; i++){
    if(cellArr[i].start){
      DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, YELLOW);
    }
    else if(cellArr[i].end){
      DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, RED);
    }
    else if(cellArr[i].solid){
      DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, BLUE);
    }
    else{
      DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, WHITE);
    }
  }
}

void updateCells(Cell *cellArr){
  drawCells(cellArr);
}
