#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "global.h"
#include "draw.h"
#include <SDL2/SDL.h>

// returns error codes
int init_SDL(Program *program) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
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
    SDL_SetRenderDrawColor(program->renderer, 32, 36, 46, 255);
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

int main(void) {
    Program program;
    init_SDL(&program);

    while(true) {
        event_loop(&program);
        draw_player(&program, 10, 10, 10);
        SDL_Delay(16);
    }

    SDL_DestroyWindow(program.window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
