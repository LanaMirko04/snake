#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>

#include "defs.h"
#include "slog.h"
#include "tui.h"
#include "game.h"

static WINDOW* outer = NULL;
static WINDOW* inner = NULL;

static int create_windows(void) {
    SLOG_INFO("Attempting to create the outer window.");
    outer = newwin(H_FIELD + 2, W_FIELD * 2 + 2, Y_GWIN, X_GWIN);
    if (outer == NULL) {
        SLOG_ERROR("Outer window creation failed.");
        return ERR;
    }
    SLOG_INFO("Outer window created successfully.");

    SLOG_INFO("Attempting to create the border for the outer window.");
    if (box(outer, 0, 0) == ERR) {
        SLOG_ERROR("Outer border creation failed.");
        delwin(outer);
        return ERR;
    }
    SLOG_INFO("Outer border created successfully.");

    wrefresh(outer);

    SLOG_INFO("Attempting to create the inner window.");
    inner = derwin(outer, H_FIELD, W_FIELD * 2, 1, 1);
    if (inner == NULL) {
        SLOG_ERROR("Inner window creation failed.");
        delwin(outer);
        return ERR;
    }
    SLOG_INFO("Inner window created successfully.");

    wrefresh(inner);

    return OK;
}

static int init_colors() {
    SLOG_INFO("Checking if the terminal supports colors.");
    if (!has_colors()) {
        SLOG_ERROR("Terminal does not support colors.");
        return ERR;
    }

    SLOG_INFO("Initializing color support in ncurses.");
    if (start_color() == ERR) {
        SLOG_ERROR("Failed to initialize color support.");
        return ERR;
    }
    SLOG_INFO("Color support initialized successfully.");

    SLOG_INFO("Creating color pair for apples (#%d): fg = RED, bg = BLACK.",
            APPLE_PAIR);
    if (init_pair(APPLE_PAIR, COLOR_RED, COLOR_BLACK) == ERR) {
        SLOG_ERROR("Failed to create color pair for apples.");
        return ERR;
    }
    SLOG_INFO("Color pair for apples created successfully.");

    SLOG_INFO("Creating color pair for the snake (#%d): fg = WHITE, bg = RED.",
            SNAKE_PAIR);
    if (init_pair(SNAKE_PAIR, COLOR_WHITE, COLOR_GREEN) == ERR) {
        SLOG_ERROR("Failed to create color pair for the snake.");
        return ERR;
    }
    SLOG_INFO("Color pair for the snake created successfully.");

    // Uncomment if you want to use default colors
    // SLOG_INFO("Using default colors.");
    // use_default_colors();

    return OK;
}

//
//-----------------------------------------------------------------------------

int init_tui(void) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    curs_set(false);

    if (init_colors() == ERR) {
        SLOG_ERROR("Failed to initialize color support | %s.", strerror(errno));
        return ERR;
    }

    return OK;
}

int clear_tui(void) {
    return endwin();
}

enum event_e handle_input(int keycode) {
    switch (keycode) {
        case 'w':
        case 'W':
        case KEY_UP:
            return EV_CHDIR_UP;

        case 'a':
        case 'A':
        case KEY_LEFT:
            return EV_CHDIR_LEFT;
        
        case 's':
        case 'S':
        case KEY_DOWN:
            return EV_CHDIR_DOWN;

        case 'd':
        case 'D':
        case KEY_RIGHT:
            return EV_CHDIR_RIGHT;

        case 'q':
        case 'Q':
        case KEY_ESC:
            return EV_QUIT;

        default:
            return EV_NONE;
    }
}

int draw_game(const game_t* game) {
    if (outer == NULL && inner == NULL) {
        SLOG_INFO("First 'draw_game()' call: creating game windows.");
        if (create_windows() == ERR) {
            SLOG_ERROR("Failed to initialize game windows | %s.",
                    strerror(errno));
            return ERR;
        }
        SLOG_INFO("Game's windows created successfully.");
    }

    // do not remove (IMPORTANT!)
    werase(inner);

    for (size_t y = 0; y < H_FIELD; ++y) {
        for (size_t x = 0; x < W_FIELD; ++x) {
            if (game->field[y][x] == APPLE) {
                wattron(inner, COLOR_PAIR(APPLE_PAIR));
                mvwprintw(inner, y, x * 2, "CO");
                wattroff(inner, COLOR_PAIR(APPLE_PAIR));
            } else if (game->field[y][x] > 0) {
                wattron(inner, COLOR_PAIR(SNAKE_PAIR));
                mvwprintw(inner, y, x * 2, "  ");
                wattroff(inner, COLOR_PAIR(SNAKE_PAIR));
            }
        }
    }

    mvwprintw(outer, 0, 1, "[ SCORE: %5d ]", game->score);

    wrefresh(outer);
    wrefresh(inner);

    return OK;
}
