CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -Iinclude
DEBUG_FLAGS = -g -O0 -fsanitize=address
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

TARGET = eafitos
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: all run clean test debug memcheck

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

debug: clean
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(TARGET)

test: $(TARGET)
	chmod +x tests/smoke_test.sh
	./tests/smoke_test.sh

memcheck: $(TARGET)
	valgrind $(VALGRIND_FLAGS) ./$(TARGET)

clean:
	rm -f $(TARGET) src/*.o prueba prueba.c
