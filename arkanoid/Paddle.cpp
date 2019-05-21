#include "Paddle.h"

//deplasarea la stanga a paddle-ului 
void Paddle::moveLeft(){
  if(pos != 0)
    pos--;  
}

//deplasarea la dreapta a paddle-ului 
void Paddle::moveRight(){
  if(pos != 8-size)
    pos++;
}
