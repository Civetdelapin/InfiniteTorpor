#pragma once
#include "Component.h"
class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject* game_object, std::string img_path, OwnMathFuncs::Vector2* sprite_size = nullptr);
	~SpriteRenderer();

	int img_sizeX = 30;
	int img_sizeY = 30;

	int sprite_sizeX = 30;
	int sprite_sizeY = 30;

	void render();
	void clean();

	SDL_Rect srcrect;
	SDL_Rect dstrect;

protected:
	SDL_Texture * texture;
	
};

