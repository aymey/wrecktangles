#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>
#include <SDL2/SDL.h>

#define GRAVITY 9.81/10 + .1
#define IND_RAD 100

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
} Colour;

typedef struct {
    float i;
    float j;
} Vector2;

typedef struct {
    float x, y;
    Uint8 w, h;
} Rect;

typedef struct {
    Rect rect;
    Vector2 velocity;
    Colour colour;
} Player;

typedef struct {
    Uint8 player;       // the player whos turn it is
    bool active;        // is player moving
    Vector2 velocity;  // the velocity of the turn
} Turn;

typedef struct {
    Player *players;    // players
    Uint8 amount;       // total amount of players
    Turn turn;
} GameState;

SDL_Rect *Rect2SDL(Rect rect);          // translate Rect to SDL_Rect

void game_physics(GameState *state);    // compute physics like player movement
Vector2 get_indicator(GameState *state);// returns the ending coords of indicator (doesnt include player pos offset)

#endif // __GAME_H__
