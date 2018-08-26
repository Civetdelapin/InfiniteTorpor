#pragma once
#include "SDL.h"
#include <string>
#include "TextureManager.h"

#include "GameObject.h"
#include "TileMap.h"

class Map : public GameObject
{
public:

	Map(std::string img_path, OwnMathFuncs::Vector2* sprite_size, std::string data_path);
	~Map();

private:

};