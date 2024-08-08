#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "slog.h"
#include "snake.h"

void init_snake(snake_t* snake) {
    snake->x = rand() % W_FIELD;
    snake->y = rand() % H_FIELD;
    snake->len = 1;
    snake->dir = NONE;
}
