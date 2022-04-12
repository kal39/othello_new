#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "terminal_interface.h"

static void _set_terminal_fg_color(unsigned char r, unsigned char g, unsigned char b) {
	printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}

static void _set_terminal_bg_color(unsigned char r, unsigned char g, unsigned char b) {
	printf("\x1b[48;2;%d;%d;%dm", r, g, b);
}

static void _reset_terminal_colors() {
	printf("\x1b[0m");
}

static void _get_input(GameState *g) {
	int row = -1, col = -1;

	while (true) {
		printf("  input row: ");
		scanf("%d", &row);
		printf("  input column: ");
		scanf("%d", &col);

		if (place_piece(g, row, col)) break;
		else printf("illegal move, try again:\n");
	}
}

static void _print_board(GameState *g) {
	printf("\nTURN %d - %s to play\n", g->turn, get_active_player(g) == BLACK ? "black" : "white");
	printf("  0 1 2 3 4 5 6 7\n");

	for (int i = 0; i < 8; i++) {
		printf("%d ", i);
		for (int j = 0; j < 8; j++) {
			if (i % 2 == j % 2) _set_terminal_bg_color(0, 70, 20);
			else _set_terminal_bg_color(0, 90, 30);

			switch (get_piece(g, i, j)) {
				case BLACK:
					_set_terminal_fg_color(0, 0, 0);
					printf("● ");
					break;
				case WHITE:
					_set_terminal_fg_color(255, 255, 255);
					printf("● ");
					break;
				case EMPTY:
					_set_terminal_fg_color(255, 0, 0);
					printf(check_placable(g, i, j) ? "◌ " : "  ");
					break;
			}

			_reset_terminal_colors();
		}
		printf("\n");
	}
}

void start_terminal_interface(void (*blackInputFun)(GameState *), void (*whiteInputFun)(GameState *)) {
	GameState g = create_game_state();

	if (blackInputFun == NULL) blackInputFun = &_get_input;
	if (whiteInputFun == NULL) whiteInputFun = &_get_input;

	while (!g.over) {
		_print_board(&g);
		get_active_player(&g) == BLACK ? blackInputFun(&g) : whiteInputFun(&g);
		if (get_active_player(&g) == BLACK) blackInputFun(&g);
		else whiteInputFun(&g);
	}
}