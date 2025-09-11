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
#define NOTE_SCORE_VALUE 10

#define MAX_SIMULTANEOUS_MALUS 3
#define MALUS_SPAWN_CHANCE 20
#define MALUS_SPRITE_OFFSET 9

typedef struct
{
    UBYTE in_used : 1;
    UBYTE has_malus : 1;
    UBYTE sprite_id;
    UBYTE malus_sprite_id;
    UBYTE move_speed;
    UBYTE key;

    UINT16 posx;
    UINT16 posy;

    uint32_t spawn_tick;
    uint32_t malus_start_tick;
} note_t;

typedef struct
{
    note_t notes[NOTE_MAX_AMOUNT];
    uint16_t score;
    UBYTE lives;
} game_t;

void game_init(void);
void game_update_game(void);
void game_reset_note(UBYTE index);
UBYTE game_get_random_note_index(void);

extern game_t game;

#endif // GAME_H
