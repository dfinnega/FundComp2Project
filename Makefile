all: textureRenderer texture2

textureRenderer: textureRender.cpp
	g++ textureRender.cpp -lSDL2 -o render

texture2: 07_texture_loading_and_rendering.cpp
	g++ 07_texture_loading_and_rendering.cpp -lSDL2 -o render2
