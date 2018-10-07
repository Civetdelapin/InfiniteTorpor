#include "TileMapCollider.h"



TileMapCollider::TileMapCollider(GameObject* game_object) : Collider(game_object)
{
	
}


TileMapCollider::~TileMapCollider()
{
}

bool TileMapCollider::isColliding(Collider * collider)
{
	
	if (room_behavior != nullptr) {

		if (BoxCollider* box_collider = dynamic_cast<BoxCollider*>(collider)) {
			
			collider->update();

			int x;
			int y;

			
			OwnMathFuncs::Vector2 new_world_pos = { game_object->getWorldPosition().x - (32 * 16 * 4) / 2, game_object->getWorldPosition().y - (20 * 16 * 4) / 2 };

			float div_x = (game_object->getWorldScale().x * room_behavior->getRoomData()->getTileMapData()->sprite_size.x);
			float div_y = (game_object->getWorldScale().y * room_behavior->getRoomData()->getTileMapData()->sprite_size.y);

			TileMapData* tileMapData = room_behavior->getRoomData()->getTileMapData();

			//We test every corner of the BoxCollider
			
			//UPPER LEFT
			x = ((box_collider->getRect().x) - (new_world_pos.x) / div_x);
			y = ((box_collider->getRect().y) - (new_world_pos.y) / div_y);

			
			TileData* tileData = tileMapData->getTile(x, y);
			if (tileData != nullptr && tileData->is_collider) {
				
				return true;
			}
			

			//DOWN LEFT
			x = ((box_collider->getRect().x) - new_world_pos.x) /div_x;
			y = ((box_collider->getRect().y + box_collider->getRect().h) - new_world_pos.y) / div_y;
			
			tileData = tileMapData->getTile(x, y);
			if (tileData != nullptr && tileData->is_collider) {
			
				return true;
			}
			

			//UPPER RIGHT
			x = ((box_collider->getRect().x + box_collider->getRect().w) - new_world_pos.x) /div_x;
			y = ((box_collider->getRect().y) - new_world_pos.y) / div_y;

			
			tileData = tileMapData->getTile(x, y);
			if (tileData != nullptr && tileData->is_collider) {
				
				return true;
			}
			

			//DOWN RIGHT
			x = ((box_collider->getRect().x + box_collider->getRect().w) - new_world_pos.x) /div_x;
			y = ((box_collider->getRect().y + box_collider->getRect().h) - new_world_pos.y) / div_y;
			
			tileData = tileMapData->getTile(x, y);
			if (tileData != nullptr && tileData->is_collider) {
				
				return true;
			}
			
		}
	}
	

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

