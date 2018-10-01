#pragma once
#include "Collider.h"
#include "TileMap.h"
#include "BoxCollider.h"

class TileMapCollider : public Collider
{
public:
	TileMapCollider(GameObject* game_object);
	~TileMapCollider();


	bool isColliding(Collider* collider);
	void update();

	void render();

private:
	TileMap* tileMap;
};

