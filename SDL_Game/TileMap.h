#pragma once
#include "Component.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct Tile {
	OwnMathFuncs::Vector2 position_grid = {0, 0};
	int nb_img;
	bool is_collider = false;

	Tile();
};

class TileMap : virtual public Component
{
public:
	TileMap(GameObject* game_object, std::string img_path, OwnMathFuncs::Vector2 sprite_size, std::string data_path);
	TileMap(GameObject* game_object, std::string img_path, OwnMathFuncs::Vector2 sprite_size, std::string data_path, std::string collider_path);
	~TileMap();

	void render();
	void clean();

	void readCSV(const char* file_path, std::vector<std::vector<Tile>>& vls);
	
	std::vector<std::vector<Tile>> getData();

	Tile* getTile(int x, int y);

	OwnMathFuncs::Vector2 sprite_size;

private:
	SDL_Texture* texture;
	
	void readCSVCollider(const char* file_path);

	std::vector<std::vector<Tile>> data;
};

