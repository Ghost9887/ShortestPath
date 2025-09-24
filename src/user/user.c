#include "user.h"

User createUser(){
  User user;
  user.mode = START;
  return user;
}

void changeMode(User *user){
  if(IsKeyPressed(KEY_ONE)){
    user->mode = START;
  }
  else if(IsKeyPressed(KEY_TWO)){
    user->mode = END;
  }
  else if(IsKeyPressed(KEY_THREE)){
    user->mode = SOLID;
  }
}

void drawMode(User *user){
  if(user->mode == START){
    DrawText("Start", SCREEN_WIDTH - 100, 30, 30, PURPLE);
  }
  else if(user->mode == END){
    DrawText("End", SCREEN_WIDTH - 100, 30, 30, PURPLE);
  }
  else if(user->mode == SOLID){
    DrawText("Solid", SCREEN_WIDTH - 100, 30, 30, PURPLE);
  }
}

void updateUser(User *user){
  drawMode(user);
  changeMode(user);
}
