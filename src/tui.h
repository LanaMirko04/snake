#ifndef __TUI_H__
#define __TUI_H__

#include "game.h"

enum event_e {
    EV_NONE,
    EV_CHDIR_UP,
    EV_CHDIR_LEFT,
    EV_CHDIR_DOWN,
    EV_CHDIR_RIGHT,
    EV_QUIT
};

extern int init_tui(void);
extern int clear_tui(void);
extern enum event_e handle_input(int keycode);
extern int draw_game(const game_t* game);

#endif
