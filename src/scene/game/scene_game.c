#include "scene_game.h"
#include "game.h"
#include "graphics.h"
#include "tileset.h"
#include "ui.h"
#include "timer.h"
#include "note_manager.h"
#include "input_handler.h"
#include "ui_manager.h"
#include "game_logic.h"
#include "scene_menu.h"
#include <gb/gb.h>

static void load(void)
{
  // Load background tiles and map
  graphics_load_tiles(backgroundTiles, SPRITE_VRAM_INDEX_TOTAL, 0);
  graphics_draw_background(backgroundMap, MAP_WIDTH, MAP_HEIGHT);

  // Load note sprites
  graphics_load_sprite(sprite_down_arrow_data, SPRITE_VRAM_INDEX_DOWN_ARROW);
  graphics_load_sprite(sprite_up_arrow_data, SPRITE_VRAM_INDEX_UP_ARROW);
  graphics_load_sprite(sprite_right_arrow_data, SPRITE_VRAM_INDEX_RIGHT_ARROW);
  graphics_load_sprite(sprite_left_arrow_data, SPRITE_VRAM_INDEX_LEFT_ARROW);
  graphics_load_sprite(sprite_a_data, SPRITE_VRAM_INDEX_A);
  graphics_load_sprite(sprite_b_data, SPRITE_VRAM_INDEX_B);

  // Load malus animation sprites
  graphics_load_sprites(sprite_hide_key_data, SPRITE_VRAM_INDEX_HIDE_KEY,
                        SPRITE_HIDE_KEY_WIDTH);

  // Initialize sprites
  graphics_hide_all_sprites();
}

static void update(void)
{
  game_spawn_notes();
  note_apply_falling_effect();
  note_display_notes();
  note_display_malus();
  ui_draw_hud();
  game_check_game_over();
}

static void unload(void)
{
  graphics_clear();
  timer_reset();
  game_init();
  graphics_hide_all_sprites();
}

static void handle_input(UINT8 keys, UINT8 keys_prev)
{
  input_handle_game_input(keys, keys_prev);
}

Scene scene_game = {load, update, unload, handle_input};