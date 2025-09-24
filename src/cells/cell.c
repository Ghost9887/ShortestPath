#include "cell.h"

Cell createCell(int posX, int posY){
  Cell cell;
  cell.pos = (Vector2){ posX, posY };
  cell.next = NULL;
  cell.colour = WHITE;
  cell.weight = 1;
  cell.solid = false;
  cell.start = false;
  cell.end = false;
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

void placeStart(Cell *cellArr, User *user){
  if(user->mode == START && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    Vector2 mousePos = GetMousePosition();
    int posX = ((int)mousePos.x / CELL_SIZE) * CELL_SIZE;
    int posY = ((int)mousePos.y / CELL_SIZE) * CELL_SIZE;
    for(int i = 0; i < AMOUNT_OF_CELLS; i++){
      if((int)cellArr[i].pos.x == posX && (int)cellArr[i].pos.y == posY && !cellArr[i].end && !cellArr[i].solid){
        cellArr[i].start = true;
        cellArr[i].colour = YELLOW;
      }
      else if(cellArr[i].end){
        continue;
      }
      else{
        cellArr[i].start = false;
        cellArr[i].colour = WHITE;
      }
    }
  }
}

void placeEnd(Cell *cellArr, User *user){
  if(user->mode == END && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    Vector2 mousePos = GetMousePosition();
    int posX = ((int)mousePos.x / CELL_SIZE) * CELL_SIZE;
    int posY = ((int)mousePos.y / CELL_SIZE) * CELL_SIZE;
    for(int i = 0; i < AMOUNT_OF_CELLS; i++){
      if((int)cellArr[i].pos.x == posX && (int)cellArr[i].pos.y == posY && !cellArr[i].start && !cellArr[i].solid){
        cellArr[i].end = true;
        cellArr[i].colour = RED;
      }
      else if(cellArr[i].start){
        continue;
      }
      else{
        cellArr[i].end = false;
        cellArr[i].colour = WHITE;
      }
    }
  }
}

void placeSolid(Cell *cellArr, User *user){
  if(user->mode == SOLID && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    Vector2 mousePos = GetMousePosition();
    int posX = ((int)mousePos.x / CELL_SIZE) * CELL_SIZE;
    int posY = ((int)mousePos.y / CELL_SIZE) * CELL_SIZE;
    int index = (posY / CELL_SIZE) * GRID_WIDTH + (posX / CELL_SIZE);
    cellArr[index].solid = true;
    cellArr[index].colour = BLUE;
  }
  else if(user->mode == SOLID && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
    Vector2 mousePos = GetMousePosition();
    int posX = ((int)mousePos.x / CELL_SIZE) * CELL_SIZE;
    int posY = ((int)mousePos.y / CELL_SIZE) * CELL_SIZE;
    int index = (posY / CELL_SIZE) * GRID_WIDTH + (posX / CELL_SIZE);
    cellArr[index].solid = false;
    cellArr[index].colour = WHITE;
  
  }
}

void drawCells(Cell *cellArr){
  for(int i = 0; i < AMOUNT_OF_CELLS; i++){
    DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, cellArr[i].colour);
  }
}

void updateCells(Cell *cellArr, User *user){
  drawCells(cellArr);
  placeStart(cellArr, user);
  placeEnd(cellArr, user);
  placeSolid(cellArr, user);
}
