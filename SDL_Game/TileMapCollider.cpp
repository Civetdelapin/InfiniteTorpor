#include "TileMapCollider.h"
#include "GenerateLevel.h"


TileMapCollider::TileMapCollider(GameObject* gameObject) : Collider(gameObject)
{
	
}


TileMapCollider::~TileMapCollider()
{
}

bool TileMapCollider::isColliding(Collider * collider)
{
	
	if (roomBehavior != nullptr) {

		if (BoxCollider* boxCollider = dynamic_cast<BoxCollider*>(collider)) {
			
			collider->update();

			int x;
			int y;

			OwnMathFuncs::Vector2 new_world_pos = { gameObject->getWorldPosition().x - (GenerateLevel::ROOM_GRID_SIZE_X * roomBehavior->getRoomData()->getTileMapData()->spriteSize.x * gameObject->localScale.x) / 2,
													gameObject->getWorldPosition().y - (GenerateLevel::ROOM_GRID_SIZE_Y * roomBehavior->getRoomData()->getTileMapData()->spriteSize.y * gameObject->localScale.y) / 2 };

			float div_x = (gameObject->getWorldScale().x * roomBehavior->getRoomData()->getTileMapData()->spriteSize.x);
			float div_y = (gameObject->getWorldScale().y * roomBehavior->getRoomData()->getTileMapData()->spriteSize.y);

			TileMapData* tileMapData = roomBehavior->getRoomData()->getTileMapData();

			//We test every corner of the BoxCollider
			
			//UPPER LEFT
			x = ((boxCollider->getRect().x ) - (new_world_pos.x) / div_x);
			y = ((boxCollider->getRect().y ) - (new_world_pos.y) / div_y);

			
			TileData* tileData = tileMapData->getTile(x, y);
			if (tileData != nullptr && tileData->collider) {
				
				return true;
			}
			

			//DOWN LEFT
			x = ((boxCollider->getRect().x) - new_world_pos.x) /div_x;
			y = ((boxCollider->getRect().y + boxCollider->getRect().h) - new_world_pos.y) / div_y;
			
			tileData = tileMapData->getTile(x, y);
			if (tileData != nullptr && tileData->collider) {
			
				return true;
			}
			

			//UPPER RIGHT
			x = ((boxCollider->getRect().x + boxCollider->getRect().w) - new_world_pos.x) /div_x;
			y = ((boxCollider->getRect().y) - new_world_pos.y) / div_y;

			
			tileData = tileMapData->getTile(x, y);
			if (tileData != nullptr && tileData->collider) {
				
				return true;
			}
			

			//DOWN RIGHT
			x = ((boxCollider->getRect().x + boxCollider->getRect().w) - new_world_pos.x) /div_x;
			y = ((boxCollider->getRect().y + boxCollider->getRect().h) - new_world_pos.y) / div_y;
			
			tileData = tileMapData->getTile(x, y);
			if (tileData != nullptr && tileData->collider) {
	 			
				return true;
			}
			
		}
	}
	

	return false;
}

void TileMapCollider::start()
{
	roomBehavior = gameObject->getComponent<RoomBehavior>();
}

void TileMapCollider::update()
{


}

void TileMapCollider::render()
{
	/*
	if (roomBehavior != nullptr) {

		OwnMathFuncs::Vector2 spriteSize = roomBehavior->getRoomData()->getTileMapData()->spriteSize;
		OwnMathFuncs::Vector2 new_world_pos = { gameObject->getWorldPosition().x - (GenerateLevel::ROOM_GRID_SIZE_X * roomBehavior->getRoomData()->getTileMapData()->spriteSize.x * gameObject->localScale.x) / 2,
			gameObject->getWorldPosition().y - (GenerateLevel::ROOM_GRID_SIZE_Y * roomBehavior->getRoomData()->getTileMapData()->spriteSize.y * gameObject->localScale.y) / 2 };


		for (std::vector<TileData*> tiles_ligne : roomBehavior->getRoomData()->getTileMapData()->data) {

			
			for (TileData* tile : tiles_ligne) {

				if (tile != nullptr) {
					SDL_Rect srcrect;
					SDL_Rect dstrect;

					srcrect.x = (tile->nbImg % 30) * spriteSize.x;
					srcrect.y = (tile->nbImg / 30) * spriteSize.y;
					srcrect.h = spriteSize.x;
					srcrect.w = spriteSize.y;

					dstrect.x = new_world_pos.x + (tile->positionGrid.x * spriteSize.x * gameObject->getWorldScale().x);
					dstrect.y = new_world_pos.y + (tile->positionGrid.y * spriteSize.y * gameObject->getWorldScale().y);

					dstrect.h = spriteSize.x * gameObject->getWorldScale().x;
					dstrect.w = spriteSize.y * gameObject->getWorldScale().y;

					//TextureManager::DrawTexture(texture, srcrect, dstrect);

					if (tile->collider) {
						TextureManager::DrawRect(dstrect);
					}
				}
			}
			
		}
	}
	*/
}

