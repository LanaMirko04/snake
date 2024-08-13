#ifndef __DEFS_H__
#define __DEFS_H__

#ifndef OK
    #define OK 0
#endif

#ifndef ERR
    #define ERR -1
#endif

#define LOG_FILE_PATH   "/tmp/snake.log"

#define KEY_ESC 27

#define MILLIS_EASY     150
#define MILLIS_NORMAL   100
#define MILLIS_HARD     70

#define H_FIELD 18
#define W_FIELD 32
#define Y_GWIN  ((LINES - (H_FIELD + 2)) / 2)
#define X_GWIN  ((COLS - (W_FIELD * 2 +2)) / 2)

#define APPLE       -1

#define APPLE_PAIR 1
#define SNAKE_PAIR 2

#define APPLE_SCORE 5 
#define WARP_MALUS  -2

#endif
