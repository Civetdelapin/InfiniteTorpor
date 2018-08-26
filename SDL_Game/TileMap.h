#pragma once
#include "Component.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct Tile {
	OwnMathFuncs::Vector2 position_grid = {0, 0};
	int nb_img;

	Tile();
};

class TileMap : virtual public Component
{
public:
	TileMap(GameObject* game_object, std::string img_path, OwnMathFuncs::Vector2* sprite_size, std::string data_path);
	~TileMap();

	void render(float camera_pos_x, float camera_pos_y);

	void readCSV(const char* file_path, std::vector<Tile> &data);

private:
	SDL_Texture* texture;
	OwnMathFuncs::Vector2* sprite_size;

	std::vector<Tile> data;

};

