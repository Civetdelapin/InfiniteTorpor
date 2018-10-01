#include "Map.h"

Map::Map(std::string img_path, OwnMathFuncs::Vector2 sprite_size, std::string data_path)
{
	TileMap* tileMap = new TileMap(this, img_path, sprite_size, data_path);
	tileMap->setLayer(0);

	TileMapCollider* tile_map_collider = new TileMapCollider(this);
	tile_map_collider->setLayer(0);

	local_scale = { 3, 3 };
}

Map::Map(std::string img_path, OwnMathFuncs::Vector2 sprite_size, std::string data_path, std::string collider_path)
{
	TileMap* tileMap = new TileMap(this, img_path, sprite_size, data_path, collider_path);
	tileMap->setLayer(0);

	TileMapCollider* tile_map_collider = new TileMapCollider(this);
	tile_map_collider->setLayer(0);

	local_scale = { 3, 3 };
}

Map::~Map()
{

}


