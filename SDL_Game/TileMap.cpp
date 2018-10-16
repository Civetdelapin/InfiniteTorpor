#include "TileMap.h"

TileMap::TileMap(GameObject * gameObject, OwnMathFuncs::Vector2 sprite_size, Room * room_data, SDL_Texture * texture) : Component(gameObject), Renderer(this), sprite_size(sprite_size), texture(texture), room_data(room_data)
{

}

TileMap::~TileMap()
{

}

void TileMap::render()
{
	/*
	for (std::vector<TileData*> tiles_ligne : room_data->getTileMapData().data) {

		
		for (TileData* tile : tiles_ligne) {

			if (tile->nb_img != -1) {
				SDL_Rect srcrect;
				SDL_Rect dstrect;

				srcrect.x = (tile->nb_img % 30) * sprite_size.x;
				srcrect.y = (tile->nb_img / 30) * sprite_size.y;
				srcrect.h = sprite_size.x;
				srcrect.w = sprite_size.y;

				dstrect.x = gameObject->getWorldPosition().x + (tile->position_grid.x * sprite_size.x * gameObject->getWorldScale().x);
				dstrect.y = gameObject->getWorldPosition().y + (tile->position_grid.y * sprite_size.y * gameObject->getWorldScale().y);

				dstrect.h = sprite_size.x * gameObject->getWorldScale().x;
				dstrect.w = sprite_size.y * gameObject->getWorldScale().y;

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
	for (std::vector<TileData*> tiles_ligne : room_data->getTileMapData().data) {

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
	return sprite_size;
}

Room * TileMap::getRoomData()
{
	return room_data;
}
