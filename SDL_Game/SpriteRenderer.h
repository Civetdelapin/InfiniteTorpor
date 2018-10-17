#pragma once
#include "Component.h"
#include "Renderer.h"

class SpriteRenderer : public Component, public Renderer
{
public:
	SpriteRenderer(GameObject* gameObject, std::string img_path, OwnMathFuncs::Vector2 spriteSize);
	SpriteRenderer(GameObject* gameObject, SDL_Texture* texture, bool mustDestroyTexture);

	~SpriteRenderer();

	void render();
	void clean();

	OwnMathFuncs::Vector2 getSpriteSize();

	SDL_Rect getDestRect();

	void setSourceRect(SDL_Rect rect);

	void setAlpha(float value);
	void setIsLookingRight(bool value);

	OwnMathFuncs::Vector2 getBottomPosition();

private:
	SDL_Texture * texture;
	
	OwnMathFuncs::Vector2 imgSize = { 30, 30 };
	OwnMathFuncs::Vector2 spriteSize = { 30, 30 };

	float alpha = 255;

	bool lookingRight = true;

	bool mustDestroyTexture = true;

	SDL_Rect srcrect;
	SDL_Rect dstrect;
};

