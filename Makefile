CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address -fsanitize=undefined
LDFLAGS = -fsanitize=address -fsanitize=undefined
INCLUDES = -Iinclude

SRC = src/matrix.c
OBJ = build/matrix.o
TEST = test/test.c
BIN = build/test

all: $(BIN)

$(BIN): $(OBJ) $(TEST)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ) $(TEST) $(LDFLAGS)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf build

format:
	clang-format -i include/*.h src/*.c test/*.c

check:
	cppcheck --enable=all --inconclusive --std=c99 --language=c . --suppress=missingIncludeSystem

valgrind:
	valgrind --leak-check=full ./$(BIN)
