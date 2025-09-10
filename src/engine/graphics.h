#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <gb/gb.h>
#include <stdio.h>

// Screen dimensions
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define TILE_SIZE 8

// Initialization
void init_graphics(void);
void init_main_menu_graphics(void);
void init_game_graphics(void);

void draw_background(void);
void load_tiles(void);
void clear_screen(void);

void draw_player(UBYTE x, UBYTE y);

#endif // GRAPHICS_H
