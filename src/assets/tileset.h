#ifndef TILESET_H
#define TILESET_H

// Background map dimensions
#define MAP_WIDTH 20
#define MAP_HEIGHT 18

// Color palette definitions
#define PALETTE_WHITE 0
#define PALETTE_LIGHT_GRAY 1
#define PALETTE_DARK_GRAY 2
#define PALETTE_BLACK 3

// Tile definitions
#define TILE_COUNTER 5

#define TILE_EMPTY 0
#define TILE_SOLID 1
#define TILE_PATTERN 2
#define TILE_DIAGONAL 3
#define TILE_CIRCLE 4

// Sprite definitions
#define SPRITE_COUNTER 2

#define SPRITE_DOWN_ARROW 0
#define SPRITE_TOP_ARROW 0

extern const unsigned char tile_data[];
extern const unsigned char background_map[];
extern const unsigned char sprite_sheet_gameplay_data[];

#endif // TILESET_H
