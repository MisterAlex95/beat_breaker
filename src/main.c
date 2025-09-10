#include <gb/gb.h>
#include "graphics.h"
#include "input.h"
#include "game.h"

void main(void)
{
    CRITICAL
    {
        init_graphics();
        input_init();
        init_game();
    }

    while (1)
    {
        vsync();
        input_update(scene_current());
        scene_update();
    }
}
