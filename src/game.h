#ifndef GAME_H
#define GAME_H

#include <gb/gb.h>
#include <stdio.h>

#define MAX_SCORE 9999
#define MAX_LIVES 3

#define NOTE_MAX_AMOUNT 40
#define NOTE_DEFAULT_SPEED 1
#define NOTE_MAX_SPEED 1
#define NOTE_DEFAULT_TILE 0

typedef struct
{
    UBYTE in_used;
    UBYTE sprite_id;
    UBYTE move_speed;
    UBYTE posx;
    UBYTE posy;
    UBYTE key;
} note_t;

typedef struct
{
    note_t notes[NOTE_MAX_AMOUNT];
    UBYTE score;
    UBYTE lives;
} game_t;

void game_init(void);
void game_update_game(void);
void game_reset_note(UBYTE index);
UBYTE game_get_random_note_index(void);

extern game_t game;

#endif // GAME_H
