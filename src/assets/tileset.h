#ifndef TILESET_H
#define TILESET_H

// Background map dimensions
#define MAP_WIDTH 20
#define MAP_HEIGHT 18

// Sprite definitions
#define SPRITE_VRAM_INDEX_DOWN_ARROW 0
#define SPRITE_VRAM_INDEX_TOP_ARROW 1

#define SPRITE_ID_DOWN_ARROW 0
#define SPRITE_ID_TOP_ARROW 1

extern const unsigned char sprite_top_arrow_data[];
extern const unsigned char sprite_down_arrow_data[];

#endif // TILESET_H
