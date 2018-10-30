#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(GameObject* gameObject, std::string img_path, OwnMathFuncs::Vector2 spriteSize) : Renderer(this), Component(gameObject),  spriteSize(spriteSize)
{

	int x, y = 0;
	texture = TextureManager::LoadTexture(img_path.c_str(), x, y);

	imgSize.x = x;
	imgSize.y = y;
}

SpriteRenderer::SpriteRenderer(GameObject * gameObject, SDL_Texture * texture, bool mustDestroyTexture) : Renderer(this), Component(gameObject), texture(texture), mustDestroyTexture(mustDestroyTexture)
{
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	imgSize.x = w;
	imgSize.y = h;

	spriteSize.x = w;
	spriteSize.y = h;
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::render()
{
	
	if (texture != nullptr) {

		dstrect.x = (gameObject->getWorldPosition().x - ((spriteSize.x / 2) + offset.x) * fabs(gameObject->getWorldScale().x));
		dstrect.y = (gameObject->getWorldPosition().y - ((spriteSize.y / 2) + offset.y) * fabs(gameObject->getWorldScale().y));

		dstrect.w = spriteSize.x * fabs(gameObject->getWorldScale().x);
		dstrect.h = spriteSize.y * fabs(gameObject->getWorldScale().y);

		srcrect.w = spriteSize.x;
		srcrect.h = spriteSize.y;

		SDL_RendererFlip flip = lookingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
		if (gameObject->getWorldScale().x < 0) {
			flip = lookingRight ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}

		TextureManager::DrawTexture(texture, srcrect, dstrect, flip);
	}

}

void SpriteRenderer::clean()
{
	if (mustDestroyTexture) {
		SDL_DestroyTexture(texture);
	}
	
	Renderer::clean();
	Component::clean();
}

OwnMathFuncs::Vector2 SpriteRenderer::getSpriteSize()
{
	return spriteSize;
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
	lookingRight = value;
}

void SpriteRenderer::setOffset(OwnMathFuncs::Vector2 value)
{
	offset = value;
}

OwnMathFuncs::Vector2 SpriteRenderer::getBottomPosition()
{
	return {getGameObject()->getWorldPosition().x, getGameObject()->getWorldPosition().y + spriteSize.y * fabs(gameObject->getWorldScale().y) };
}
