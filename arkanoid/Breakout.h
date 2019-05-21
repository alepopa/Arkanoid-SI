#include "ball.h"
#include "config.h"
#include "paddle.h"
#include "Arduino.h"

class Breakout
{
  Paddle paddle = {PADDLE_START, PADDLE_SIZE};  //obiect de tip paddle
  
  void moveBall();
  void checkCollision();
  void resetBricks();
  void movePaddle(int controls);
  void checkSides();
  void hitEnd();
  void hitPaddle();

  public:
  Ball ball = {PADDLE_START + paddle.size/2, 1, 0, 1}; //obiect de tip minge
  //acest vector il folosim pentru a avea o imagine clara a matricei.
  //avem 4 valori: E=Empty
  //               O=Ball
  //               P=Paddle
  //               B=Bricks
  char level[8][8];  
  int speed = START_SPEED;
  int bricks = BRICKS;
  
  void restart();
  void updatePaddle();
  void won();
  void lost();
  void play(int controls);
  
};
