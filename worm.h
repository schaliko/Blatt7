// A simple variant of the game Snake
//
// Used for teaching in classes
//
// Author:
// Franz Regensburger
// Ingolstadt University of Applied Sciences
// (C) 2011
//

#ifndef _WORM_H
#define _WORM_H

// Result codes of functions
enum ResCodes {
    RES_OK,
    RES_FAILED,
    RES_INTERNAL_ERROR,
};

// Dimensions and bounds
#define NAP_TIME    100   // Time in milliseconds to sleep between updates of display
#define WORM_LENGTH 20 // Maximal length of the worm
#define UNUSED_POS_ELEM -1
#define ROWS_RESERVED 4 // Lines reserved for the message area
#define MIN_NUMBER_OF_ROWS 3 // The guaranteed number of . . .
#define MIN_NUMBER_OF_COLS 70 // The guaranteed number of columns . . .

// Numbers for color pairs used by curses macro COLOR_PAIR
//#define COLP_USER_WORM 1
enum ColorPairs {
    COLP_USER_WORM = 1,
    COLP_FREE_CELL,
    COLP_BARRIER,
};

// Symbols to display
#define SYMBOL_FREE_CELL ' '
#define SYMBOL_BARRIER '#'
#define SYMBOL_WORM_INNER_ELEMENT '0'

// Game state codes
//#define  WORM_GAME_ONGOING  0
//#define  WORM_OUT_OF_BOUNDS 1   // Left screen
//#define  WORM_GAME_QUIT     2   // User likes to quit
// Game state codes
enum GameStates {
    WORM_GAME_ONGOING,
    WORM_OUT_OF_BOUNDS, // Left screen
    WORM_CROSSING, // Worm head crossed another worm element
    WORM_GAME_QUIT, // User likes to quit
};
#endif  // #define _WORM_H
