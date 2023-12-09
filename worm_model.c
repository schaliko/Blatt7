// A simple variant of the game Snake
//
// Used for teaching in classes
//
// Author:
// Franz Regensburger
// Ingolstadt University of Applied Sciences
// (C) 2011
//
// The worm model

#include <curses.h>
#include "worm.h"
#include "board_model.h"
#include "worm_model.h"

enum ColorPairs theworm_wcolor; 

// Initialize the worm
enum ResCodes initializeWorm(struct worm* aworm, int len_max, struct pos headpos, enum WormHeading dir, enum ColorPairs color) {
    int i;
    // Initialize last usable index to len_max -1
    aworm->maxindex = len_max - 1 ;

	// Initialize headindex
    aworm->headindex = 0; // Index pointing to head position is set to 0
    // Mark all elements as unused in the array of positions.
    // This allows for the effect that the worm appears element by element at
    // the start of each level    
    for (i = 0; i <= aworm->maxindex; i++) {
        aworm->wormpos[i].y = UNUSED_POS_ELEM;
        aworm->wormpos[i].x = UNUSED_POS_ELEM;
    }

    // Initialize position of worms head
    aworm->wormpos[aworm->headindex] = headpos;
    // Initialize the heading of the worm
    setWormHeading(aworm, dir);
    // Initialze color of the worm
    aworm->wcolor = color;
    return RES_OK;
}

// Show the worms's elements on the display
// Simple version
void showWorm(struct worm* aworm) {
    // Due to our encoding we just need to show the head element
    // All other elements are already displayed
    placeItem(
            aworm->wormpos[aworm->headindex].y,
            aworm->wormpos[aworm->headindex].x,
            SYMBOL_WORM_INNER_ELEMENT,
            aworm->wcolor);
}

void cleanWormTail(struct worm* aworm) {
    int tailindex;
    // Compute tailindex
    tailindex = (aworm->headindex + 1) % (aworm->maxindex + 1);
    // Check the array of worm elements.
    // Is the array element at tailindex already in use?
    // Checking either array theworm_wormpos_y
    // or theworm_wormpos_x is enough.
    if (aworm->wormpos[tailindex].y != UNUSED_POS_ELEM) {
        // YES: place a SYMBOL_FREE_CELL at the tail's position
        placeItem(aworm->wormpos[tailindex].y, aworm->wormpos[tailindex].x,
	    SYMBOL_FREE_CELL, COLP_FREE_CELL);
    }
}

void moveWorm(struct worm* aworm, enum GameStates* agame_state) {
    int headpos_y, headpos_x;
    // Get the current position of the worm's head element and
    // compute the new head position according to current heading.
    // Do not store the new head position in the array of positions, yet.
	headpos_y = aworm->wormpos[aworm->headindex].y + aworm->dy;
	headpos_x = aworm->wormpos[aworm->headindex].x + aworm->dx;

    // Check if we would leave the display if we move the worm's head according
    // to worm's last direction.
    // We are not allowed to leave the display's window.
    if (headpos_x < 0) {
        *agame_state = WORM_OUT_OF_BOUNDS;
        //endwin();
    } else if (headpos_x > getLastCol() ) { 
        *agame_state = WORM_OUT_OF_BOUNDS;
        //endwin();
    } else if (headpos_y < 0) {  
        *agame_state = WORM_OUT_OF_BOUNDS;
        //endwin();
    } else if (headpos_y > getLastRow() ) {
        *agame_state = WORM_OUT_OF_BOUNDS;
        //endwin();
    } 
    else {
        struct pos new_pos;
        new_pos.x = headpos_x;
        new_pos.y = headpos_y;
        //We will stay within bounds.
        //Check if the worm's head will collide with itself at the new position
        if (isInUseByWorm(aworm, new_pos)) {
            // That's bad: stop game
            *agame_state = WORM_CROSSING;
        }
    }

    // Check the status of *agame_state
    // Go on if nothing bad happened
    if ( *agame_state == WORM_GAME_ONGOING ) {
        // So all is well: we did not hit anything bad and did not leave the
        // window. --> Update the worm structure.
        // Increment theworm_headindex
        // Go round if end of worm is reached (ring buffer)
        aworm->headindex = (aworm->headindex + 1) % (aworm->maxindex + 1);
		aworm->wormpos[aworm->headindex].y = headpos_y;
		aworm->wormpos[aworm->headindex].x = headpos_x;
    }
}

// A simple collision detection
bool isInUseByWorm(struct worm* aworm, struct pos new_headpos) {
    int i;
    bool collision = false;
    i = aworm->headindex;
    do {// Compare the position of the current worm element with the new_headpos
        if (aworm->wormpos[i].y == new_headpos.y && 
            aworm->wormpos[i].x == new_headpos.x) {
			// found!
			collision = true;
			break;
		}
		i = (i + 1) % (aworm->maxindex + 1);
    } while ( i != aworm->headindex && aworm->wormpos[i].x != UNUSED_POS_ELEM);
    // Return what we found out.
    return collision;
}

// Setters
void setWormHeading(struct worm* aworm, enum WormHeading dir) {
    switch(dir) {
        case WORM_UP :// User wants up
            aworm->dx=0;
            aworm->dy=-1;
            break;
        case WORM_DOWN :// User wants down
            aworm->dx=0;
            aworm->dy=+1;
            break;
        case WORM_LEFT      :// User wants left
            aworm->dx=-1;
            aworm->dy=0;
            break;
        case WORM_RIGHT      :// User wants right
            aworm->dx=+1;
            aworm->dy=0;
            break;
    }
} 

struct pos getWormHeadPos(struct worm* aworm) {
    // Structures are passed by value!
    // -> we return a copy here
    return aworm->wormpos[aworm->headindex];
}
