#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "PlayerController.h"
#include "VelocityBody.h"

class PlayerAttack : public Component
{
public:
	PlayerAttack(GameObject* gameObject, BoxCollider* boxColliderAttack, BoxCollider* boxColliderAttackUp, BoxCollider* boxColliderAttackCorner,PlayerController* playerController, VelocityBody* velocityBody);
	~PlayerAttack();

	enum State { attacking, ready_attack, between_attack, cant_attack };

	void start();
	void update();
	void clean();

	
private:

	float timeAttackUp = 0.15;
	float timeAttackCd = 0.5;
	float timeAttackCancelCombo = 1;
	int nbComboMax = 3;

	float attackDamage[3] = { 8, 12, 15 };
	float timeEnemyStun = 0.5f;

	float velocityAttack = 200;

	BoxCollider * boxColliderAttack;
	BoxCollider* boxColliderAttackUp;
	BoxCollider* boxColliderAttackCorner;

	PlayerController* playerController;
	VelocityBody* velocityBody;
	PlayerBehavior* playerBehavior;

	std::vector<GameObject*> gameObjectsTouched;
	OwnMathFuncs::Vector2 normalizeDirection = { 1, 0 };

	State state = ready_attack;

	float timeLeft;
	float timeLeftCancelCombo;

	bool button_pressed = false;

	int nb_combo = 0;

	float boxColliderAttackUpDownOffset;
	float boxColliderAttackCornerOffset;

	void manageNormalizeDirection();
	void manageAttackButton();
	void attackButtonPressed();

	void cancelAttackColliders();
	void activeAttackColliders();

	BoxCollider* getActiveCollider();
};

