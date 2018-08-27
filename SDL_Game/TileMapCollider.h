#pragma once
#include "Collider.h"
#include "TileMap.h"

class TileMapCollider : public Collider
{
public:
	TileMapCollider(GameObject* game_object, TileMap tile_map);
	~TileMapCollider();


	bool isColliding(Collider* collider);


	void update();
	void render(float camera_pos_x, float camera_pos_y);


protected:
	std::vector<std::vector<int>*>* collider_values;
};

