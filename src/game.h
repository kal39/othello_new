#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

typedef enum Color { BLACK, WHITE, EMPTY } Color;

typedef struct GameState {
	int turn;
	bool over;
	Color cells[64];
} GameState;

GameState create_game_state();
Color get_active_player(GameState *g);
Color get_inactive_player(GameState *g);
Color get_piece(GameState *g, int row, int col);
void set_piece(GameState *g, int row, int col, Color color);
bool check_placable(GameState *g, int row, int col);
bool place_piece(GameState *g, int row, int col);

#endif