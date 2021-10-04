SRC=source
HEADERS=$(SRC)/Exception.hpp $(SRC)/MediaManager.hpp $(SRC)/Game.hpp $(SRC)/Particle.hpp $(SRC)/Animation.hpp
MAINSRC=$(SRC)/main.cpp 
BIN=bin/Simple
SDL2CFLAGS=-I/usr/include/SDL2 -D_REENTRANT
SDL2LIBS=-lSDL2 -lSDL2_mixer

all: $(BIN)

$(BIN): $(MAINSRC) $(HEADERS) 
		g++ -g $(MAINSRC) $(SDL2CFLAGS) -o $(BIN) $(SDL2LIBS) -DRELEASE
		
debug: $(BIN)
	gdb $(BIN)
		
run:  $(BIN)
	$(BIN)


### Old Stuff, tbd


# SRC=source
# #HEADERS=$(SRC)/Exception.hpp $(SRC)/MediaManager.hpp $(SRC)/Game.hpp $(SRC)/Particle.hpp
# MAINSRC=$(SRC)/main.cpp 
# BIN=bin/Simple
# SDL2CFLAGS=-I/usr/include/SDL2 -D_REENTRANT
# SDL2LIBS=-lSDL2

# all: $(BIN)

# $(BIN): $(MAINSRC) $(HEADERS) 
# 	g++ -g $(MAINSRC) $(SDL2CFLAGS) -o $(BIN) $(SDL2LIBS)
		
# debug: $(BIN)
# 	gdb $(BIN)
		
# run:  $(BIN)
# 	$(BIN)



#MacSRC = source
#MacMAINSRC = $(MacSRC)/main.cpp
#MacBIN = bin/Simple
#MacSDL2CFLAGS = -I/usr/include/SDL2 -D_REENTRANT
#MacSDL2LIBS = -lSDL2

#Maccall: $(MacBIN)

#$(MacBIN): $(MacMAINSRC)
#	g++ $(MacMAINSRC) $(MacSDL2CFLAGS) -o $(MacBIN) $(MacSDL2LIBS)

#Macrun: $(MacBIN)
#	$(MacBIN)
