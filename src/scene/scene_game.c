#include "gbdk/console.h"

#include "scene_game.h"
#include "scene_menu.h"

#include "input.h"
#include "graphics.h"
#include "game.h"

static void load()
{
    draw_background();
}

static void update(void)
{
    draw_player(game.player.x, game.player.y);
}

static void unload()
{
    clear_screen();
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
