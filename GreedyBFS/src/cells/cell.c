#include "cell.h"

Cell createCell(int posX, int posY, int id){
  Cell cell;
  cell.id = id;
  cell.pos = (Vector2){ posX, posY };
  cell.next = NULL;
  cell.start = false;
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

void placeCell(Cell *cellArr, User *user){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    Vector2 mousePos = GetMousePosition();
    int posX = ((int)mousePos.x / CELL_SIZE) * CELL_SIZE;
    int posY = ((int)mousePos.y / CELL_SIZE) * CELL_SIZE;
    int index = (posY / CELL_SIZE) * GRID_WIDTH + (posX / CELL_SIZE);
    if(user->mode == START){
      if(!cellArr[index].solid && !cellArr[index].end && !user->placedStart){
        cellArr[index].start = true;
        user->placedStart = true;
        printf("placed start cell: %d\n", index);
      }
    }
    else if(user->mode == END){
      if(!cellArr[index].solid && !cellArr[index].start && !user->placedEnd){
        cellArr[index].end = true;
        user->placedEnd = true;
      }
    }
    else if(user->mode == SOLID){
      if(!cellArr[index].start && !cellArr[index].end){
        cellArr[index].solid = true;
      }
    }
  }
}

void deleteCell(Cell *cellArr, User *user){
  if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
    Vector2 mousePos = GetMousePosition();
    int posX = ((int)mousePos.x / CELL_SIZE) * CELL_SIZE;
    int posY = ((int)mousePos.y / CELL_SIZE) * CELL_SIZE;
    int index = (posY / CELL_SIZE) * GRID_WIDTH + (posX / CELL_SIZE);
    if(cellArr[index].start){
      user->placedStart = false;
    }
    if(cellArr[index].end){
      user->placedEnd = false;
    }
    cellArr[index].start = false;
    cellArr[index].end = false;
    cellArr[index].solid = false;
  }
}

void initializeGreedyBFS(Cell *cellArr){
  
}

void GreedyBFS(Cell *cellArr){

}

void callGreedyBFS(Cell *cellArr){

}

void updateCells(Cell *cellArr, User *user){
  drawCells(cellArr);
  placeCell(cellArr, user);
  deleteCell(cellArr, user);
  callGreedyBFS(cellArr);
}
