#include "game.h"
#include "scene.h"
#include "input.h"
#include "graphics.h"
#include "scene/scene_menu.h"

game_t game;

void game_init(void)
{
    // Initialize game state
    game.score = 0;
    game.lives = MAX_LIVES;

    for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++)
    {
        game_reset_note(i);
    }
}

UBYTE game_get_random_note_index(void)
{
    for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++)
    {
        if (game.notes[i].in_used == 0)
        {
            return i;
        }
    }

    return 255;
}

void game_reset_note(UBYTE index)
{
    if (index > NOTE_MAX_AMOUNT)
    {
        return;
    }

    game.notes[index].in_used = 0;
    game.notes[index].sprite_id = NOTE_DEFAULT_TILE;
    game.notes[index].move_speed = NOTE_DEFAULT_SPEED;
    game.notes[index].posx = 0;
    game.notes[index].posy = 0;
}

void game_update_game(void)
{
    scene_update();
}
