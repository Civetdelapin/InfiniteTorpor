#pragma once
#include "SDL.h"
#include <string>
#include "TextureManager.h"
#include <vector>

class Map
{
public:

	static std::vector<std::string> loadMap(SDL_Renderer* renderer);
	
	const static int tile_width = 16;
	const static int tile_height = 16;

private:
	static SDL_Texture* map_texture;
	
	static void readCSV(FILE *fp, std::vector<std::string>& vls);
};

