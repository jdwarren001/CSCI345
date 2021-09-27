SRC = source
MAINSRC = $(SRC)/main.cpp
BIN = bin/Simple
SDL2CFLAGS = -IC:/libsdl/include/SDL2
SDL2LIBS = -LC:/libsdl/lib -lmingw32 -lSDL2main -lSDL2

all: $(BIN)

$(BIN): $(MAINSRC)
	g++ $(MAINSRC) $(SDL2CFLAGS) -o $(BIN) $(SDL2LIBS)

run: $(BIN)
	$(BIN)