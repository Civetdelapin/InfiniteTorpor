#include "Player.h"


Player::Player(OwnMathFuncs::Vector2 init_local_pos) :  GameObject(init_local_pos)
{
	SpriteRenderer* spriteRenderer = new SpriteRenderer(this, "img/player_0.png", { 32, 32 });
	spriteRenderer->setLayer(RendererManager::TOP_DOWN_LAYER);

	SpriteRenderer* spriteRenderer2 = new SpriteRenderer(this, "img/player_1.png", { 54, 41 });
	spriteRenderer2->setLayer(RendererManager::TOP_DOWN_LAYER);
	spriteRenderer2->setActive(false);

	Animator* animator = new Animator(this);
	animator->addSpriteRenderer(spriteRenderer);
	animator->addSpriteRenderer(spriteRenderer2);

	// Creation of Animations
	Animation animIdle;
	animIdle.nbSprites = 10;
	animIdle.speed = 0.3f;
	animIdle.indexY = 0;

	animator->addAnimation(std::pair <std::string, Animation> ("Idle", animIdle));
	
	Animation animWalking;
	animWalking.nbSprites = 10;
	animWalking.speed = 0.1f;
	animWalking.indexY = 2;

	animator->addAnimation(std::pair <std::string, Animation>("Walking", animWalking));
	animator->play("Idle");
	
	Animation animDead;
	animDead.nbSprites = 10;
	animDead.speed = 0.2f;
	animDead.indexY = 4;
	animDead.looping = false;

	animator->addAnimation(std::pair <std::string, Animation>("Dying", animDead));

	Animation animWakeUp;
	animWakeUp.nbSprites = 10;
	animWakeUp.speed = 0.2f;
	animWakeUp.indexY = 4;
	animWakeUp.looping = false;
	animWakeUp.reverse = true;

	animator->addAnimation(std::pair <std::string, Animation>("WakingUp", animWakeUp));

	Animation animDodge;
	animDodge.nbSprites = 8;
	animDodge.speed = 0.075f;
	animDodge.looping = false;
	animDodge.spriteRendererIndex = 1;

	animator->addAnimation(std::pair <std::string, Animation>("Dodge", animDodge));

	BoxCollider* boxCollider = new BoxCollider(this);
	boxCollider->offset = { 1, 14};
	boxCollider->size = { 10, 5.5 };

	VelocityBody* velocityBody = new VelocityBody(this);
	velocityBody->setDrag({ 10, 10 });

	PlayerController* playerController = new PlayerController(this);
	PlayerBehavior* playerBehavior = new PlayerBehavior(this);

	localScale = { 4, 4};
	tag = "Player";

	//Creation of child
	GameObject* game_object_child = new GameObject();

	BoxCollider* boxColliderHitBox = new BoxCollider(game_object_child);
	boxColliderHitBox->offset = { 0, 4 };
	boxColliderHitBox->size = { 10, 22 };
	boxColliderHitBox->setCollisionLayer(10);

	game_object_child->tag = "Player";
	addGameObjectAsChild(game_object_child);

	GameObject* game_object_child_2 = new GameObject();

	BoxCollider* boxColliderHitBoxAttack = new BoxCollider(game_object_child_2);
	boxColliderHitBoxAttack->offset = {12, 0 };
	boxColliderHitBoxAttack->size = { 26, 40};
	boxColliderHitBoxAttack->setCollisionLayer(5);

	BoxCollider* boxColliderHitBoxAttackUpDown = new BoxCollider(game_object_child_2);
	boxColliderHitBoxAttackUpDown->offset = { 0, -16 };
	boxColliderHitBoxAttackUpDown->size = { 40, 26 };
	boxColliderHitBoxAttackUpDown->setCollisionLayer(5);


	BoxCollider* boxColliderHitBoxAttackCorner1 = new BoxCollider(game_object_child_2);
	boxColliderHitBoxAttackCorner1->offset = { 12, -13 };
	boxColliderHitBoxAttackCorner1->size = { 28, 28 };
	boxColliderHitBoxAttackCorner1->setCollisionLayer(5);


	PlayerAttack* player_attack = new PlayerAttack(game_object_child_2, boxColliderHitBoxAttack, boxColliderHitBoxAttackUpDown, boxColliderHitBoxAttackCorner1 ,playerController, velocityBody);

	game_object_child_2->tag = "Player";
	addGameObjectAsChild(game_object_child_2);


	//--------- CREATION OF SHADOW -------------
	
	GameObject* game_object_child_3 = new GameObject({ 0, spriteRenderer->getSpriteSize().y / 2});
	SpriteRenderer* sprite_renderer_2 = new SpriteRenderer(game_object_child_3, "img/dungeon_tileset.png", { 16, 16 });
	sprite_renderer_2->setLayer(4);

	SDL_Rect tempRect;
	tempRect.x = 0 * sprite_renderer_2->getSpriteSize().x;
	tempRect.y = 32 * sprite_renderer_2->getSpriteSize().y;
	sprite_renderer_2->setSourceRect(tempRect);
	addGameObjectAsChild(game_object_child_3);
	
	//------------------------------------------
}


Player::~Player()
{
}
