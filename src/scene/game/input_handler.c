#include "input_handler.h"
#include "note_manager.h"
#include "graphics.h"
#include "tileset.h"

static const UINT8 key_masks[] = {
    [SPRITE_ID_DOWN_ARROW] = J_DOWN,
    [SPRITE_ID_UP_ARROW] = J_UP,
    [SPRITE_ID_RIGHT_ARROW] = J_RIGHT,
    [SPRITE_ID_LEFT_ARROW] = J_LEFT,
    [SPRITE_ID_A_BUTTON] = J_A,
    [SPRITE_ID_B_BUTTON] = J_B};

void input_handle_game_input(UINT8 keys, UINT8 keys_prev)
{
    (void)keys_prev;

    if (!keys)
        return;

    for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++)
    {
        if (game.notes[i].in_used)
        {
            const UBYTE key_mask = key_masks[game.notes[i].key];

            if (keys & key_mask)
            {
                game.score += NOTE_SCORE_VALUE;
                note_cleanup(i);
            }
        }
    }
}