#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <stddef.h>

enum dir_e { NONE, UP, DOWN, LEFT, RIGHT };

struct __snake_t {
    int         x, y;
    size_t      len;
    enum dir_e  dir;
};

typedef struct __snake_t snake_t;

extern void init_snake(snake_t* snake);

#endif
