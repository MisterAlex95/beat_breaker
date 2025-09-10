#include "graphics.h"
#include "tileset.h"

void init_graphics(void)
{
    // Turn off display during setup
    LCDC_REG = 0x00;

    // Load tile data into VRAM
    SPRITES_8x8;
    load_tiles();

    // Turn on display
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;
}

void init_main_menu_graphics(void)
{
    // Nothing to do yet
}

void init_game_graphics(void)
{
    draw_background();
}

void load_tiles(void)
{
    set_bkg_data(0, TILE_COUNTER, tile_data);
    set_sprite_data(0, TILE_COUNTER, tile_data);
    set_sprite_tile(0, TILE_CIRCLE);
}

void draw_background(void)
{
    set_bkg_tiles(0, 0, MAP_WIDTH, MAP_HEIGHT, background_map);
}

void clear_screen(void)
{
    fill_bkg_rect(0, 0, MAP_WIDTH, MAP_HEIGHT, TILE_EMPTY);
}

void draw_player(UBYTE x, UBYTE y)
{
    move_sprite(0, x, y);
}
