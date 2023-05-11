#include "patterns.h"

#define ALIVE '#'
#define DEAD '.'

//// Still patterns

void block(char *field, int position, int width){
    field[position] = ALIVE;
    field[position+1] = ALIVE;
    field[position+width] = ALIVE;
    field[position+width+1] = ALIVE;
}

void tub(char *field, int position, int width){
    field[position] = ALIVE;
    field[position+width+1] = ALIVE;
    field[position+width-1] = ALIVE;
    field[position+2*width] = ALIVE;
}

void beehive(char *field, int position, int width){
    field[position] = ALIVE;
    field[position+1] = ALIVE;
    field[position+width-1] = ALIVE;
    field[position+width+2] = ALIVE;
    field[position+2*width] = ALIVE;
    field[position+2*width+1] = ALIVE;
}

//// Oscillators

void toad(char *field, int position, int width){
    field[position] = ALIVE;
    field[position+1] = ALIVE;
    field[position+2] = ALIVE;
    field[position+width-1] = ALIVE;
    field[position+width] = ALIVE;
    field[position+width+1] = ALIVE;
}

void blinker(char *field, int position){
    field[position] = ALIVE;
    field[position+1] = ALIVE;
    field[position-1] = ALIVE;
}

//// Spaceships

void glider(char *field, int position, int width){
    field[position+1] = ALIVE;
    field[position+width+2] = ALIVE;
    field[position+2*width] = ALIVE;
    field[position+2*width+1] = ALIVE;
    field[position+2*width+2] = ALIVE;
}

void pentadecathlon(char *field, int position, int width){
    field[position+2] = ALIVE;
    field[position+7] = ALIVE;
    for(int i = 0; i <= 9; ++i){
        field[position+width+i] = ALIVE;
    }
    field[position+width+2] = DEAD;
    field[position+width+7] = DEAD;
    field[position+width*2+2] = ALIVE;
    field[position+width*2+7] = ALIVE;
}

//// Other
void r_petromino(char *field, int position, int width){
    field[position+1] = ALIVE;
    field[position+2] = ALIVE;
    field[position+width] = ALIVE;
    field[position+width+1] = ALIVE;
    field[position+width*2+1] = ALIVE;
}