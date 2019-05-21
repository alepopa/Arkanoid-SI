#define MAX7219DIN 4
#define MAX7219CS 5
#define MAX7219CLK 6
#define JOYX A1


#include "Breakout.h"
#include "LedControl.h"

int count = 0;
Breakout breakout;
LedControl lc=LedControl(4,6,5,1); 

void setup(){
  
   pinMode(SELECT,INPUT_PULLUP); //declaram butonul joystick-ului
   lc.shutdown(0, false);  //device-ul nu este in modul de power save
   lc.setIntensity(0, 8); //setam intensitatea luminoasa
  
}

void loop() {
 switch(state){
    // setarile de configurare a jocului
    case SETUP:
    
      breakout.restart();
      breakout.speed = START_SPEED; 

        state = START;
        break;

    case START:
    // daca apasam butonul, jocul intra in starea PLAY

      checkActions();
      
        if(actions == SEL){
        state = PLAY; 
      }
      break;
      
    case LOST:
    //in caz de infrangere, se refac setarile initiale ale jocului si
    //vom reveni in starea de START

      reDraw();
      breakout.restart();
      breakout.speed = START_SPEED;
      state = START;
      break;

    case WON:
    // in caz de victorie, putem juca din nou, dar la un grad de dificultate mai mare

      breakout.won(); 
      reDraw();
      breakout.restart();
      state = START;
      break;
      
    case PLAY:
      // determinam in care din starile jocului ne aflam
      {
        if(count > breakout.speed){
          checkControls();
          
          breakout.play(controls);
          count = 0;
        
          if(breakout.bricks == 0){
          state = WON;
          }
          if(breakout.ball.y == 0)
            state = LOST;
          }
        delay(20);
        count++;
      }
  }
  reDraw();
}

//functie prin care reconfiguram starea de inceput a jocului
void reDraw(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(breakout.level[i][8-j-1] != 'E'){ 
        lc.setLed(0, i, j, true); //cu ajutorul acestei functii setam fiecare led in mod individual
      }
      else
        lc.setLed(0, i, j, false);
    }  
  }
}

//verificam daca butonul joystick-ului a fost apasat
void checkActions(){
  int count = 0;
  while(count < 5 && digitalRead(SELECT) == LOW){
    count++;
  }
  if(count > 4){
    actions = SEL;
    return;
  }
  actions = NO;
}

//verificam daca joystick-ul a fost inclinat catre stanga sau dreapta
void checkControls(){
  int count = 0;
  while(count < 5 && analogRead(JOYX)<256){
    count++;
  }
  if(count > 4){
    controls = LEFT;
    return;
  }
  count = 0;
  while(count < 5 && analogRead(JOYX)>768){
    count++;
  }
  if(count > 4){
    controls = RIGHT;
    return;
  }
  
  controls = NONE;
}
