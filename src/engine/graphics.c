#include <gbdk/console.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "graphics.h"

void graphics_init(void)
{
    DISPLAY_OFF;
    SPRITES_8x8;
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}

void graphics_clear(void)
{
    static const UINT8 blank[SCREEN_TILE_WIDTH * SCREEN_TILE_HEIGHT] = {0};
    set_bkg_tiles(0, 0, SCREEN_TILE_WIDTH, SCREEN_TILE_HEIGHT, blank);
}

void graphics_load_tiles(const unsigned char *tiles, UINT16 tile_count, UINT8 vram_index)
{
    set_bkg_data(vram_index, tile_count, tiles);
}

void graphics_draw_background(const unsigned char *map, UINT8 width, UINT8 height)
{
    set_bkg_tiles(0, 0, width, height, map);
}

void graphics_load_sprite(const unsigned char *sprite_data, UINT8 vram_tile_index)
{
    set_sprite_data(vram_tile_index, 1, sprite_data);
}

void graphics_assign_sprite(UINT8 vram_tile_index, UINT8 sprite_id)
{
    set_sprite_tile(sprite_id, vram_tile_index);
}

void graphics_move_sprite(UINT8 sprite_id, UINT8 x, UINT8 y)
{
    move_sprite(sprite_id, x, y);
}

void graphics_hide_sprite(UINT8 sprite_id)
{
    move_sprite(sprite_id, 255U, 255U);
}

void graphics_draw_text(UINT8 x, UINT8 y, const char *text)
{
    gotoxy(x, y);
    printf("%s", text);
}