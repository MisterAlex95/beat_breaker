# GBDK Makefile for Game Boy development
# Based on GBDK-2020

# ============================================================================
# PROJECT CONFIGURATION
# ============================================================================

PROJECT = gameboy_project
BUILD_DIR = build
SRC_DIR = src
SRC_ENGINE_DIR = src/engine
SRC_SYSTEM_DIR = src/system
SRC_SCENE_DIR = src/scene
SRC_SCENE_GAME = src/scene/game
SRC_SCENE_MENU = src/scene/menu
SRC_UTILS_DIR = src/utils
SRC_ASSETS_DIR = src/assets

# ============================================================================
# GBDK CONFIGURATION
# ============================================================================

GBDK_HOME = /Users/alex/gbdk
CC = $(GBDK_HOME)/bin/lcc
AS = $(GBDK_HOME)/bin/lcc
OBJCOPY = $(GBDK_HOME)/bin/objcopy

# ============================================================================
# SOURCE FILES
# ============================================================================

SOURCES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/game.c \
	$(SRC_SYSTEM_DIR)/scene.c \
	$(SRC_ENGINE_DIR)/graphics.c \
	$(SRC_ENGINE_DIR)/timer.c \
	$(SRC_ENGINE_DIR)/input.c \
	$(SRC_SCENE_MENU)/scene_menu.c \
	$(SRC_SCENE_GAME)/game_logic.c \
	$(SRC_SCENE_GAME)/input_handler.c \
	$(SRC_SCENE_GAME)/note_manager.c \
	$(SRC_SCENE_GAME)/scene_game.c \
	$(SRC_SCENE_GAME)/ui_manager.c \
	$(SRC_ASSETS_DIR)/tileset.c \
	$(SRC_ASSETS_DIR)/ui.c \
	$(SRC_UTILS_DIR)/math.c

# ============================================================================
# COMPILER FLAGS
# ============================================================================

CFLAGS = -Wa-l -Wl-m -Wl-j -I$(SRC_DIR) \
	-I$(SRC_ENGINE_DIR) \
	-I$(SRC_SYSTEM_DIR) \
	-I$(SRC_SCENE_GAME) \
	-I$(SRC_SCENE_MENU) \
	-I$(SRC_ASSETS_DIR) \
	-I$(SRC_UTILS_DIR)

# ============================================================================
# TARGETS
# ============================================================================

# Default target
all: $(BUILD_DIR)/$(PROJECT).gb

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile the ROM
$(BUILD_DIR)/$(PROJECT).gb: $(SOURCES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Run in emulator (requires an emulator like SameBoy, BGB, or VBA)
run: $(BUILD_DIR)/$(PROJECT).gb
	open $(BUILD_DIR)/$(PROJECT).gb

# Debug build with additional symbols
debug: CFLAGS += -Wl-y
debug: $(BUILD_DIR)/$(PROJECT).gb

.PHONY: all clean run debug
