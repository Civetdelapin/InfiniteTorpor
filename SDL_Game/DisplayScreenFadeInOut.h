#pragma once
#include "Renderer.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "TextureManager.h"

class DisplayScreenFadeInOut : public Renderer, public Component
{
public:

	const enum State { FadingOut, FadingIn, Over };

	DisplayScreenFadeInOut(GameObject* game_object);
	~DisplayScreenFadeInOut();
	
	void start();
	void update();
	void render();

	void clean();

	void setState(State value);

	void setAlpha(float value);

private:

	float time_passed;

	State state_fading = Over;

	SDL_Texture* black_texture;

	float alpha = 255;

	float time_alpha_out = 1.0f;
	float time_alpha_in = 0.5f;

	SDL_Rect src_rect;
	SDL_Rect dest_rect;
};

