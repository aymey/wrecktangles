#include <SDL2/SDL.h>
#include "draw.h"
#include "global.h"

void draw_player(Program *program, Uint8 r, Uint8 g, Uint8 b) {
    SDL_RenderClear(program->renderer);
    SDL_SetRenderDrawColor(program->renderer, r, g, b, 255);

    SDL_RenderFillRect(program->renderer,
            &(SDL_Rect) {
                0,
                0,
                100,
                100
            });
    SDL_SetRenderDrawColor(program->renderer, 0, 0, 0, 255);
    SDL_RenderPresent(program->renderer);
}
