#pragma once
#include "Renderer.h"
#include "PlayerBehavior.h"
#include "Component.h"

class DisplayPlayerScore : public Renderer, public Component
{
public:
	DisplayPlayerScore(GameObject* gameObject);
	~DisplayPlayerScore();

	void start();
	void update();
	void render();

	void clean();

private:
	PlayerBehavior * playerBehavior;
	TTF_Font* ttf_Font;

	float fontSize = 40;
};

