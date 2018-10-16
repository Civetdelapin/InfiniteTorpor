#include "DisplayScreenFadeInOut.h"
#include "Game.h"

const float DisplayScreenFadeInOut::TIME_FADE_DEAD = 0.5f;
const float DisplayScreenFadeInOut::TIME_FADE_TRANSITION = 1.0f;

DisplayScreenFadeInOut::DisplayScreenFadeInOut(GameObject * game_object) : Component(game_object), Renderer(this)
{
	black_texture = TextureManager::LoadTexture("img/ui/black_square.png", src_rect.w, src_rect.h);

	src_rect.x = 0;
	src_rect.y = 0;

	dest_rect.x = 0;
	dest_rect.y = 0;
	dest_rect.w = Game::instance()->getScreenSize().x;
	dest_rect.h = Game::instance()->getScreenSize().y;

	setLayer(RendererManager::MAX_LAYER - 1);

	setAlpha(SDL_ALPHA_OPAQUE);
}

DisplayScreenFadeInOut::~DisplayScreenFadeInOut()
{

}

void DisplayScreenFadeInOut::start()
{

}

void DisplayScreenFadeInOut::update()
{
	if (state_fading == FadingIn) {
		float alpha_value = SDL_ALPHA_OPAQUE - ( (timeLeft / timeToFade) * SDL_ALPHA_OPAQUE) ;
		setAlpha(alpha_value);

		std::cout << alpha_value << std::endl;

		if (timeLeft <= 0) {
			setState(Over);
		}
	}
	else if (state_fading == FadingOut) {
		float alpha_value = (timeLeft / timeToFade) * SDL_ALPHA_OPAQUE;
		setAlpha(alpha_value);

		if (timeLeft <= 0) {
			setState(Over);
		}
	}
	std::cout << timeLeft << std::endl;

	timeLeft -= Time::deltaTime;
}


void DisplayScreenFadeInOut::render()
{
	dest_rect.w = Game::instance()->getScreenSize().x;
	dest_rect.h = Game::instance()->getScreenSize().y;

	TextureManager::DrawTexture(black_texture, src_rect, dest_rect, SDL_FLIP_NONE, false);
}

void DisplayScreenFadeInOut::clean()
{
	SDL_DestroyTexture(black_texture);

	Renderer::clean();
	Component::clean();
}

void DisplayScreenFadeInOut::setState(State value, float time)
{
	state_fading = value;

	timeLeft = time;
	timeToFade = time;
}

void DisplayScreenFadeInOut::setAlpha(float value)
{
	alpha = value;

	SDL_SetTextureAlphaMod(black_texture, alpha);
}
