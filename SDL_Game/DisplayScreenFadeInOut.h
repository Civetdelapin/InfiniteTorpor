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

	DisplayScreenFadeInOut(GameObject* gameObject);
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

	State stateFading = Over;

	SDL_Texture* blackTexture;

	float alpha = 255;

	SDL_Rect sourceRect;
	SDL_Rect destRect;
};

