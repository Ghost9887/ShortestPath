#include "user.h"

User createUser(){
  User user;
  user.mode = START;
  user.placedStart = false;
  user.placedEnd = false;
  return user;
}

void switchModes(User *user){
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

void drawUserMode(User *user){ 
  switch(user->mode){
    case START:
      DrawText("Start", SCREEN_WIDTH - 100, 30, 30, PURPLE);
      break;
    case END:
      DrawText("End", SCREEN_WIDTH - 100, 30, 30, PURPLE);
      break;
    case SOLID:
      DrawText("Solid", SCREEN_WIDTH - 100, 30, 30, PURPLE);
      break;
    default:
      break;
  }
}

void updateUser(User *user){
  switchModes(user);
  drawUserMode(user);
}
