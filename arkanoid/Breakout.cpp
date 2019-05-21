#include "Breakout.h"

//functie de configurare care se apeleaza la inceputul fiecarui joc
void Breakout::restart(){
  paddle = {PADDLE_START, PADDLE_SIZE};           //paddle(pos, size)
  ball = {PADDLE_START + paddle.size/2, 1, 0, 1};   //ball(x, y, dirX, dirY)
  bricks = BRICKS;                                //numarul de caramizi

  resetBricks();
  updatePaddle();
  level[7-ball.y][ball.x] = 'O';
}

//cu aceasta functie aranjam caramizile pe matrice
void Breakout::resetBricks(){
  int bricksSetup = 0; //numarator pentru caramizile deja reprezentate pe matrice
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(bricksSetup < bricks){
        level[i][j] = 'B';  
        bricksSetup++;  //dupa fiecare adaugare, incrementam numaratorul
      }
      else{
        level[i][j] = 'E';
      }
    }  
  }}

//adaugarea paddle-ului
void Breakout::updatePaddle(){
  // initial configuram tot randul ca Empty
  for(int i = 0; i < 8; i++){
    level[7][i] = 'E';
  }
  // adaugam paddle-ul la pozitia specificata
  for(int i = 0; i < paddle.size; i++){
    level[7][paddle.pos+i] = 'P';  
  }
}

void Breakout::won(){
  
  // decrementam variabila pentru viteza, astfel ca bila va merge mai repede
  speed--;

  // viteza nu poate sa fie mai mica decat 3.
  if(speed < 3){
    speed = 3;
  }
}

//functia de joc, verificam coliziunile la fiecare miscare a bilei, si actualizam matricea de observare
void Breakout::play(int controls){
  
  moveBall();
  checkCollision();
  level[7-ball.y][ball.x] = 'O';
  movePaddle(controls);
}

//functie care muta paddle-ul stanga, dreapta
void Breakout::movePaddle(int controls){
  switch(controls){
    case LEFT:
      paddle.moveLeft();
      break;
    case RIGHT:
      paddle.moveRight();
      break;
  }
  updatePaddle();

}

//verificam daca mingea a lovit vreo caramida
void Breakout::checkCollision(){
  // daca vreo caramida  este lovita
  if(level[7-ball.y][ball.x] == 'B'){
    bricks--;
  }
  
  else if(ball.y <= 1){
    
    // daca mingea este in paddle
    if(level[7-ball.y][ball.x] == 'P'){
      ball.y++;
    }
    
    // daca paddle-ul este lovit
    if(level[7-ball.y+1][ball.x] == 'P'){
      hitPaddle();
    }
    checkSides();
  }
}

void Breakout::hitPaddle(){
      // mingea loveste paddle-ul in mijloc
      if(ball.x == paddle.pos+paddle.size/2){
        ball.bounceUp();
      }
      
      // daca mingea loveste pe margini
      else if(ball.dirX == 0){
        hitEnd();
      }
      ball.up();
}
      
void Breakout::hitEnd(){
  // capatul din stanga
  if(ball.x < paddle.pos+paddle.size/2){
    ball.bounceLeft();
  }
        
  // capatul din dreapta
  else if(ball.x > paddle.pos+paddle.size/2){
    ball.bounceRight();
  }
}

void Breakout::checkSides(){
  if(ball.y == 1){
      
    // daca mingea a lovit pe muchia din stanga
    if(ball.dirX == 1 && ball.x == paddle.pos-1){
      ball.bounceBackLeft();
    }
      
    // daca mingea a lovit pe muchia din dreapta
    else if(ball.dirX == -1 && ball.x == paddle.pos + paddle.size){
      ball.bounceBackRight();
    }
  }
}

void Breakout::moveBall(){
  //daca pozitia din matrice e Empty
  level[7-ball.y][ball.x] = 'E';
  ball.move();
}
