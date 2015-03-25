all: textureRenderer

textureRenderer: textureRender.cpp
	g++ textureRender.cpp -lSDL2 -o render
