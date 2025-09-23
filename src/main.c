#include "common.h"
#include "grid.h"
#include "cell.h"

void updateGameState(Cell *cellArr);

int main(){

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shortest Path");
  SetTargetFPS(FPS);

  Cell *cellArr = (Cell*)malloc(sizeof(Cell) * AMOUNT_OF_CELLS);
  initCellArr(cellArr);

  while(!WindowShouldClose()){
    
    BeginDrawing();

      ClearBackground(WHITE);

      updateGameState(cellArr);

    EndDrawing();

  }
  
  free(cellArr);

  CloseWindow();

  return 0;
}

void updateGameState(Cell *cellArr){

  drawGrid();

  updateCells(cellArr);

}
