#include "TileMapCollider.h"



TileMapCollider::TileMapCollider(GameObject* game_object) : Collider(game_object)
{
	tileMap = game_object->getComponent<TileMap>();

}


TileMapCollider::~TileMapCollider()
{
}

bool TileMapCollider::isColliding(Collider * collider)
{
	if (tileMap != nullptr) {

		if (BoxCollider* box_collider = dynamic_cast<BoxCollider*>(collider)) {

			collider->update();

			int x;
			int y;

			//We test every corner of the BoxCollider

			//UPPER LEFT
			x = ((box_collider->getRect().x) - game_object->getWorldPosition().x) / (game_object->getWorldScale().x * tileMap->getSpriteSize().x);
			y = ((box_collider->getRect().y) - game_object->getWorldPosition().y) / (game_object->getWorldScale().y * tileMap->getSpriteSize().y);
			Tile* tile = tileMap->getTile(x, y);
			if (tile != nullptr && tile->is_collider) {

				return true;
			}

			//DOWN LEFT
			x = ((box_collider->getRect().x) - game_object->getWorldPosition().x) / (game_object->getWorldScale().x * tileMap->getSpriteSize().x);
			y = ((box_collider->getRect().y + box_collider->getRect().h) - game_object->getWorldPosition().y) / (game_object->getWorldScale().y * tileMap->getSpriteSize().y);
			tile = tileMap->getTile(x, y);
			if (tile != nullptr && tile->is_collider) {

				return true;
			}

			//UPPER RIGHT
			x = ((box_collider->getRect().x + box_collider->getRect().w) - game_object->getWorldPosition().x) / (game_object->getWorldScale().x * tileMap->getSpriteSize().x);
			y = ((box_collider->getRect().y) - game_object->getWorldPosition().y) / (game_object->getWorldScale().y * tileMap->getSpriteSize().y);
			tile = tileMap->getTile(x, y);
			if (tile != nullptr && tile->is_collider) {

				return true;
			}

			//DOWN RIGHT
			x = ((box_collider->getRect().x + box_collider->getRect().w) - game_object->getWorldPosition().x) / (game_object->getWorldScale().x * tileMap->getSpriteSize().x);
			y = ((box_collider->getRect().y + box_collider->getRect().h) - game_object->getWorldPosition().y) / (game_object->getWorldScale().y * tileMap->getSpriteSize().y);
			tile = tileMap->getTile(x, y);
			if (tile != nullptr && tile->is_collider) {

				return true;
			}

			return false;
		}
	}
}

void TileMapCollider::update()
{


}

void TileMapCollider::render()
{


}
