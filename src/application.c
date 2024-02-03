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

    // program->surface = SDL_GetWindowSurface(program->window);
    // if(!program->surface) {
    //     fprintf(stderr, "Failed to get window surface (\"%s\")", SDL_GetError());
    //     return EXIT_FAILURE;
    // }

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
void event_loop(Program *program) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                SDL_DestroyWindow(program->window);
                SDL_Quit();
                exit(0);
                break;

            default:
                break;
        }
    }
}

void loop(Program *program, GameState state) {
    while(true) {
        SDL_UpdateWindowSurface(program->window);
        event_loop(program);
        update(program, 1./60.);
        draw(program, state);
        SDL_Delay(16);
    }
}

void update(Program *program, double delta) {

}

void draw(Program *program, GameState state) {
    SDL_SetRenderDrawColor(program->renderer, BG_R, BG_G, BG_B, 255);
    SDL_RenderClear(program->renderer);

    for(int i = 0; i < state.amount; i++) {
        SDL_SetRenderDrawColor(program->renderer,
                state.players[i].colour.r,
                state.players[i].colour.g,
                state.players[i].colour.b,
                255);
        SDL_RenderFillRect(program->renderer, &state.players[i].rect);
    }

    // SDL_UpdateWindowSurface(program->window);
    SDL_RenderPresent(program->renderer);
}
