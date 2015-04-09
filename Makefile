FILE=smb

all: $(FILE)

$(FILE): $(FILE).o init.o
	g++ $(FILE).o init.o -lSDL2 -lSDL_image -o $(FILE)

$(FILE).o: $(FILE).cpp
	g++ $(FILE).cpp -lSDL2 -lSDL_image -c

SDL: init.cpp
	g++ init.cpp -lSDL2 -lSDL_image -c

PHONY: clean
clean:
	rm *.o $(FILE)
