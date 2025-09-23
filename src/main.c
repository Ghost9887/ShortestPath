#include "common.h"
#include "grid.h"

void updateGameState();

int main(){

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shortest Path");
  SetTargetFPS(FPS);

  while(!WindowShouldClose()){
    
    BeginDrawing();

      ClearBackground(WHITE);

      updateGameState();

    EndDrawing();

  }
  
  CloseWindow();

  return 0;
}

void updateGameState(){

  drawGrid();

}
