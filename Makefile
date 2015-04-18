FILE=smb

all: $(FILE)

$(FILE): $(FILE).o init.o Mario.o enemy.o Ltexture.o
	g++ $(FILE).o init.o Mario.o enemy.o Ltexture.o -lSDL2 -o $(FILE)

$(FILE).o: $(FILE).cpp
	g++ $(FILE).cpp -lSDL2 -c

init.o: init.cpp
	g++ init.cpp -lSDL2 -c

Mario.o: Mario.cpp
	g++ Mario.cpp -lSDL2 -c

enemy.o: enemy.cpp
	g++ enemy.cpp -lSDL2 -c

Ltexture.o: Ltexture.cpp
	g++ Ltexture.cpp -lSDL2 -c

PHONY: clean
clean:
	rm *.o $(FILE)
