CC = gcc
CFLAGS = -Wall -Wextra -pthread -I./include
LDFLAGS = -lncurses -lm

SRC = src/main.c src/game.c src/tetrimino.c src/render.c src/input.c src/utilities.c
OBJ = $(SRC:.c=.o)
TARGET = tetris

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run