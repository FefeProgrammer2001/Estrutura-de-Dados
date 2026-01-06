CC =clang++
CFLAG =-Wall -Werror -Wextra -std=c++23 -O3
SRC =Main.cpp
OBJ =Main.o
BIN =Main

Hash: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAG) -c $(SRC)
	$(CC) $(OBJ) -o $(BIN)

clean:
	rm -rf Main Main.o

.PHONY: Hash Clean
