#include "TileMapCollider.h"



TileMapCollider::TileMapCollider(GameObject* game_object, TileMap tile_map) : Collider(game_object)
{

}


TileMapCollider::~TileMapCollider()
{
}

bool TileMapCollider::isColliding(Collider * collider)
{
	return false;
}

void TileMapCollider::update()
{




}

void TileMapCollider::render(float camera_pos_x, float camera_pos_y)
{


}
