#include "TileMapCollider.h"



TileMapCollider::TileMapCollider(GameObject* game_object) : Collider(game_object)
{
	
}


TileMapCollider::~TileMapCollider()
{
}

bool TileMapCollider::isColliding(Collider * collider)
{
	/*
	if (room_behavior != nullptr) {

		if (BoxCollider* box_collider = dynamic_cast<BoxCollider*>(collider)) {

			collider->update();

			int x;
			int y;


			OwnMathFuncs::Vector2 new_world_pos = { game_object->getWorldPosition().x - (32 * 16 * 4) / 2, game_object->getWorldPosition().y - (20 * 16 * 4) / 2 };
			//We test every corner of the BoxCollider

			//UPPER LEFT
			x = ((box_collider->getRect().x) - (new_world_pos.x - 16 * 32 *4) / (game_object->getWorldScale().x * room_behavior->getRoomData()->getTileMapData().sprite_size.x));
			y = ((box_collider->getRect().y) - (new_world_pos.y - 16 * 20 * 4) / (game_object->getWorldScale().y * room_behavior->getRoomData()->getTileMapData().sprite_size.y));

			
			TileData* tileData = room_behavior->getRoomData()->getTileMapData().getTile(x, y);
			if (tileData != nullptr && tileData->is_collider) {
				
				return true;
			}

			//DOWN LEFT
			x = ((box_collider->getRect().x) - new_world_pos.x) / (game_object->getWorldScale().x * room_behavior->getRoomData()->getTileMapData().sprite_size.x);
			y = ((box_collider->getRect().y + box_collider->getRect().h) - new_world_pos.y) / (game_object->getWorldScale().y * room_behavior->getRoomData()->getTileMapData().sprite_size.y);
			tileData = room_behavior->getRoomData()->getTileMapData().getTile(x, y);
			if (tileData != nullptr && tileData->is_collider) {
				//std::cout << x << ", " << y << std::endl;
				return true;
			}

			//UPPER RIGHT
			x = ((box_collider->getRect().x + box_collider->getRect().w) - new_world_pos.x) / (game_object->getWorldScale().x * room_behavior->getRoomData()->getTileMapData().sprite_size.x);
			y = ((box_collider->getRect().y) - new_world_pos.y) / (game_object->getWorldScale().y * room_behavior->getRoomData()->getTileMapData().sprite_size.y);
			tileData = room_behavior->getRoomData()->getTileMapData().getTile(x, y);
			if (tileData != nullptr && tileData->is_collider) {
				//std::cout << x << ", " << y << std::endl;
				return true;
			}

			//DOWN RIGHT
			x = ((box_collider->getRect().x + box_collider->getRect().w) - new_world_pos.x) / (game_object->getWorldScale().x * room_behavior->getRoomData()->getTileMapData().sprite_size.x);
			y = ((box_collider->getRect().y + box_collider->getRect().h) - new_world_pos.y) / (game_object->getWorldScale().y * room_behavior->getRoomData()->getTileMapData().sprite_size.y);
			tileData = room_behavior->getRoomData()->getTileMapData().getTile(x, y);
			if (tileData != nullptr && tileData->is_collider) {
				//std::cout << x << ", " << y << std::endl;
				return true;
			}

			std::cout << x << ", " << y << std::endl;

		}
	}
	*/

	return false;
}

void TileMapCollider::start()
{
	room_behavior = game_object->getComponent<RoomBehavior>();
}

void TileMapCollider::update()
{


}

void TileMapCollider::render()
{
}

