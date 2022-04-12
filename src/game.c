#include <stdio.h>

#include "game.h"

static int _idx(int row, int col) {
	return row * 8 + col;
}

static int _check_in_board(int row, int col) {
	return row >= 0 && row < 8 && col >= 0 && col < 8;
}

static bool _check_direction(GameState *g, int row, int col, int dirRow, int dirCol) {
	int nextRow = row + dirRow;
	int nextCol = col + dirCol;

	if (_check_in_board(nextRow, nextCol) && get_piece(g, nextRow, nextCol) == get_inactive_player(g)) {
		nextRow += dirRow;
		nextCol += dirCol;

		while (nextRow >= 0 && nextRow < 8 && nextCol >= 0 && nextCol < 8) {
			if (get_piece(g, nextRow, nextCol) == get_active_player(g)) return true;
			nextRow += dirRow;
			nextCol += dirCol;
		}
	}

	return false;
}

static void _flip_direction(GameState *g, int row, int col, int dirRow, int dirCol) {

	if (_check_direction(g, row, col, dirRow, dirCol)) {
		int nextRow = row + dirRow;
		int nextCol = col + dirCol;

		while (nextRow >= 0 && nextRow < 8 && nextCol >= 0 && nextCol < 8) {
			if (get_piece(g, nextRow, nextCol) == get_active_player(g)) return;
			else set_piece(g, nextRow, nextCol, get_active_player(g));

			nextRow += dirRow;
			nextCol += dirCol;
		}
	}
}

static bool _skip_necessary(GameState *g) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (check_placable(g, i, j)) return false;
		}
	}
	return true;
}

GameState create_game_state() {
	GameState g;
	g.turn = 1;
	g.over = false;
	for (int i = 0; i < 64; i++) g.cells[i] = EMPTY;
	set_piece(&g, 3, 3, WHITE);
	set_piece(&g, 3, 4, BLACK);
	set_piece(&g, 4, 3, BLACK);
	set_piece(&g, 4, 4, WHITE);
	return g;
}

Color get_active_player(GameState *g) {
	return g->turn % 2 == 0 ? WHITE : BLACK;
}

Color get_inactive_player(GameState *g) {
	return g->turn % 2 == 0 ? BLACK : WHITE;
}

Color get_piece(GameState *g, int row, int col) {
	return g->cells[_idx(row, col)];
}

void set_piece(GameState *g, int row, int col, Color color) {
	g->cells[_idx(row, col)] = color;
}

bool check_placable(GameState *g, int row, int col) {
	if (get_piece(g, row, col) == EMPTY) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (_check_direction(g, row, col, i, j)) return true;
			}
		}
	}

	return false;
}

bool place_piece(GameState *g, int row, int col) {
	if (check_placable(g, row, col)) {
		set_piece(g, row, col, get_active_player(g));

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				_flip_direction(g, row, col, i, j);
			}
		}

		g->turn++;

		if (_skip_necessary(g)) {
			g->turn++;
			if (_skip_necessary(g)) g->over = true;
		}

		return true;
	}

	return false;
}