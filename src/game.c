#include "game.h"
#include "scene.h"
#include "input.h"
#include "graphics.h"
#include "scene/scene_menu.h"

game_t game;

void init_game(void)
{
    // Initialize game state
    game.state = GAME_STATE_MENU;
    game.score = 0;
    game.lives = 3;

    // Initialize player position (center of screen for testing)
    game.player.x = 10;        // Center horizontally
    game.player.y = 9;         // Center vertically
    game.player.sprite_id = 4; // Use tile 5 (player sprite)
    game.player.direction = 2; // Start facing down
    game.player.moving = 0;
    game.player.move_timer = 0;
    game.player.move_speed = 8; // Not used in simple movement

    scene_set(&scene_menu);
}

void update_game(void)
{
    input_update(scene_current());
    scene_update();
}
