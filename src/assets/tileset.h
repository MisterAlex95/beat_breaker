#ifndef TILESET_H
#define TILESET_H

// Background map dimensions
#define MAP_WIDTH 20
#define MAP_HEIGHT 18
#define TILE_SIZE 8

// Sprite definitions
#define SPRITE_VRAM_INDEX_DOWN_ARROW 0
#define SPRITE_VRAM_INDEX_UP_ARROW 1
#define SPRITE_VRAM_INDEX_RIGHT_ARROW 2
#define SPRITE_VRAM_INDEX_LEFT_ARROW 3
#define SPRITE_VRAM_INDEX_A 4
#define SPRITE_VRAM_INDEX_B 5

#define SPRITE_ID_DOWN_ARROW 0
#define SPRITE_ID_UP_ARROW 1
#define SPRITE_ID_RIGHT_ARROW 2
#define SPRITE_ID_LEFT_ARROW 3
#define SPRITE_ID_A_BUTTON 4
#define SPRITE_ID_B_BUTTON 5

extern const unsigned char sprite_up_arrow_data[];
extern const unsigned char sprite_down_arrow_data[];
extern const unsigned char sprite_right_arrow_data[];
extern const unsigned char sprite_left_arrow_data[];
extern const unsigned char sprite_a_data[];
extern const unsigned char sprite_b_data[];

#endif // TILESET_H
