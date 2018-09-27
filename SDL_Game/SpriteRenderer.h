#pragma once
#include "Component.h"
class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject* game_object, std::string img_path, OwnMathFuncs::Vector2 sprite_size);
	~SpriteRenderer();

	OwnMathFuncs::Vector2 img_size = { 30, 30 };

	OwnMathFuncs::Vector2 sprite_size = { 30, 30 };

	void render();
	void clean();

	SDL_Rect srcrect;
	SDL_Rect dstrect;

protected:
	SDL_Texture * texture;
	
};

