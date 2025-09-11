#include "scene_game.h"
#include "game.h"
#include "graphics.h"
#include "math.h"
#include "scene_menu.h"
#include "tileset.h"
#include "timer.h"
#include "ui.h"
#include <gb/gb.h>


static const UINT8 key_masks[] = {
    [SPRITE_ID_DOWN_ARROW] = J_DOWN,
    [SPRITE_ID_UP_ARROW] = J_UP,
    [SPRITE_ID_RIGHT_ARROW] = J_RIGHT,
    [SPRITE_ID_LEFT_ARROW] = J_LEFT,
    [SPRITE_ID_A_BUTTON] = J_A,
    [SPRITE_ID_B_BUTTON] = J_B
};

static void load(void) {
  graphics_load_tiles(backgroundTiles, SPRITE_VRAM_INDEX_TOTAL, 0);
  graphics_draw_background(backgroundMap, MAP_WIDTH, MAP_HEIGHT);

  graphics_load_sprite(sprite_down_arrow_data, SPRITE_VRAM_INDEX_DOWN_ARROW);
  graphics_load_sprite(sprite_up_arrow_data, SPRITE_VRAM_INDEX_UP_ARROW);
  graphics_load_sprite(sprite_right_arrow_data, SPRITE_VRAM_INDEX_RIGHT_ARROW);
  graphics_load_sprite(sprite_left_arrow_data, SPRITE_VRAM_INDEX_LEFT_ARROW);
  graphics_load_sprite(sprite_a_data, SPRITE_VRAM_INDEX_A);
  graphics_load_sprite(sprite_b_data, SPRITE_VRAM_INDEX_B);

  graphics_load_sprites(sprite_hide_key_data, SPRITE_VRAM_INDEX_HIDE_KEY,
                        SPRITE_HIDE_KEY_WIDTH);

  graphics_hide_all_sprites();
}

static void update(void) {
  static uint32_t last_spawn_time = 0;
  uint32_t current_time = timer_get_seconds();

  if (current_time - last_spawn_time >= 1) {
    UBYTE note_index = game_get_random_note_index();
    if (note_index < NOTE_MAX_AMOUNT) {
      initialize_note(note_index);
    }

    last_spawn_time = current_time;
  }

  apply_falling_effect();

  display_notes();
  display_malus();

  draw_hud();

  check_game_over();
}

static void unload(void) {
  graphics_clear();
  timer_reset();
  game_init();
  graphics_hide_all_sprites();
}

void apply_falling_effect(void) {
  const UINT16 screen_bottom = TILE_SIZE * SCREEN_TILE_HEIGHT - 2 * TILE_SIZE;
  
  for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++) {
    if (game.notes[i].in_used) {
      game.notes[i].posy += game.notes[i].move_speed;

      if (game.notes[i].has_malus) {
        graphics_move_sprite(game.notes[i].malus_sprite_id, game.notes[i].posx,
                             game.notes[i].posy);
      }

      if (game.notes[i].posy > screen_bottom) {
        game.lives--;
        game.notes[i].in_used = 0;
        graphics_hide_sprite(game.notes[i].sprite_id);
        if (game.notes[i].has_malus) {
          graphics_hide_sprite(game.notes[i].malus_sprite_id);
        }
      }
    }
  }
}

void display_notes(void) {
  for (UBYTE i = 0; i < NOTE_MAX_AMOUNT && i < MAX_SPRITES; i++) {
    if (game.notes[i].in_used == 1) {
      graphics_move_sprite(game.notes[i].sprite_id, game.notes[i].posx,
                           game.notes[i].posy);
    }
  }
}

void display_malus(void) {
  const uint32_t current_tick = timer_get_ticks();
  const UINT8 max_frame_index = SPRITE_HIDE_KEY_WIDTH - 1;

  for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++) {
    if (game.notes[i].in_used && game.notes[i].has_malus) {
      uint32_t elapsed = current_tick - game.notes[i].malus_start_tick;
      UINT8 frame_index = elapsed / 8;

      if (frame_index >= SPRITE_HIDE_KEY_WIDTH) {
        frame_index = max_frame_index;
        graphics_hide_sprite(game.notes[i].malus_sprite_id);
      }

      graphics_assign_sprite(game.notes[i].malus_sprite_id, 
                            SPRITE_VRAM_INDEX_HIDE_KEY + frame_index);
    }
  }
}

void initialize_note(UBYTE index) {
  game.notes[index].in_used = 1;
  game.notes[index].posx =
      random_between(TILE_SIZE * 2, TILE_SIZE * SCREEN_TILE_WIDTH - 16);
  game.notes[index].posy = 5 * TILE_SIZE;

  game.notes[index].sprite_id = index;
  UBYTE sprite_type = random_between(SPRITE_ID_DOWN_ARROW, SPRITE_ID_B_BUTTON);
  game.notes[index].key = sprite_type;
  game.notes[index].move_speed =
      random_between(NOTE_DEFAULT_SPEED, NOTE_MAX_SPEED);

  graphics_assign_sprite(game.notes[index].sprite_id, sprite_type);
  graphics_move_sprite(game.notes[index].sprite_id, game.notes[index].posx,
                       game.notes[index].posy);

  if (random_between(0, 100) < MALUS_SPAWN_CHANCE) {
    game.notes[index].has_malus = 1;
    game.notes[index].malus_sprite_id = index + MALUS_SPRITE_OFFSET;

    graphics_assign_sprite(game.notes[index].malus_sprite_id,
                           SPRITE_VRAM_INDEX_HIDE_KEY);
    graphics_move_sprite(game.notes[index].malus_sprite_id,
                         game.notes[index].posx, game.notes[index].posy);

    game.notes[index].malus_start_tick = timer_get_ticks();
  } else {
    game.notes[index].has_malus = 0;
  }
}

void draw_hud(void) {
  if (game.lives < 0) return;

  // display timer
  char buf[32];
  sprintf(buf, "%d", timer_get_seconds());
  graphics_draw_text(SCREEN_TILE_WIDTH - 4, 1, buf);

  // display score
  sprintf(buf, "%d", game.score);
  graphics_draw_text(6, 1, buf);

  for (UBYTE i = 0; i < MAX_LIVES; i++) {
    const UINT8 tile_index = (i >= game.lives) ? SPRITE_VRAM_INDEX_EMPTY : SPRITE_VRAM_INDEX_HEART;
    set_bkg_tiles(1 + i, 1, 1, 1, &tile_index);
  }
}

static void handle_input(UINT8 keys, UINT8 keys_prev) {
  if (!keys) return;
  
  for (UBYTE i = 0; i < NOTE_MAX_AMOUNT; i++) {
    if (game.notes[i].in_used) {
      const UBYTE key_mask = key_masks[game.notes[i].key];
      
      if (keys & key_mask) {
        game.score += NOTE_SCORE_VALUE;
        game.notes[i].in_used = 0;
        graphics_hide_sprite(game.notes[i].sprite_id);
        if (game.notes[i].has_malus) {
          graphics_hide_sprite(game.notes[i].malus_sprite_id);
        }
      }
    }
  }
}

void check_game_over(void) {
  if (game.lives <= 0) {
    // Temporaryly switch to menu scene
    scene_set(&scene_menu);
  }
}

Scene scene_game = {load, update, unload, handle_input};
