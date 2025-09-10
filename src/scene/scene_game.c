#include <gb/gb.h>
#include "scene_game.h"
#include "scene_menu.h"
#include "timer.h"
#include "graphics.h"
#include "tileset.h"
#include "ui.h"
#include "game.h"
#include "math.h"

#define MAX_SPRITES 40

static void load(void)
{
    graphics_load_tiles(backgroundTiles, SPRITE_VRAM_INDEX_TOTAL, 0);
    graphics_draw_background(backgroundMap, MAP_WIDTH, MAP_HEIGHT);

    graphics_load_sprite(sprite_down_arrow_data, SPRITE_VRAM_INDEX_DOWN_ARROW);
    graphics_load_sprite(sprite_up_arrow_data, SPRITE_VRAM_INDEX_UP_ARROW);
    graphics_load_sprite(sprite_right_arrow_data, SPRITE_VRAM_INDEX_RIGHT_ARROW);
    graphics_load_sprite(sprite_left_arrow_data, SPRITE_VRAM_INDEX_LEFT_ARROW);
    graphics_load_sprite(sprite_a_data, SPRITE_VRAM_INDEX_A);
    graphics_load_sprite(sprite_b_data, SPRITE_VRAM_INDEX_B);

    for (UINT8 i = 0; i < MAX_SPRITES; i++)
    {
        graphics_hide_sprite(i);
    }
}

static void update(void)
{
    static uint32_t last_spawn_time = 0;
    uint32_t current_time = timer_get_seconds();

    if (current_time - last_spawn_time >= 1)
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

    check_game_over();
}

static void unload(void)
{
    graphics_clear();
    timer_reset();
    game_init();
    for (UINT8 i = 0; i < MAX_SPRITES; i++)
    {
        graphics_hide_sprite(i);
    }
}

void apply_falling_effect(void)
{
    for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++)
    {
        if (game.notes[i].in_used)
        {
            game.notes[i].posy += game.notes[i].move_speed;

            if (game.notes[i].posy > TILE_SIZE * SCREEN_TILE_HEIGHT - 2 * TILE_SIZE)
            {
                // lose a life
                game.lives--;
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
    }
}

void initialize_note(UBYTE index)
{
    game.notes[index].in_used = 1;
    game.notes[index].posx = random_between(TILE_SIZE * 2, TILE_SIZE * SCREEN_TILE_WIDTH - 16);
    game.notes[index].posy = 5 * TILE_SIZE; // start below the UI

    game.notes[index].sprite_id = index;

    // assign random sprite type
    UBYTE sprite_type = random_between(0, 5);

    game.notes[index].key = sprite_type;
    graphics_assign_sprite(sprite_type, game.notes[index].sprite_id);
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

    // display timer
    char buf[32];
    sprintf(buf, "%d", timer_get_seconds());
    graphics_draw_text(SCREEN_TILE_WIDTH - 4, 1, buf);

    // display score
    sprintf(buf, "%d", game.score);
    graphics_draw_text(6, 1, buf);

    // display an heart for each life
    if (game.lives < 0)
        return;

    for (UBYTE i = 0; i < MAX_LIVES; i++)
    {
        UINT8 tile_index;
        if (i >= game.lives)
            tile_index = SPRITE_VRAM_INDEX_EMPTY;
        else
            tile_index = SPRITE_VRAM_INDEX_HEART;

        set_bkg_tiles(1 + i, 1, 1, 1, &tile_index);
    }
}

static void handle_input(UINT8 keys, UINT8 keys_prev)
{
    for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++)
    {
        if (game.notes[i].in_used)
        {
            // Check for corresponding key press
            if ((game.notes[i].key == SPRITE_ID_DOWN_ARROW && (keys & J_DOWN)) ||   // Down arrow
                (game.notes[i].key == SPRITE_ID_UP_ARROW && (keys & J_UP)) ||       // Up arrow
                (game.notes[i].key == SPRITE_ID_RIGHT_ARROW && (keys & J_RIGHT)) || // Right arrow
                (game.notes[i].key == SPRITE_ID_LEFT_ARROW && (keys & J_LEFT)) ||   // Left arrow
                (game.notes[i].key == SPRITE_ID_A_BUTTON && (keys & J_A)) ||        // A button
                (game.notes[i].key == SPRITE_ID_B_BUTTON && (keys & J_B)))          // B button
            {
                // Successful hit
                game.score += 10; // Increase score
                game.notes[i].in_used = 0;
                graphics_hide_sprite(game.notes[i].sprite_id);
            }
        }
    }
}

void check_game_over(void)
{
    if (game.lives <= 0)
    {
        // Temporaryly switch to menu scene
        scene_set(&scene_menu);
    }
}

Scene scene_game = {
    load,
    update,
    unload,
    handle_input};
