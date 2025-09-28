#include "cell.h"

PriorityQueue pq;
Cell *start;
Cell *end;

bool initialized = false;
bool running = false;

int *cameFrom;

Cell createCell(int posX, int posY, int id){
  Cell cell;
  cell.id = id;
  cell.pos = (Vector2){ posX, posY };
  cell.next = NULL;
  cell.start = false;
  cell.end = false;
  cell.solid = false;
  cell.visited = false;
  cell.path = false;
  cell.distance = 0.0f;
  cell.weight = ((int)GetRandomValue(1, 20));
  cell.total = 0;
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
      //DrawText(TextFormat("%d", cellArr[i].weight), cellArr[i].pos.x, cellArr[i].pos.y, 10, BLACK);
    }
    else if(cellArr[i].end){
      DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, RED);
    }
    else if(cellArr[i].solid){
      DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, BLUE);
    }
    else if(cellArr[i].visited || cellArr[i].path){
      if(cellArr[i].visited) DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, GREEN);
      if(cellArr[i].path) DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, PURPLE);
    }
   else{
      DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELL_SIZE, CELL_SIZE, WHITE);
    }
  DrawText(TextFormat("%d", cellArr[i].weight), cellArr[i].pos.x, cellArr[i].pos.y, 10, BLACK);
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

float heuristic(Cell *a, Cell *b){
  return fabs(a->pos.x - b->pos.x) + fabs(a->pos.y - b->pos.y); // Manhattan
}

void AStar(Cell *cellArr){
  if (pq.front == NULL) return;
  Cell *current = dequeue(&pq);
  if (current->id == end->id){
    int curr = end->id;
    while (curr != start->id){
      cellArr[curr].path = true;
      curr = cameFrom[curr];
    }
    running = false;
    free(cameFrom);
    return;
  }
  int *neighbors = checkNeighbours(cellArr, current->id);
  for (int i = 0; i < 8; i++){
    int nid = neighbors[i];
    if (nid == -1 || cellArr[nid].solid) continue;
      float tentativeGScore = cellArr[current->id].distance + cellArr[nid].weight;
      if (!cellArr[nid].visited || tentativeGScore < cellArr[nid].distance){
        cameFrom[nid] = current->id;
        cellArr[nid].distance = tentativeGScore;
        cellArr[nid].total = tentativeGScore + heuristic(&cellArr[nid], end);
        cellArr[nid].visited = true;
        enqueue(&pq, &cellArr[nid]);
      }
  }
  free(neighbors);
}

void initializeAStar(Cell *cellArr){
  if(!initialized){
    pq = createPQ();
    cameFrom = malloc(sizeof(int) * AMOUNT_OF_CELLS);
    for (int i = 0; i < AMOUNT_OF_CELLS; i++){
      cellArr[i].distance = INT_MAX;
      cellArr[i].total = INT_MAX;
      if (cellArr[i].start) start = &cellArr[i];
      else if (cellArr[i].end) end = &cellArr[i];
    }
    if (!start || !end) return;
      start->distance = 0;
      start->total = heuristic(start, end);
      cameFrom[start->id] = start->id;
      enqueue(&pq, start);
      running = true;
      initialized = true;
    }
    if(running){
      AStar(cellArr);
    }
}
void callAStar(Cell *cellArr){
  if(IsKeyPressed(KEY_SPACE) || running){
    initializeAStar(cellArr);
  }
}

void updateCells(Cell *cellArr, User *user){
  drawCells(cellArr);
  placeCell(cellArr, user);
  deleteCell(cellArr, user);
  callAStar(cellArr);
}
