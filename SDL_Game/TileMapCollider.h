#pragma once
#include "Collider.h"
#include "TileMap.h"
#include "BoxCollider.h"
#include "RoomBehavior.h"

class TileMapCollider : public Collider
{
public:
	TileMapCollider(GameObject* gameObject);
	~TileMapCollider();


	bool isColliding(Collider* collider);

	void start();
	void update();

	void render();

private:
	RoomBehavior* room_behavior;
};

