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

void SpriteRenderer::render(float camera_pos_x, float camera_pos_y)
{
	
	if (texture != nullptr) {

		dstrect.x = (game_object->position.x - camera_pos_x - (sprite_sizeX / 2) * fabs(game_object->scale.x));
		dstrect.y = (game_object->position.y - camera_pos_y - (sprite_sizeY / 2) * fabs(game_object->scale.y));

		dstrect.w = sprite_sizeX * fabs(game_object->scale.x);
		dstrect.h = sprite_sizeY * fabs(game_object->scale.y);

		srcrect.w = sprite_sizeX;
		srcrect.h = sprite_sizeY;

		SDL_RendererFlip flip = SDL_FLIP_NONE;
		if (game_object->scale.x < 0) {
			flip = SDL_FLIP_HORIZONTAL;
		}

		TextureManager::DrawTexture(texture, srcrect, dstrect, flip);
	}

	Component::render(camera_pos_x, camera_pos_y);
}

void SpriteRenderer::clean()
{
	SDL_DestroyTexture(texture);
	Component::clean();
}
