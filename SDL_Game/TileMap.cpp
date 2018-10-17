#include "TileMap.h"

TileMap::TileMap(GameObject * gameObject, OwnMathFuncs::Vector2 spriteSize, Room * roomData, SDL_Texture * texture) : Component(gameObject), Renderer(this), spriteSize(spriteSize), texture(texture), roomData(roomData)
{

}

TileMap::~TileMap()
{

}

void TileMap::render()
{
	/*
	for (std::vector<TileData*> tiles_ligne : roomData->getTileMapData().data) {

		
		for (TileData* tile : tiles_ligne) {

			if (tile->nb_img != -1) {
				SDL_Rect srcrect;
				SDL_Rect dstrect;

				srcrect.x = (tile->nb_img % 30) * spriteSize.x;
				srcrect.y = (tile->nb_img / 30) * spriteSize.y;
				srcrect.h = spriteSize.x;
				srcrect.w = spriteSize.y;

				dstrect.x = gameObject->getWorldPosition().x + (tile->position_grid.x * spriteSize.x * gameObject->getWorldScale().x);
				dstrect.y = gameObject->getWorldPosition().y + (tile->position_grid.y * spriteSize.y * gameObject->getWorldScale().y);

				dstrect.h = spriteSize.x * gameObject->getWorldScale().x;
				dstrect.w = spriteSize.y * gameObject->getWorldScale().y;

				TextureManager::DrawTexture(texture, srcrect, dstrect);

				if (tile->is_collider) {
					TextureManager::DrawRect(dstrect);
				}
			}
		}
	}
	*/
}

void TileMap::clean()
{
	/*
	for (std::vector<TileData*> tiles_ligne : roomData->getTileMapData().data) {

		for (TileData* tile : tiles_ligne) {
			delete tile;
		}
	}

	Renderer::clean();
	Component::clean();
	*/
}

OwnMathFuncs::Vector2 TileMap::getSpriteSize()
{
	return spriteSize;
}

Room * TileMap::getRoomData()
{
	return roomData;
}
