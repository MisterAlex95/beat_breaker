#ifndef TILESET_H
#define TILESET_H

#define MAP_WIDTH 20
#define MAP_HEIGHT 18
#define TILE_SIZE 8

#define SPRITE_BASE_INDEX 9
#define SPRITE_VRAM_INDEX_DOWN_ARROW (SPRITE_BASE_INDEX + 0)
#define SPRITE_VRAM_INDEX_UP_ARROW (SPRITE_BASE_INDEX + 1)
#define SPRITE_VRAM_INDEX_RIGHT_ARROW (SPRITE_BASE_INDEX + 2)
#define SPRITE_VRAM_INDEX_LEFT_ARROW (SPRITE_BASE_INDEX + 3)
#define SPRITE_VRAM_INDEX_A (SPRITE_BASE_INDEX + 4)
#define SPRITE_VRAM_INDEX_B (SPRITE_BASE_INDEX + 5)

#define SPRITE_ID_DOWN_ARROW (SPRITE_BASE_INDEX + 0)
#define SPRITE_ID_UP_ARROW (SPRITE_BASE_INDEX + 1)
#define SPRITE_ID_RIGHT_ARROW (SPRITE_BASE_INDEX + 2)
#define SPRITE_ID_LEFT_ARROW (SPRITE_BASE_INDEX + 3)
#define SPRITE_ID_A_BUTTON (SPRITE_BASE_INDEX + 4)
#define SPRITE_ID_B_BUTTON (SPRITE_BASE_INDEX + 5)

#define SPRITE_VRAM_INDEX_HIDE_KEY 0
#define SPRITE_ID_HIDE_KEY 0
#define SPRITE_HIDE_KEY_WIDTH 8

extern const unsigned char sprite_up_arrow_data[];
extern const unsigned char sprite_down_arrow_data[];
extern const unsigned char sprite_right_arrow_data[];
extern const unsigned char sprite_left_arrow_data[];
extern const unsigned char sprite_a_data[];
extern const unsigned char sprite_b_data[];
extern unsigned char sprite_hide_key_data[];

#endif // TILESET_H
