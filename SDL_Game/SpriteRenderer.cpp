#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(GameObject* gameObject, std::string img_path, OwnMathFuncs::Vector2 sprite_size) : Renderer(this), Component(gameObject),  sprite_size(sprite_size)
{

	int x, y = 0;
	texture = TextureManager::LoadTexture(img_path.c_str(), x, y);

	img_size.x = x;
	img_size.y = y;
}

SpriteRenderer::SpriteRenderer(GameObject * gameObject, SDL_Texture * texture, bool must_destroy_text) : Renderer(this), Component(gameObject), texture(texture), must_destroy_text(must_destroy_text)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	img_size.x = w;
	img_size.y = h;

	sprite_size.x = w;
	sprite_size.y = h;
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::render()
{
	
	if (texture != nullptr) {

		dstrect.x = (gameObject->getWorldPosition().x - (sprite_size.x / 2) * fabs(gameObject->getWorldScale().x));
		dstrect.y = (gameObject->getWorldPosition().y - (sprite_size.y / 2) * fabs(gameObject->getWorldScale().y));

		dstrect.w = sprite_size.x * fabs(gameObject->getWorldScale().x);
		dstrect.h = sprite_size.y * fabs(gameObject->getWorldScale().y);

		srcrect.w = sprite_size.x;
		srcrect.h = sprite_size.y;

		SDL_RendererFlip flip = is_looking_right ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
		if (gameObject->getWorldScale().x < 0) {
			flip = is_looking_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}

		TextureManager::DrawTexture(texture, srcrect, dstrect, flip);
	}

}

void SpriteRenderer::clean()
{
	if (must_destroy_text) {
		SDL_DestroyTexture(texture);
	}
	
	Renderer::clean();
	Component::clean();
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
	return {getGameObject()->getWorldPosition().x, getGameObject()->getWorldPosition().y + sprite_size.y * fabs(gameObject->getWorldScale().y) };
}
