#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(GameObject* game_object, std::string img_path, OwnMathFuncs::Vector2 sprite_size) : Component(game_object), sprite_size(sprite_size)
{

	int x, y = 0;
	texture = TextureManager::LoadTexture(img_path.c_str(), x, y);

	img_size.x = x;
	img_size.y = y;
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::render()
{
	
	if (texture != nullptr) {

		dstrect.x = (game_object->getWorldPosition().x - (sprite_size.x / 2) * fabs(game_object->getWorldScale().x));
		dstrect.y = (game_object->getWorldPosition().y - (sprite_size.y / 2) * fabs(game_object->getWorldScale().y));

		dstrect.w = sprite_size.x * fabs(game_object->getWorldScale().x);
		dstrect.h = sprite_size.y * fabs(game_object->getWorldScale().y);

		srcrect.w = sprite_size.x;
		srcrect.h = sprite_size.y;

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
