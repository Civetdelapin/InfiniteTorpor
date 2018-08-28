#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(GameObject* game_object, std::string img_path, OwnMathFuncs::Vector2* sprite_size) : Component(game_object)
{

	texture = TextureManager::LoadTexture(img_path.c_str(), img_sizeX, img_sizeY);

	if (sprite_size == nullptr) {
		sprite_sizeX = img_sizeX;
		sprite_sizeY = img_sizeY;
	}
	else {
		sprite_sizeX = sprite_size->x;
		sprite_sizeY = sprite_size->y;
	}
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::render()
{
	
	if (texture != nullptr) {

		dstrect.x = (game_object->getWorldPosition().x - (sprite_sizeX / 2) * fabs(game_object->getWorldScale().x));
		dstrect.y = (game_object->getWorldPosition().y - (sprite_sizeY / 2) * fabs(game_object->getWorldScale().y));

		dstrect.w = sprite_sizeX * fabs(game_object->getWorldScale().x);
		dstrect.h = sprite_sizeY * fabs(game_object->getWorldScale().y);

		srcrect.w = sprite_sizeX;
		srcrect.h = sprite_sizeY;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		if (game_object->getWorldScale().x < 0) {
			flip = SDL_FLIP_HORIZONTAL;
		}

		TextureManager::DrawTexture(texture, srcrect, dstrect, flip);
	}

	Component::render();
}

void SpriteRenderer::clean()
{
	SDL_DestroyTexture(texture);
	Component::clean();
}
