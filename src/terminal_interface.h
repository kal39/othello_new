#ifndef TERMINAL_INTERFACE_H
#define TERMINAL_INTERFACE_H

#include "game.h"

void start_terminal_interface(void (*blackInputFun)(GameState *), void (*whiteInputFun)(GameState *));

#endif