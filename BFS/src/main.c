#include "common.h"
#include "grid.h"
#include "cell.h"
#include "user.h"

void updateGameState(Cell *cellArr, User *user);

int main(){

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shortest Path");
  SetTargetFPS(FPS);

  Cell *cellArr = (Cell*)malloc(sizeof(Cell) * AMOUNT_OF_CELLS);
  initCellArr(cellArr);

  User user = createUser();

  while(!WindowShouldClose()){
    
    BeginDrawing();

      ClearBackground(WHITE);

      updateGameState(cellArr, &user);

    EndDrawing();

  }
  
  free(cellArr);

  CloseWindow();

  return 0;
}

void updateGameState(Cell *cellArr, User *user){

  updateCells(cellArr, user);

  drawGrid();

  updateUser(user);

}
