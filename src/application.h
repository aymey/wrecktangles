#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SDL2/SDL.h>

#define BG_R 32
#define BG_G 36
#define BG_B 45

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} Program;

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
} Colour;

typedef struct {
    SDL_Rect rect;
    Colour colour;
} Player;

typedef struct {
    Player *players;
    Uint8 amount;
} GameState;

// sdl window stuff
int init_app(Program *program);
void event_loop(Program *program);

// loop
void loop(Program *program, GameState state);
void update(Program *program, double delta);
void draw(Program *program, GameState state);

#endif // __APPLICATION_H__
