CC=clang++
CFLAGS=-Wall -Werror -Wextra -std=c++23 -O3
SRC=BMain.cpp
BIN=BMain
OBJ=BMain.o

btree: $(BIN)

$(BIN): $(SRC)
	$(CC) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

clean:
	rm -rf BMain.o BMain

.PHONY: btree clean
