#include "game_logic.h"
#include "scene_menu.h"
#include "note_manager.h"
#include "timer.h"

#define SPAWN_INTERVAL_SECONDS 1

void game_check_game_over(void)
{
    if (game.lives <= 0)
    {
        scene_set(&scene_menu);
    }
}

void game_spawn_notes(void)
{
    static uint32_t last_spawn_time = 0;
    uint32_t current_time = timer_get_seconds();

    if (current_time - last_spawn_time >= SPAWN_INTERVAL_SECONDS)
    {
        UBYTE note_index = game_get_random_note_index();
        if (note_index < NOTE_MAX_AMOUNT)
        {
            note_initialize(note_index);
        }
        last_spawn_time = current_time;
    }
}