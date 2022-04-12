#------------------------------------------------------------------------------#
# important variables                                                          #
#------------------------------------------------------------------------------#

BIN := othello
FLAGS := -Wall -Wno-missing-braces

#------------------------------------------------------------------------------#
# other variables                                                              #
#------------------------------------------------------------------------------#

CC := gcc $(FLAGS)
RM := rm -rf
MKDIR := mkdir -p

BUILD := build
SRC := src

#------------------------------------------------------------------------------#
# build process                                                                #
#------------------------------------------------------------------------------#

.PHONY: all clean

all: $(BUILD)
	$(CC) -c $(SRC)/main.c -o $(BUILD)/main.a
	$(CC) -c $(SRC)/game.c -o $(BUILD)/game.a
	$(CC) -c $(SRC)/terminal_interface.c -o $(BUILD)/terminal_interface.a

	$(CC) $(BUILD)/* -o $(BIN)

$(BUILD):
	$(MKDIR) $(BUILD)

clean:
	$(RM) $(BUILD)
	$(RM) $(BIN)