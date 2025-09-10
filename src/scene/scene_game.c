#include "gbdk/console.h"

#include "scene_game.h"
#include "scene_menu.h"

#include "tileset.h"

#include "input.h"
#include "graphics.h"
#include "game.h"

static void load()
{
    graphics_load_tiles(tile_data, TILE_COUNTER, 0);
    graphics_create_sprite(sprite_sheet_gameplay_data, 0, 10, 10);
}

static void update(void)
{
    graphics_move_sprite(game.player.sprite_id, game.player.x, game.player.y);
}

static void unload()
{
    graphics_clear();
}

static void handle_input(UINT8 keys, UINT8 keys_prev)
{
    if ((keys & J_UP) && game.player.y > 0)
    {
        game.player.y--;
        game.player.direction = 0;
    }
    else if ((keys & J_RIGHT))
    {
        game.player.x++;
        game.player.direction = 1;
    }
    else if ((keys & J_DOWN))
    {
        game.player.y++;
        game.player.direction = 2;
    }
    else if ((keys & J_LEFT) && game.player.x > 0)
    {
        game.player.x--;
        game.player.direction = 3;
    }

    if (keys & J_A)
    {
        // nothing
    }

    if (keys & J_B)
    {
        // nothing
    }

    if (keys & J_START)
    {
        // nothing
    }

    if (keys & J_SELECT)
    {
        // nothing
    }
}

Scene scene_game = {
    load,
    update,
    unload,
    handle_input};
