#include "Enemy.h"

Enemy::Enemy(std::string img_path, OwnMathFuncs::Vector2* sprite_size) : GameObject()
{
	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, img_path, sprite_size);

	BoxCollider* boxCollider = new BoxCollider(this);
	boxCollider->offset = { 0, 14 };
	boxCollider->size = { 10, 6 };
	boxCollider->is_trigger = true;

	tag = "Enemy";
	local_scale = { 3, 3 };
	VelocityBody* velocityBody = new VelocityBody(this);


	//Creation of child
	GameObject* game_object_child = new GameObject();

	BoxCollider* boxColliderHitBox = new BoxCollider(game_object_child); 
	boxColliderHitBox->offset = { 0, 10 };
	boxColliderHitBox->size = { 12, 10};
	boxColliderHitBox->collision_layer = 5;

	game_object_child->tag = "Enemy";
	addGameObject(game_object_child);

}


Enemy::~Enemy()
{
}
