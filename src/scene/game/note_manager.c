#include "note_manager.h"
#include "tileset.h"
#include "timer.h"
#include "math.h"

#define MALUS_ANIMATION_FRAME_DURATION 8
#define NOTE_SPAWN_Y_POSITION (5 * TILE_SIZE)
#define NOTE_SPAWN_X_MARGIN (TILE_SIZE * 2)
#define NOTE_SPAWN_X_MAX (TILE_SIZE * SCREEN_TILE_WIDTH - 16)

void note_apply_falling_effect(void)
{
    const UINT16 screen_bottom = TILE_SIZE * SCREEN_TILE_HEIGHT - 2 * TILE_SIZE;

    for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++)
    {
        if (game.notes[i].in_used)
        {
            game.notes[i].posy += game.notes[i].move_speed;

            if (game.notes[i].has_malus)
            {
                graphics_move_sprite(game.notes[i].malus_sprite_id, game.notes[i].posx,
                                     game.notes[i].posy);
            }

            if (game.notes[i].posy > screen_bottom)
            {
                game.lives--;
                note_cleanup(i);
            }
        }
    }
}

void note_display_notes(void)
{
    for (UBYTE i = 0; i < NOTE_MAX_AMOUNT && i < MAX_SPRITES; i++)
    {
        if (game.notes[i].in_used)
        {
            graphics_move_sprite(game.notes[i].sprite_id, game.notes[i].posx,
                                 game.notes[i].posy);
        }
    }
}

void note_display_malus(void)
{
    const uint32_t current_tick = timer_get_ticks();
    const UINT8 max_frame_index = SPRITE_HIDE_KEY_WIDTH - 1;

    for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++)
    {
        if (game.notes[i].in_used && game.notes[i].has_malus)
        {
            uint32_t elapsed = current_tick - game.notes[i].malus_start_tick;
            UINT8 frame_index = elapsed / MALUS_ANIMATION_FRAME_DURATION;

            if (frame_index >= SPRITE_HIDE_KEY_WIDTH)
            {
                frame_index = max_frame_index;
                graphics_hide_sprite(game.notes[i].malus_sprite_id);
            }

            graphics_assign_sprite(game.notes[i].malus_sprite_id,
                                   SPRITE_VRAM_INDEX_HIDE_KEY + frame_index);
        }
    }
}

void note_initialize(UBYTE index)
{
    game.notes[index].in_used = 1;
    game.notes[index].posx = random_between(NOTE_SPAWN_X_MARGIN, NOTE_SPAWN_X_MAX);
    game.notes[index].posy = NOTE_SPAWN_Y_POSITION;

    game.notes[index].sprite_id = index;
    UBYTE sprite_type = random_between(SPRITE_ID_DOWN_ARROW, SPRITE_ID_B_BUTTON);
    game.notes[index].key = sprite_type;
    game.notes[index].move_speed = random_between(NOTE_DEFAULT_SPEED, NOTE_MAX_SPEED);

    graphics_assign_sprite(game.notes[index].sprite_id, sprite_type);
    graphics_move_sprite(game.notes[index].sprite_id, game.notes[index].posx,
                         game.notes[index].posy);

    if (random_between(0, 100) < MALUS_SPAWN_CHANCE)
    {
        game.notes[index].has_malus = 1;
        game.notes[index].malus_sprite_id = index + MALUS_SPRITE_OFFSET;

        graphics_assign_sprite(game.notes[index].malus_sprite_id,
                               SPRITE_VRAM_INDEX_HIDE_KEY);
        graphics_move_sprite(game.notes[index].malus_sprite_id,
                             game.notes[index].posx, game.notes[index].posy);

        game.notes[index].malus_start_tick = timer_get_ticks();
    }
    else
    {
        game.notes[index].has_malus = 0;
    }
}

void note_cleanup(UBYTE index)
{
    game.notes[index].in_used = 0;
    graphics_hide_sprite(game.notes[index].sprite_id);
    if (game.notes[index].has_malus)
    {
        graphics_hide_sprite(game.notes[index].malus_sprite_id);
    }
}