WinSRC = source
WinMAINSRC = $(WinSRC)/main.cpp
WinBIN = bin/Simple
WinSDL2CFLAGS = -IC:/libsdl/include/SDL2
WinSDL2LIBS = -LC:/libsdl/lib -lmingw32 -lSDL2main -lSDL2

allCliff: $(WinBIN)

$(WinBIN): $(WinMAINSRC)
	g++ $(WinMAINSRC) $(WinSDL2CFLAGS) -o $(WinBIN) $(WinSDL2LIBS)

Winrun: $(WinBIN)
	$(WinBIN)


MacSRC = source
MacMAINSRC = $(MacSRC)/main.cpp
MacBIN = bin/Simple
MacSDL2CFLAGS = -I/usr/include/SDL2 -D_REENTRANT
MacSDL2LIBS = -lSDL2

Macall: $(MacBIN)

$(MacBIN): $(MacMAINSRC)
	g++ $(MacMAINSRC) $(MacSDL2CFLAGS) -o $(MacBIN) $(MacSDL2LIBS)

Macrun: $(MacBIN)
	$(MacBIN)