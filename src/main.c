#include <gb/gb.h>
#include "graphics.h"
#include "input.h"
#include "game.h"
#include "timer.h"
#include "tileset.h"

void main(void)
{
    CRITICAL
    {
        timer_init();
        graphics_init();
        input_init();
        game_init();
    }

    while (1)
    {
        vsync();

        // Timer
        timer_tick();

        // Input
        input_update(scene_current());

        // Scene
        scene_update();
    }
}
