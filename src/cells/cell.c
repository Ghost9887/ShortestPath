#include "cell.h"

PriorityQueue pq;
bool initializedBFS;
bool playingBFS;
Cell *start = NULL;
Cell *end = NULL;
const float updateTime = 0.1f;
float updateTimer = 0.0f;

int *parent;


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
  // left
  if(index - 1 >= 0 && index - 1 < AMOUNT_OF_CELLS && !cellArr[index - 1].solid && !cellArr[index - 1].visited){
    cells[0] = index - 1;
  }else{
    cells[0] = -1;
  }

  // below
  if(index + GRID_WIDTH >= 0 && index + GRID_WIDTH < AMOUNT_OF_CELLS && !cellArr[index + GRID_WIDTH].solid && !cellArr[index + GRID_WIDTH].visited){
    cells[1] = index + GRID_WIDTH;
  }else{
    cells[1] = -1;
  }

  // right
  if(index + 1 >= 0 && index + 1 < AMOUNT_OF_CELLS && !cellArr[index + 1].solid && !cellArr[index + 1].visited){
    cells[2] = index + 1;
  }else{
    cells[2] = -1;
  }

    // above
  if(index - GRID_WIDTH >= 0 && index - GRID_WIDTH < AMOUNT_OF_CELLS && !cellArr[index - GRID_WIDTH].solid && !cellArr[index - GRID_WIDTH].visited){
    cells[3] = index - GRID_WIDTH;
  }else{
    cells[3] = -1;
  }
  //top left
  if(index - GRID_WIDTH - 1 >= 0 && index - GRID_WIDTH - 1 < AMOUNT_OF_CELLS && !cellArr[index - GRID_WIDTH - 1].solid && !cellArr[index - GRID_WIDTH - 1].visited){
    cells[4] = index - GRID_WIDTH - 1;
  }else{
    cells[4] = -1;
  }

  //top right
  if(index - GRID_WIDTH + 1 >= 0 && index - GRID_WIDTH + 1 < AMOUNT_OF_CELLS && !cellArr[index - GRID_WIDTH + 1].solid && !cellArr[index - GRID_WIDTH + 1].visited){
    cells[5] = index - GRID_WIDTH + 1;
  }else{
    cells[5] = -1;
  }

  //bottom right
  if(index + GRID_WIDTH + 1 >= 0 && index + GRID_WIDTH + 1 < AMOUNT_OF_CELLS && !cellArr[index + GRID_WIDTH + 1].solid && !cellArr[index + GRID_WIDTH + 1].visited){
    cells[6] = index + GRID_WIDTH + 1;
  }else{
    cells[6] = -1;
  }

  //bottom left
  if(index + GRID_WIDTH - 1 >= 0 && index + GRID_WIDTH - 1 < AMOUNT_OF_CELLS && !cellArr[index + GRID_WIDTH - 1].solid && !cellArr[index + GRID_WIDTH - 1].visited){
    cells[7] = index + GRID_WIDTH - 1;
  }else{
    cells[7] = -1;
  }

}


void BFS(Cell *cellArr){
  if(pq.front->index == end->index){
    playingBFS = false;
  }
  //find the neighbours
  Cell *current = dequeue(&pq);
  if(current != start && current != end){
    current->colour = GREEN;
  }
  int *cells = malloc(sizeof(int) * 8); 
  checkNeighbours(cells, cellArr, current->index);
  for(int i = 0; i < 8; i++){
    if(cells[i] != -1){
      cellArr[cells[i]].visited = true;
      enqueue(&pq, &cellArr[cells[i]]);
      parent[cells[i]] = current->index;
    }
  }
  free(cells);
  if(getSize(&pq) <= 0 || !playingBFS){
    playingBFS = false;
    //reconstruct the path
    int currentIndex = end->index;
    while(currentIndex != -1 && currentIndex != start->index){
      cellArr[currentIndex].colour = ORANGE;
      currentIndex = parent[currentIndex];
    }
    free(parent);
    printf("BFS Stopped\n");
  }
}

void initializeBFS(Cell *cellArr){
  if(!initializedBFS){
    printf("BFS Started\n");
    parent = malloc(sizeof(int) * AMOUNT_OF_CELLS);
    for(int i = 0; i < AMOUNT_OF_CELLS; i++){
      parent[i] = -1; // no parent
    }
    pq = createPQ();
      //find the start and end cells
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
    enqueue(&pq, start);
    start->visited = true;
    parent[start->index] = start->index;
    initializedBFS = true;
    playingBFS = true;
  }
  if(playingBFS){
    BFS(cellArr);
  }
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
  if(IsKeyPressed(KEY_SPACE) || playingBFS){
    initializeBFS(cellArr);
  }
}

void updateCells(Cell *cellArr, User *user){
  drawCells(cellArr);
  placeStart(cellArr, user);
  placeEnd(cellArr, user);
  placeSolid(cellArr, user);
  updateTimer += GetFrameTime();
  if(updateTimer >= updateTime || !initializedBFS){
    callBFSAlgo(cellArr);
    updateTimer = 0.0f;
  }
}
