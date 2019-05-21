#include "Ball.h"

void Ball::move(){
  // update pozitie y
  if(dirY > 0){
    y++;
    if(y > 7){
      y = 6;
      down();
    }
  }
  else if(dirY < 0){
    y--;
    if(y < 0){
      y = 1;
      up(); 
    }
  }

  // update pozitie x
  if(dirX > 0){
    x++;
    if(x > 7){
      x = 6;
      bounceLeft();  
    }
  }
  else if(dirX < 0){
    x--;
    if(x < 0){
      x = 1;
      bounceRight(); 
    }  
  }
}

//cazul in care mingea loveste muchia din stanga a paddle-ului
void Ball::bounceBackLeft(){
  dirX = -1;
  dirY = 1;
  x++;
}

//cazul in care mingea loveste muchia din dreapta a paddle-ului
void Ball::bounceBackRight(){
  dirX = 1;
  dirY = 1;
  x--;
}

//cazul in care mingea loveste centrul paddle-ului
void Ball::bounceUp(){
  dirX = 0;
  dirY = 1;
}

//cazul in care mingea loveste partea stanga a paddle-ului
void Ball::bounceLeft(){
  dirX = -1;
}

//cazul in care mingea loveste partea dreapta a paddle-ului
void Ball::bounceRight(){
  dirX = 1;
}

void Ball::up(){
  dirY = 1;
}

void Ball::down(){
  dirY = -1;
}
