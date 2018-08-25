#pragma once
#include "SDL.h"
#include <string>
#include "TextureManager.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "GameObject.h"

class Map : public virtual GameObject
{
public:

	Map(SDL_Renderer* renderer, int map_int);
	~Map();

	
	const static int tile_width = 16;
	const static int tile_height = 16;

	void render(float camera_pos_x, float camera_pos_y);

	int getTile(int x, int y);

private:
	
	void readCSV(const char* file_path, std::vector<std::vector<int>>& vls);
	std::vector<std::vector<int>> mapValues;

	std::vector<std::vector<int>> mapCollider;

	void DrawMap(std::vector<std::vector<int>> vecToDraw, float camera_pos_x, float camera_pos_y);

	SDL_Texture* map_texture;
};

