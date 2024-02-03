#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include "application.h"

// returns error codes
int init_app(Program *program) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL couldnt initialize (\"%s\")\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    program->window = SDL_CreateWindow("wrecktangles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if(!program->window) {
        fprintf(stderr, "Couldnt create window (\"%s\")", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    program->renderer = SDL_CreateRenderer(program->window, -1, SDL_RENDERER_ACCELERATED);
    if(!program->renderer) {
        fprintf(stderr, "Failed to create renderer (\"%s\")", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetRenderDrawColor(program->renderer, BG_R, BG_G, BG_B, 255);
    SDL_RenderClear(program->renderer);
    SDL_RenderPresent(program->renderer);

    return EXIT_SUCCESS;
}

// program event loop
void event_loop(Program *program, GameState *state) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                SDL_DestroyWindow(program->window);
                SDL_Quit();
                exit(0);
                break;

            // for turns
            case SDL_MOUSEBUTTONDOWN:
                state->turn.charge = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                apply_forces(state);
                state->turn.charge = 0;
                break;

            default:
                break;
        }
    }
}

void loop(Program *program, GameState *state) {
    state->players[0].rect.y =2;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;

    while(true) {
        LAST = NOW;
        SDL_UpdateWindowSurface(program->window);
        event_loop(program, state);
        update(program, state);
        draw(program, *state);
        program->delta = ((double)(NOW - LAST)*1000 / SDL_GetPerformanceFrequency());
        SDL_Delay(16);
    }
}

void update(Program *program, GameState *state) {
    game_physics(state, program->delta);
}

void draw(Program *program, GameState state) {
    SDL_SetRenderDrawColor(program->renderer, BG_R, BG_G, BG_B, 255);
    SDL_RenderClear(program->renderer);

    // draw turn indicator
    if(state.turn.charge) {
        program->delta *= 100;
        Player player = state.players[state.turn.player];
        SET_COLOUR(program->renderer, player.colour);
        Vector2 indicator = get_indicator(&state);

        Vector2 pos = (Vector2) {
            player.rect.x+(float)player.rect.w/2,
            player.rect.y+(float)player.rect.h/2
        };

        SDL_RenderDrawLine(
                program->renderer,
                pos.i,
                pos.j,
                pos.i+indicator.i,
                pos.j+indicator.j);
    }

    // draw players
    for(int i = 0; i < state.amount; i++) {
        SET_COLOUR(program->renderer, state.players[i].colour);
        SDL_RenderFillRect(program->renderer, Rect2SDL(state.players[i].rect));
    }

    // SDL_UpdateWindowSurface(program->window);
    SDL_RenderPresent(program->renderer);
}
