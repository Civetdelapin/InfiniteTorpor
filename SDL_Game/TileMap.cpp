#include "TileMap.h"

TileMap::TileMap(GameObject * game_object, OwnMathFuncs::Vector2 sprite_size, Room * room_data, SDL_Texture * texture) : Component(game_object), Renderer(this), sprite_size(sprite_size), texture(texture), room_data(room_data)
{

}

TileMap::~TileMap()
{

}

void TileMap::render()
{
	
	for (std::vector<TileData*> tiles_ligne : room_data->getTileMapData().data) {

		
		for (TileData* tile : tiles_ligne) {

			if (tile->nb_img != -1) {
				SDL_Rect srcrect;
				SDL_Rect dstrect;

				srcrect.x = (tile->nb_img % 30) * sprite_size.x;
				srcrect.y = (tile->nb_img / 30) * sprite_size.y;
				srcrect.h = sprite_size.x;
				srcrect.w = sprite_size.y;

				dstrect.x = game_object->getWorldPosition().x + (tile->position_grid.x * sprite_size.x * game_object->getWorldScale().x);
				dstrect.y = game_object->getWorldPosition().y + (tile->position_grid.y * sprite_size.y * game_object->getWorldScale().y);

				dstrect.h = sprite_size.x * game_object->getWorldScale().x;
				dstrect.w = sprite_size.y * game_object->getWorldScale().y;

				TextureManager::DrawTexture(texture, srcrect, dstrect);

				if (tile->is_collider) {
					TextureManager::DrawRect(dstrect);
				}
			}
		}
	}

}

void TileMap::clean()
{
	for (std::vector<TileData*> tiles_ligne : room_data->getTileMapData().data) {

		for (TileData* tile : tiles_ligne) {
			delete tile;
		}
	}

	Renderer::clean();
	Component::clean();
}

OwnMathFuncs::Vector2 TileMap::getSpriteSize()
{
	return sprite_size;
}

Room * TileMap::getRoomData()
{
	return room_data;
}
