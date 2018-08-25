#include "Player.h"


Player::Player(std::string img_path, OwnMathFuncs::Vector2* sprite_size) :  GameObject()
{
	PlayerController* playerController = new PlayerController(this);
	addComponent(playerController);

	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, img_path, sprite_size);
	addComponent(spriteRenderer);

	scale.x = 3;
	scale.y = 3;
}


Player::~Player()
{
}
