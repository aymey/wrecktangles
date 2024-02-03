#include <stdio.h>
#include <stdlib.h>

#include "application.h"
#include <SDL2/SDL.h>

int main(void) {
    Program program;
    if(init_app(&program)) {
        return EXIT_FAILURE;
    }

    GameState game = (GameState) {
        &(Player) {
            (SDL_Rect) {
                0, 0,
                100, 100
            },
            (Colour) {
                0xFF, 0xFF, 0xFF
            }
        },
        1
    };

    loop(&program, game);

    return EXIT_SUCCESS;
}
