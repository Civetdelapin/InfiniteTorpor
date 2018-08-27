#include "Map.h"

Map::Map(std::string img_path, OwnMathFuncs::Vector2* sprite_size, std::string data_path)
{
	TileMap* tileMap = new TileMap(this, img_path, sprite_size, data_path);
	addComponent(tileMap);

	scale = { 3, 3 };
}

Map::Map(std::string img_path, OwnMathFuncs::Vector2 * sprite_size, std::string data_path, std::string collider_path)
{
	TileMap* tileMap = new TileMap(this, img_path, sprite_size, data_path, collider_path);
	addComponent(tileMap);

	scale = { 3, 3 };
}

Map::~Map()
{

}


