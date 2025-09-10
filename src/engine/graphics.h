#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <gb/gb.h>

#define SCREEN_TILE_WIDTH 20
#define SCREEN_TILE_HEIGHT 18
#define TILE_SIZE 8

void graphics_init(void);
void graphics_clear(void);

void graphics_load_tiles(const unsigned char *tiles, UINT16 tile_count, UINT8 vram_index);
void graphics_draw_background(const unsigned char *map, UINT8 width, UINT8 height);

void graphics_load_sprite(const unsigned char *sprite_data, UINT8 vram_tile_index);
void graphics_assign_sprite(UINT8 vram_tile_index, UINT8 sprite_id);
void graphics_move_sprite(UINT8 sprite_id, UINT8 x, UINT8 y);
void graphics_hide_sprite(UINT8 sprite_id);

void graphics_draw_text(UINT8 x, UINT8 y, const char *text);

#endif // GRAPHICS_H
