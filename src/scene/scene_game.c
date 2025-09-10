#include <gb/gb.h>
#include "scene_game.h"
#include "timer.h"
#include "graphics.h"
#include "tileset.h"
#include "game.h"

#define MAX_SPRITES 40

static void load(void)
{
    graphics_load_sprite(sprite_down_arrow_data, SPRITE_VRAM_INDEX_DOWN_ARROW);
    graphics_load_sprite(sprite_top_arrow_data, SPRITE_VRAM_INDEX_TOP_ARROW);

    for (UINT8 i = 0; i < MAX_SPRITES; i++)
    {
        graphics_hide_sprite(i);
    }
}

static void update(void)
{
    static uint32_t last_spawn_time = 0;
    uint32_t current_time = timer_get_seconds();

    if (current_time - last_spawn_time >= 3)
    {
        UBYTE note_index = game_get_random_note_index();
        if (note_index < NOTE_MAX_AMOUNT)
        {
            initialize_note(note_index);
        }

        last_spawn_time = current_time;
    }

    apply_falling_effect();
    display_notes();
    draw_hud();
}

static void unload(void)
{
    graphics_clear();
}

void apply_falling_effect(void)
{
    for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++)
    {
        if (game.notes[i].in_used)
        {
            game.notes[i].posy += game.notes[i].move_speed;

            if (game.notes[i].posy > 144)
            {
                game.notes[i].in_used = 0;
                graphics_hide_sprite(game.notes[i].sprite_id);
            }
        }
    }
}

void display_notes(void)
{
    for (UBYTE i = 0; i < NOTE_MAX_AMOUNT && i < MAX_SPRITES; i++)
    {
        if (game.notes[i].in_used == 1)
        {
            graphics_move_sprite(game.notes[i].sprite_id, game.notes[i].posx, game.notes[i].posy);
        }
        else
        {
            graphics_hide_sprite(game.notes[i].sprite_id);
        }
    }
}

void initialize_note(UBYTE index)
{
    game.notes[index].in_used = 1;
    game.notes[index].posx = 5;
    game.notes[index].posy = 0;

    game.notes[index].sprite_id = index;

    graphics_assign_sprite(SPRITE_VRAM_INDEX_DOWN_ARROW, game.notes[index].sprite_id);
    graphics_move_sprite(game.notes[index].sprite_id, game.notes[index].posx, game.notes[index].posy);
}

void draw_hud(void)
{
    UBYTE nbr_of_notes = 0;
    for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++)
    {
        if (game.notes[i].in_used)
            nbr_of_notes++;
    }

    char buf[32];
    sprintf(buf, "Notes: %d Time: %d", nbr_of_notes, timer_get_seconds());
    graphics_draw_text(0, 0, buf);
}

static void handle_input(UINT8 keys, UINT8 keys_prev)
{
    if (keys & J_UP)
    {
    }
    if (keys & J_DOWN)
    {
    }
    if (keys & J_LEFT)
    {
    }
    if (keys & J_RIGHT)
    {
    }

    if (keys & J_A)
    {
    }
    if (keys & J_B)
    {
    }
    if (keys & J_START)
    {
    }
    if (keys & J_SELECT)
    {
    }
}

Scene scene_game = {
    load,
    update,
    unload,
    handle_input};
