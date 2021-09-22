SRC = source
MAINSRC = $(SRC)/main.cpp
BIN = bin/Simple
SDL2CFLAGS = -I/usr/include/SDL2 -D_REENTRANT
SDL2LIBS = -lSDL2

all: $(BIN)

$(BIN): $(MAINSRC)
	g++ $(MAINSRC) $(SDL2CFLAGS) -o $(BIN) $(SDL2LIBS)

run: $(BIN)
	$(BIN)