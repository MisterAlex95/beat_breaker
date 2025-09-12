#include "ui_manager.h"
#include "graphics.h"
#include "timer.h"
#include "tileset.h"
#include "ui.h"

void ui_draw_hud(void)
{
    if (game.lives <= 0)
        return;

    ui_draw_timer();
    ui_draw_score();
    ui_draw_lives();
}

void ui_draw_timer(void)
{
    char buf[32];
    sprintf(buf, "%d", timer_get_seconds());
    graphics_draw_text(SCREEN_TILE_WIDTH - 4, 1, buf);
}

void ui_draw_score(void)
{
    char buf[32];
    sprintf(buf, "%d", game.score);
    graphics_draw_text(6, 1, buf);
}

void ui_draw_lives(void)
{
    for (UBYTE i = 0; i < MAX_LIVES; i++)
    {
        const UINT8 tile_index = (i >= game.lives) ? SPRITE_VRAM_INDEX_EMPTY : SPRITE_VRAM_INDEX_HEART;
        set_bkg_tiles(1 + i, 1, 1, 1, &tile_index);
    }
}