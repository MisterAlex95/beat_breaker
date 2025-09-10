#ifndef GAME_H
#define GAME_H

#include <gb/gb.h>
#include <stdio.h>

#define MAX_SCORE 9999
#define MAX_LIVES 9
#define PLAYER_START_X 10
#define PLAYER_START_Y 8

typedef struct
{
    UBYTE x;
    UBYTE y;
    UBYTE sprite_id;
    UBYTE direction;  // 0=up, 1=right, 2=down, 3=left
    UBYTE moving;     // 1 if currently moving, 0 if stationary
    UBYTE move_timer; // Timer for smooth movement
    UBYTE move_speed; // Movement speed (frames per tile)
} player_t;

typedef struct
{
    player_t player;
    UBYTE score;
    UBYTE lives;
} game_t;

void init_game(void);
void update_game(void);

extern game_t game;

#endif // GAME_H
