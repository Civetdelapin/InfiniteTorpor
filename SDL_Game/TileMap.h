#pragma once
#include "Renderer.h"
#include "Component.h"
#include "Room.h"

class TileMap : public Renderer, public Component
{
public:
	TileMap(GameObject* gameObject, OwnMathFuncs::Vector2 spriteSize, Room* roomData, SDL_Texture* texture);
	~TileMap();

	void render();
	void clean();

	OwnMathFuncs::Vector2 getSpriteSize();

	Room* getRoomData();

private:
	SDL_Texture* texture;
	Room* roomData;

	OwnMathFuncs::Vector2 spriteSize;
};

