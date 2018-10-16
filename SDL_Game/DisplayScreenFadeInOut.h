#pragma once
#include "Renderer.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "TextureManager.h"

class DisplayScreenFadeInOut : public Renderer, public Component
{
public:

	const enum State { FadingOut, FadingIn, Over };

	static const float TIME_FADE_DEAD;
	static const float TIME_FADE_TRANSITION;

	DisplayScreenFadeInOut(GameObject* game_object);
	~DisplayScreenFadeInOut();
	
	void start();
	void update();
	void render();

	void clean();

	void setState(State value, float time = 0);

	void setAlpha(float value);

private:

	float timeLeft;
	float timeToFade;

	State state_fading = Over;

	SDL_Texture* black_texture;

	float alpha = 255;

	SDL_Rect src_rect;
	SDL_Rect dest_rect;
};

