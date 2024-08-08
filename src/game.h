#ifndef __GAME_H__
#define __GAME_H__

#include "snake.h"

struct __game_t {
    int     field[H_FIELD][W_FIELD];
    snake_t player;
    bool    running;
    int     score;
};

typedef struct __game_t game_t;

extern void init_game(game_t* game);
extern void update_game(game_t* game);

#endif
