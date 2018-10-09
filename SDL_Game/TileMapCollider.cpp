#include "TileMapCollider.h"
#include "GenerateLevel.h"


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

			OwnMathFuncs::Vector2 new_world_pos = { game_object->getWorldPosition().x - (GenerateLevel::room_grid_size_x * room_behavior->getRoomData()->getTileMapData()->sprite_size.x * game_object->local_scale.x) / 2,
													game_object->getWorldPosition().y - (GenerateLevel::room_grid_size_y * room_behavior->getRoomData()->getTileMapData()->sprite_size.y * game_object->local_scale.y) / 2 };

			float div_x = (game_object->getWorldScale().x * room_behavior->getRoomData()->getTileMapData()->sprite_size.x);
			float div_y = (game_object->getWorldScale().y * room_behavior->getRoomData()->getTileMapData()->sprite_size.y);

			TileMapData* tileMapData = room_behavior->getRoomData()->getTileMapData();

			//We test every corner of the BoxCollider
			
			//UPPER LEFT
			x = ((box_collider->getRect().x ) - (new_world_pos.x) / div_x);
			y = ((box_collider->getRect().y ) - (new_world_pos.y) / div_y);

			
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
	/*
	if (room_behavior != nullptr) {

		OwnMathFuncs::Vector2 sprite_size = room_behavior->getRoomData()->getTileMapData()->sprite_size;
		OwnMathFuncs::Vector2 new_world_pos = { game_object->getWorldPosition().x - (GenerateLevel::room_grid_size_x * room_behavior->getRoomData()->getTileMapData()->sprite_size.x * game_object->local_scale.x) / 2,
			game_object->getWorldPosition().y - (GenerateLevel::room_grid_size_y * room_behavior->getRoomData()->getTileMapData()->sprite_size.y * game_object->local_scale.y) / 2 };


		for (std::vector<TileData*> tiles_ligne : room_behavior->getRoomData()->getTileMapData()->data) {

			
			for (TileData* tile : tiles_ligne) {

				if (tile != nullptr) {
					SDL_Rect srcrect;
					SDL_Rect dstrect;

					srcrect.x = (tile->nb_img % 30) * sprite_size.x;
					srcrect.y = (tile->nb_img / 30) * sprite_size.y;
					srcrect.h = sprite_size.x;
					srcrect.w = sprite_size.y;

					dstrect.x = new_world_pos.x + (tile->position_grid.x * sprite_size.x * game_object->getWorldScale().x);
					dstrect.y = new_world_pos.y + (tile->position_grid.y * sprite_size.y * game_object->getWorldScale().y);

					dstrect.h = sprite_size.x * game_object->getWorldScale().x;
					dstrect.w = sprite_size.y * game_object->getWorldScale().y;

					//TextureManager::DrawTexture(texture, srcrect, dstrect);

					if (tile->is_collider) {
						TextureManager::DrawRect(dstrect);
					}
				}
			}
			
		}
	}
	*/
}

