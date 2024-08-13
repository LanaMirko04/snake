#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#include "defs.h"
#include "slog.h"
#include "game.h"
#include "tui.h"

#define ERROR(fmt, ...) do { \
    SLOG_ERROR(fmt __VA_OPT__(,) __VA_ARGS__); \
    exit(EXIT_FAILURE); \
} while (false)

[[noreturn]]
static void print_help(int code) {
    printf(
            "\033[4mUsage:\033[0m snake [OPTIONS]\n"
            "\n"
            "\033[4mOptions:\033[0m\n"
            "  -h           Show this help message and exit.\n"
            "  -d           Specify the difficulty of the game (easy, normal,\n"
            "               hard). Default is normal.\n"
            "\n"
            "\033[4mControls:\033[0m\n"
            "  Arrow keys   Move the snake (Up, Down, Left, Right).\n"
            "  W            Move Up.\n"
            "  A            Move Left.\n"
            "  S            Move Down.\n"
            "  D            Move Right.\n"
            "  Q            Quit the game.\n"
            "\n"
            "\033[4mDescription:\033[0m\n"
            "  A classic arcade Snake game with a twist: when you hit the\n"
            "  wall you don't die; instead, you lose points.\n"
            "\n"
          );
    exit(code);
}

// An ugly and dumb way to handle CLI arguments
static int handle_cli_args(int argc, char* argv[]) {
    if (argc > 3) {
        print_help(EXIT_FAILURE);
    } else if (argc == 1) {
        return MILLIS_NORMAL;
    } else {
        if ((argv[1][0] != '-') || (strlen(argv[1]) > 2)) {
            print_help(EXIT_FAILURE);
        }

        switch (argv[1][1]) {
            case 'h':
                print_help(EXIT_SUCCESS);

            case 'd':
                if (!strncmp(argv[2], "easy", 4)) {
                    return MILLIS_EASY;
                } else if (!strncmp(argv[2], "normal", 6)) {
                    return MILLIS_NORMAL;
                } else if (!strncmp(argv[2], "hard", 4)) {
                    return MILLIS_HARD;
                } else {
                    print_help(EXIT_FAILURE);
                }

            default:
                print_help(EXIT_FAILURE);
        }
    }
}

//
//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    srand(time(NULL));
    SLOG_INIT(LOG_FILE_PATH, LV_ALL ^ LV_DEBUG);

    SLOG_INFO("Parsing CLI arguments.");
    int millis = handle_cli_args(argc, argv);
    SLOG_DEBUG("'timeout(...)' millis: %d", millis);

    game_t game = { 0 };
    init_game(&game);

    SLOG_INFO("Initializing the TUI.");
    if (init_tui() == ERR) {
        clear_tui();
        ERROR("Failed to initialize the TUI.");
    }
    SLOG_INFO("TUI initialized successfully.");

    timeout(millis);

    SLOG_INFO("Starting the game.");
    while (game.running) {
        int ch = getch();
        SLOG_DEBUG("Pressed key: %d", ch);

        switch (handle_input(ch)) {
            case EV_CHDIR_UP:
                if (game.player.dir != DOWN) {
                    game.player.dir = UP;
                }
                break;

            case EV_CHDIR_LEFT:
                if (game.player.dir != RIGHT) {
                    game.player.dir = LEFT;
                }
                break;

            case EV_CHDIR_DOWN:
                if (game.player.dir != UP) {
                    game.player.dir = DOWN;
                }
                break;

            case EV_CHDIR_RIGHT:
                if (game.player.dir != LEFT) {
                    game.player.dir = RIGHT;
                }
                break;

            case EV_QUIT:
                game.running = false;
                break;

            case EV_NONE:
            default:
                break;
        }       

        update_game(&game);
        
        if (draw_game(&game) == ERR) {
            ERROR("Failed to draw the game.");
        }

    }

    clear_tui();
    //SLOG_INFO("TUI cleared successfully");
    
    // Temporary solution
    printf(
            "\033[1m======================\033[0m\n"
            "\033[1m     GAME RESULTS     \033[0m\n"
            "\033[1m======================\033[0m\n"
            "\033[4m\033[1mScore:\033[0m%16d\n"
            "\033[4m\033[1mApples:\033[0m%15ld\n"
            "\033[1m======================\033[0m\n",
            game.score,
            game.player.len - 1
        );
    
    return OK;
}

