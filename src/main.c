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
            (Rect) {
                500., 500.,
                50, 100
            },
            (Vector2) {
                1., 1.
            },
            (Colour) {
                0xFF, 0xFF, 0xFF
            }
        },
        1,
        (Turn) {
            0,
            0,
            (Vector2) {0., 0.}
        }
    };

    loop(&program, &game);

    return EXIT_SUCCESS;
}
