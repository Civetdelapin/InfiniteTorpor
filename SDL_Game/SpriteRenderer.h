#pragma once
#include "Component.h"
class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject* game_object, std::string img_path, OwnMathFuncs::Vector2 sprite_size);
	~SpriteRenderer();

	void render();
	void clean();

	OwnMathFuncs::Vector2 getSpriteSize();
	void setSourceRect(SDL_Rect rect);

	void setAlpha(float value);
	void setIsLookingRight(bool value);

private:
	SDL_Texture * texture;
	
	OwnMathFuncs::Vector2 img_size = { 30, 30 };
	OwnMathFuncs::Vector2 sprite_size = { 30, 30 };

	float alpha = 255;

	bool is_looking_right = true;

	SDL_Rect srcrect;
	SDL_Rect dstrect;
};

