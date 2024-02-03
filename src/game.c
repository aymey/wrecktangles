#include <stdbool.h>
#include "game.h"

SDL_Rect *Rect2SDL(Rect rect) {
    return &(SDL_Rect) {
        (int)rect.x,
        (int)rect.y,
        rect.w,
        rect.h
    };
}

void apply_forces(GameState *state) {
    state->players[state->turn.player].velocity.i += state->turn.velocity.i;
    state->players[state->turn.player].velocity.j += state->turn.velocity.j;
}

Vector2 get_indicator(GameState *state) {
    // TODO: implement
    state->turn.charge++;

    int cx, cy;
    SDL_GetMouseState(&cx, &cy);

    Rect player = state->players[state->turn.player].rect;

    int dx = cx - player.x+(float)player.w/2;
    int dy = cy - player.y+(float)player.h/2;

    int mag = sqrt(dx*dx + dy*dy);

    return (Vector2) {
            ((float)dx/mag) * IND_RAD,
            ((float)dy/mag) * IND_RAD
        };
}

void game_physics(GameState *state, double delta) {
    for(int i = 0; i < state->amount; i++) {
        Player *player = &state->players[i];

        player->velocity.j *= GRAVITY/2 * delta;
        player->velocity.i *= state->turn.velocity.i;
        player->velocity.i *= AIR_FRI;

        player->rect.x += player->velocity.i;
        player->rect.y += player->velocity.j;
    }
}
