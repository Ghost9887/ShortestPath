#include "cell.h"

PriorityQueue pq;
Cell *start;
Cell *end;

bool initialized = false;
bool running = false;

Cell createCell(int posX, int posY, int id){
  Cell cell;
  cell.id = id;
  cell.pos = (Vector2){ posX, posY };
  cell.next = NULL;
  cell.start = false;
  cell.end = false;
  cell.solid = false;
  cell.visited = false;
  cell.distance = INT_MAX;
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
    else if(cellArr[i].visited){
      DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, GREEN);
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

float heuristic(Cell *cell){
  return(fabs(cell->pos.x - end->pos.x) + fabs(cell->pos.y - end->pos.y));
}

int *checkNeighbours(Cell *cellArr, int index){
  int *cells = malloc(sizeof(int) * 8);
  //top
  if(index - GRID_WIDTH > 0 && !cellArr[index - GRID_WIDTH].solid && !cellArr[index - GRID_WIDTH].visited){
    cells[0] = index - GRID_WIDTH;
  }
  else{
    cells[0] = -1;
  }
  //left
  if(index - 1 > 0 && !cellArr[index - 1].solid && !cellArr[index - 1].visited){
    cells[1] = index - 1;
  }else{
    cells[1] = -1;
  }

  //bottom
  if(index + GRID_WIDTH < AMOUNT_OF_CELLS && !cellArr[index + GRID_WIDTH].solid && !cellArr[index + GRID_WIDTH].visited){
    cells[2] = index + GRID_WIDTH;
  }else{
    cells[2] = -1;
  }

  //right
  if(index + 1 < AMOUNT_OF_CELLS && !cellArr[index + 1].solid && !cellArr[index + 1].visited){
    cells[3] = index + 1;
  }else{
    cells[3] = -1;
  }

  //top left
  if(index - GRID_WIDTH - 1 > 0 && !cellArr[index - GRID_WIDTH - 1].solid && !cellArr[index - GRID_WIDTH - 1].visited){
    cells[4] = index - GRID_WIDTH - 1;
  }else{
    cells[4] = -1;
  }

  //top right
  if(index - GRID_WIDTH + 1 > 0 && !cellArr[index - GRID_WIDTH + 1].solid && !cellArr[index - GRID_WIDTH + 1].visited){
    cells[5] = index - GRID_WIDTH + 1;
  }else{
    cells[5] = -1;
  }

  //bottom left
  if(index + GRID_WIDTH - 1 < AMOUNT_OF_CELLS && !cellArr[index + GRID_WIDTH - 1].solid && !cellArr[index + GRID_WIDTH - 1].visited){
    cells[6] = index + GRID_WIDTH - 1;
  }
  else{
    cells[6] = -1;
  }

  //bottom right
  if(index + GRID_WIDTH + 1 < AMOUNT_OF_CELLS && !cellArr[index + GRID_WIDTH + 1].solid && !cellArr[index + GRID_WIDTH + 1].visited){
    cells[7] = index + GRID_WIDTH + 1;
  }
  else{
    cells[7] = -1;
  }
  return cells;
}

void GreedyBFS(Cell *cellArr){
  if(pq.front->id == end->id){
    running = false;
    return;
  }
  Cell *current = dequeue(&pq);
  int *cells = checkNeighbours(cellArr, current->id);
  for(int i = 0; i < 8; i++){
    if(cells[i] > -1){
      cellArr[cells[i]].visited = true;
      cellArr[cells[i]].distance = heuristic(&cellArr[cells[i]]);
      enqueue(&pq, &cellArr[cells[i]]);
    } 
  }
  free(cells);
}

void initializeGreedyBFS(Cell *cellArr){
  if(!initialized){
    pq = createPQ();
  
    for(int i = 0; i < AMOUNT_OF_CELLS; i++){
      if(cellArr[i].start){
        start = &cellArr[i];
      }
      else if(cellArr[i].end){
        end = &cellArr[i];
      }
    }
    if(start == NULL || end == NULL){
      printf("Invalid path\n");
      return;
    }
    start->visited = true;
    start->distance = heuristic(start);
    enqueue(&pq, start);
    running = true;
    initialized = true;
  }
  if(running){
    GreedyBFS(cellArr);
  }
}

void callGreedyBFS(Cell *cellArr){
  if(IsKeyPressed(KEY_SPACE) || running){
    initializeGreedyBFS(cellArr);
  }
}

void updateCells(Cell *cellArr, User *user){
  drawCells(cellArr);
  placeCell(cellArr, user);
  deleteCell(cellArr, user);
  callGreedyBFS(cellArr);
}
