#ifndef NOTE_MANAGER_H
#define NOTE_MANAGER_H

#include <gb/gb.h>
#include "game.h"
#include "graphics.h"

void note_apply_falling_effect(void);
void note_display_notes(void);
void note_display_malus(void);
void note_initialize(UBYTE index);
void note_cleanup(UBYTE index);

#endif // NOTE_MANAGER_H