#include "cell.h"

bool playing = false;

Cell createCell(int posX, int posY, int index){
  Cell cell;
  cell.pos = (Vector2){ posX, posY };
  cell.next = NULL;
  cell.colour = WHITE;
  cell.distance = 1;
  cell.weight = 1;
  cell.solid = false;
  cell.start = false;
  cell.end = false;
  cell.visited = false;
  cell.index = index;
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

void placeStart(Cell *cellArr, User *user){
  if(user->mode == START && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    Vector2 mousePos = GetMousePosition();
    int posX = ((int)mousePos.x / CELL_SIZE) * CELL_SIZE;
    int posY = ((int)mousePos.y / CELL_SIZE) * CELL_SIZE;
    for(int i = 0; i < AMOUNT_OF_CELLS; i++){
      if((int)cellArr[i].pos.x == posX && (int)cellArr[i].pos.y == posY && !cellArr[i].end && !cellArr[i].solid){
        cellArr[i].start = true;
        cellArr[i].colour = YELLOW;
        cellArr[i].distance = 0;
      }
      else if(cellArr[i].end){
        continue;
      }
      else{
        cellArr[i].start = false;
        cellArr[i].colour = WHITE;
        cellArr[i].distance = INT_MAX;
      }
    }
  }
}


void drawCells(Cell *cellArr){
  for(int i = 0; i < AMOUNT_OF_CELLS; i++){
    DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, cellArr[i].colour);
  }
}

void checkNeighbours(int *cells, Cell *cellArr, int index){
  // above
  if(index - GRID_WIDTH >= 0 && index - GRID_WIDTH < AMOUNT_OF_CELLS && !cellArr[index - GRID_WIDTH].solid && !cellArr[index - GRID_WIDTH].visited){
    cells[0] = index - GRID_WIDTH;
  }else{
    cells[0] = -1;
  }

  // left
  if(index - 1 >= 0 && index - 1 < AMOUNT_OF_CELLS && !cellArr[index - 1].solid && !cellArr[index - 1].visited){
    cells[3] = index - 1;
  }else{
    cells[3] = -1;
  }

  // below
  if(index + GRID_WIDTH >= 0 && index + GRID_WIDTH < AMOUNT_OF_CELLS && !cellArr[index + GRID_WIDTH].solid && !cellArr[index + GRID_WIDTH].visited){
    cells[2] = index + GRID_WIDTH;
  }else{
    cells[2] = -1;
  }

  // right
  if(index + 1 >= 0 && index + 1 < AMOUNT_OF_CELLS && !cellArr[index + 1].solid && !cellArr[index + 1].visited){
    cells[1] = index + 1;
  }else{
    cells[1] = -1;
  }


}

void BFS(Cell *cellArr){

  //used for reconstructing the path
  int *cameFrom = malloc(sizeof(int) * AMOUNT_OF_CELLS);

  //find the start and end cells
  Cell *start = NULL;
  Cell *end = NULL;
  for(int i = 0; i < AMOUNT_OF_CELLS; i++){
    if(cellArr[i].start){
      start = &cellArr[i];
    }
    else if(cellArr[i].end){
      end = &cellArr[i];
    }
  }

  //check if its valid
  if(start == NULL || end == NULL){
    printf("Invalid path given\n");
    return;
  }

  PriorityQueue pq = createPQ();
  enqueue(&pq, start);
  start->visited = true;
  cameFrom[start->index] = -1;
  while(pq.size > 0){
    if(pq.front->index == end->index){
      break;
    }
   //find the neighbours
    Cell *current = dequeue(&pq);
    int *cells = malloc(sizeof(int) * 4); // 4 neighbours 
    checkNeighbours(cells, cellArr, current->index);
    for(int i = 0; i < 4; i++){
      if(cells[i] != -1){
        cellArr[cells[i]].visited = true;
        cameFrom[cells[i]] = current->index;
        enqueue(&pq, &cellArr[cells[i]]);
      }
    }
    free(cells);
  }

  //reconstruct the path
  int index = end->index;
  while(index != start->index){
    if(index != end->index && index != start->index){
      cellArr[index].colour = ORANGE;
    }
    printf(" %d ->", index);
    index = cameFrom[index];
  }
  free(cameFrom);
}

void aStarAlgo(Cell *cellArr){

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



void callBFSAlgo(Cell *cellArr){
  if(IsKeyPressed(KEY_SPACE) && !playing){
    BFS(cellArr);
  }
}

void updateCells(Cell *cellArr, User *user){
  drawCells(cellArr);
  placeStart(cellArr, user);
  placeEnd(cellArr, user);
  placeSolid(cellArr, user);
  callBFSAlgo(cellArr);
}
