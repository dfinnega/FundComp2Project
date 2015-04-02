FILE=smb

all: $(FILE) texture

$(FILE): $(FILE).o init.o
	g++ $(FILE).o init.o -lSDL2 -lSDL_image -O0 -g3 -o $(FILE)

texture: marioAcrossScreen.cpp
	g++ marioAcrossScreen.cpp -lSDL2 -lSDL_image -o render2

$(FILE).o: $(FILE).cpp
	g++ $(FILE).cpp -lSDL2 -lSDL_image -c

SDL: init.cpp
	g++ init.cpp -lSDL2 -lSDL_image -c

PHONY: clean
clean:
	rm *.o $(FILE) texture
