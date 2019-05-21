#define SELECT 2
#define START_SPEED 5   //viteza bilei
#define PADDLE_START 2  //pozitia de start a paddle-ului 
#define PADDLE_SIZE 3   //dimensiunea paddle-ului
#define BRICKS 24       //numarul de caramizi

enum {START, WON, LOST, PLAY, SETUP} state = SETUP;
enum {LEFT, RIGHT, NONE} controls = NONE;
enum {SEL, NO} actions = NO;
