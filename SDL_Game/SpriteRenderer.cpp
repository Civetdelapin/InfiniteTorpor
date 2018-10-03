#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(GameObject* game_object, std::string img_path, OwnMathFuncs::Vector2 sprite_size) : Renderer(game_object), sprite_size(sprite_size)
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

		SDL_RendererFlip flip = is_looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
		if (game_object->getWorldScale().x < 0) {
			flip = is_looking_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}

		TextureManager::DrawTexture(texture, srcrect, dstrect, flip);
	}

}

void SpriteRenderer::clean()
{
	SDL_DestroyTexture(texture);
	Renderer::clean();
}

OwnMathFuncs::Vector2 SpriteRenderer::getSpriteSize()
{
	return sprite_size;
}

SDL_Rect SpriteRenderer::getDestRect()
{
	return dstrect;
}

void SpriteRenderer::setSourceRect(SDL_Rect rect)
{
	srcrect = rect;
}

void SpriteRenderer::setAlpha(float value)
{
	alpha = value;

	SDL_SetTextureAlphaMod(texture, alpha);
}

void SpriteRenderer::setIsLookingRight(bool value)
{
	is_looking_right = value;
}

OwnMathFuncs::Vector2 SpriteRenderer::getBottomPosition()
{
	return {getGameObject()->getWorldPosition().x, getGameObject()->getWorldPosition().y + dstrect.h / 2};
}
