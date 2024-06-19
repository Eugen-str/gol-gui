#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "patterns.h"
#include "graphics.h"
#include "game.h"

char field[HEIGHT*WIDTH];

void field_init(char *field){
    for(int i = 0; i < WIDTH*HEIGHT; ++i){
        field[i] = DEAD;
    }
}

void draw_field(char *field){
    system("clear");
    for(int i = 0; i < WIDTH*HEIGHT; ++i){
        if(i%WIDTH==0) printf("\n");
        printf("%c ",field[i]);
    }
    printf("\n\n");
}

void draw_terminal(){
    bool quit = false;
    while (!quit){
        
        draw_field(field);

        update_field(field);

        char c = getchar();
        switch(c){
            case 'q':
                quit = true;
                break;
        }
    }
}

int main(){
    field_init(field);
    //r_petromino(field, WIDTH*HEIGHT/2, WIDTH);
    pentadecathlon(field, WIDTH * 10 - WIDTH /2, WIDTH);

    draw_graphics(field);
    return 0;
}
