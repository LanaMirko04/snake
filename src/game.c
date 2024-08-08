#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "slog.h"
#include "game.h"
#include "snake.h"

static void add_apple(int field[H_FIELD][W_FIELD]) {
    int x, y;

    do {
        x = rand() % W_FIELD;
        y = rand() % H_FIELD;
    } while (field[y][x] != 0);

    field[y][x] = APPLE;
}

//
//-----------------------------------------------------------------------------

void init_game(game_t* game) {
    memset(&game->field, 0, sizeof(game->field));
    init_snake(&game->player);
    game->running = true;
    game->score = 0;

    game->field[game->player.y][game->player.x] = game->player.len;
    add_apple(game->field);
}

void update_game(game_t* game) {
    SLOG_DEBUG("Old position: x=%d y=%d",
            game->player.y, game->player.x);

    switch (game->player.dir) {
        case UP:
            if (game->player.y == 0) {
                game->player.y = H_FIELD;
                game->score += WARP_MALUS;
            }
            game->player.y--;
            break;
            
        case DOWN:
            if (++game->player.y >= H_FIELD) {
                game->player.y %= H_FIELD;
                game->score += WARP_MALUS;
            }
            break;
            
        case LEFT:
            if (game->player.x == 0) {
                game->player.x = W_FIELD;
                game->score += WARP_MALUS;
            }
            game->player.x--;

            break;
            
        case RIGHT:
            if (++game->player.x >= W_FIELD) {
                game->player.x %= W_FIELD;
                game->score += WARP_MALUS;
            }   
            break;
            
        case NONE:
        default:
            return;
    }

    SLOG_DEBUG("New position: x=%d y=%d",
            game->player.y, game->player.x);
    
    if (game->field[game->player.y][game->player.x] == APPLE) {
        game->player.len++;
        game->field[game->player.y][game->player.x] = game->player.len;
        add_apple(game->field);
        game->score += APPLE_SCORE;
    } else if (game->field[game->player.y][game->player.x] > 0) {
        game->running = false;
    } else {
        for (size_t y = 0; y < H_FIELD; ++y) {
            for (size_t x = 0; x < W_FIELD; ++x) {
                if (game->field[y][x] > 0) {
                    game->field[y][x]--;
                }
            }
        }
        game->field[game->player.y][game->player.x] = game->player.len;
    }
}
