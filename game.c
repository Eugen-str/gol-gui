#include <string.h>
#include "game.h"

int neighbors(char *field, int pos){
    int n = 0;

    for(int i = -1; i < 2; ++i){
        if(field[pos+i] == ALIVE && pos+i >= 0 && pos+i <= WIDTH*HEIGHT && pos+i != pos) n++;
        if(field[pos+i+WIDTH] == ALIVE && pos+i+WIDTH >= 0 && pos+i+WIDTH <= WIDTH*HEIGHT) n++;
        if(field[pos+i-WIDTH] == ALIVE && pos+i-WIDTH >= 0 && pos+i-WIDTH <= WIDTH*HEIGHT) n++;
    }

    return n;
}

char next_gen(char *field, int pos){
    /*
    Rules:
    -Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    -Any live cell with two or three live neighbours lives on to the next generation.
    -Any live cell with more than three live neighbours dies, as if by overpopulation.
    -Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    */
    char cell = field[pos];

    if(field[pos] == DEAD && neighbors(field, pos) == 3) cell = ALIVE;
    else{
        if(neighbors(field, pos) < 2) cell = DEAD;
        if(neighbors(field, pos) > 3) cell = DEAD;
    }
    return cell;
}

void update_field(char *field){
    char old_field[WIDTH*HEIGHT];
    strcpy(old_field, field);

    for(int i = 0; i<WIDTH*HEIGHT; ++i){
        field[i] = next_gen(old_field, i);
    }
}