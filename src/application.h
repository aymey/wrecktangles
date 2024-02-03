#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SDL2/SDL.h>
#include "game.h"

#define BG_R 32
#define BG_G 36
#define BG_B 45

#define SET_COLOUR(renderer, colour)                \
        SDL_SetRenderDrawColor(renderer,            \
                colour.r,                           \
                colour.g,                           \
                colour.b,                           \
                255)

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    double delta;
} Program;

// sdl window stuff
int init_app(Program *program);
void event_loop(Program *program, GameState *state);

// loop
void loop(Program *program, GameState *state);
void update(Program *program, GameState *state);
void draw(Program *program, GameState *state);

#endif // __APPLICATION_H__
