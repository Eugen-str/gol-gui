#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <stdbool.h>

#include "global.h"
#include "game.h"

#define WINDOW_HEIGHT 768
#define WINDOW_WIDTH 1024

#define SQUARE_SIZE 50
#define SQUARE_PAD 2

#define WALL_COLOUR 10, 10, 10, 255
#define DEAD_COLOUR 24, 24, 24, 255
#define ALIVE_COLOUR 230, 230, 230, 255


int delay = 1000;

typedef struct{
    bool left;
    bool right;
    bool up;
    bool down;
}Movement;

typedef struct{
    int x;
    int y;
}Vec2;

void handle_click(char field[], Vec2 pos, Vec2 mouse_pos, double fov, bool state){
    int x, y;
    int len = SQUARE_SIZE * fov;

    x = (-pos.x + mouse_pos.x) / len;
    y = (-pos.y + mouse_pos.y) / len;

    if(x < 0 || x > WIDTH || y < 0 || y > HEIGHT){ return; }

    if(state){
        field[y*WIDTH + x] = ALIVE;
    }
    else{
        field[y*WIDTH + x] = DEAD;
    }
}

void draw(SDL_Renderer *renderer, char field[], Vec2 pos, double fov){
    SDL_SetRenderDrawColor(renderer, WALL_COLOUR);
    SDL_RenderClear(renderer);

    for(int i = 0; i < WIDTH*HEIGHT; i++){
        int len = SQUARE_SIZE * fov;

        int x = (i % WIDTH) * len + pos.x + SQUARE_PAD;
        int y = (i / WIDTH) * len + pos.y + SQUARE_PAD;
     
        if(!(x > WINDOW_WIDTH || y > WINDOW_WIDTH)){
            if(field[i] == DEAD){
                SDL_SetRenderDrawColor(renderer, DEAD_COLOUR);
            }
            else{
                SDL_SetRenderDrawColor(renderer, ALIVE_COLOUR);
            }
            SDL_Rect rect = (SDL_Rect){.x = x, .y = y, .h = len - SQUARE_PAD*2, .w = len - SQUARE_PAD*2};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
}

void draw_graphics(char field[]){
    bool paused = false;
    int timer = 0;
    int speed_k = 10;
    double fov_k = 1.1;
    Movement movement = {0};

    double fov = 1;
    Vec2 pos = {.x = 0, .y = 0};
    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_Window *window;
    window = SDL_CreateWindow("Game of Life", 30, 30, 
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Event e;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    {
                        int mouse_x, mouse_y;
                        int mouse_button = SDL_BUTTON(SDL_GetMouseState(&mouse_x, &mouse_y));
                        if(mouse_button == 1){
                            handle_click(field, pos, (Vec2){.x = mouse_x, .y = mouse_y}, fov, true);
                        } else if (mouse_button == 8){
                            handle_click(field, pos, (Vec2){.x = mouse_x, .y = mouse_y}, fov, false);
                        }
                        break;
                    }
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_SPACE:
                            paused = !(paused);
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_PLUS:
                            delay /= 2;
                            break;
                        case SDLK_MINUS:
                            delay *= 2;
                            break;
                        case SDLK_UP:
                            movement.up = true;
                            break;
                        case SDLK_DOWN:
                            movement.down = true;
                            break;
                        case SDLK_RIGHT:
                            movement.right = true;
                            break;
                        case SDLK_LEFT:
                            movement.left = true;
                            break;
                    }
                    
                    break;
                case SDL_KEYUP:
                    switch(e.key.keysym.sym){
                        case SDLK_UP:
                            movement.up = false;
                            break;
                        case SDLK_DOWN:
                            movement.down = false;
                            break;
                        case SDLK_RIGHT:
                            movement.right = false;
                            break;
                        case SDLK_LEFT:
                            movement.left = false;
                            break;
                    }
                    
                    break;
                case SDL_MOUSEWHEEL:
                    if(e.wheel.y > 0 && fov < 2) // scroll up
                    {
                        fov *= fov_k;
                    }
                    else if(e.wheel.y < 0 && fov > 0.5) // scroll down
                    {
                        fov /= fov_k;
                    }
                    break;
            }
        }
        if(timer % 200 == 0){
            if(movement.down && pos.y > (-500 - WINDOW_HEIGHT) * (3 * fov)){
                pos.y -= speed_k;
            }
            if(movement.up && pos.y < 500){
                pos.y += speed_k;
            }
            if(movement.left && pos.x < 500){
                pos.x += speed_k;
            }
            if(movement.right && pos.x > (-500 - WINDOW_WIDTH) * (3 * fov)){
                pos.x -= speed_k;
            }
            draw(renderer, field, pos, fov);
        }
        if(timer >= delay && !paused){
            update_field(field);
            draw(renderer, field, pos, fov);
            timer = 0;
        }
        timer++;
    }
}
