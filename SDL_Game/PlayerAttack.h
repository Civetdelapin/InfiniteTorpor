#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "PlayerController.h"
#include "VelocityBody.h"

class PlayerAttack : public Component
{
public:
	PlayerAttack(GameObject* game_object, BoxCollider* box_collider_attack, BoxCollider* box_coolider_attack_up, BoxCollider* box_collider_attack_corner,PlayerController* player_controller, VelocityBody* velocity_body);
	~PlayerAttack();

	enum State { attacking, ready_attack, between_attack, cant_attack };

	void start();
	void update();
	void clean();

	const float time_attack_up = 0.15;
	const float time_attack_cd = 0.5;
	const float time_attack_cancel_combo = 1;
	const int nb_combo_max = 3;

	const float attack_dmg[3] = {8, 12, 15};
	const float time_enemy_stun = 0.5f;

	const float velocity_attack = 200;

	
private:
	BoxCollider * box_collider_attack;
	BoxCollider* box_coolider_attack_up;
	BoxCollider* box_collider_attack_corner;

	PlayerController* player_controller;
	VelocityBody* velocity_body;
	PlayerBehavior* player_stat;

	std::vector<GameObject*> game_objects_touched;
	OwnMathFuncs::Vector2 normalizeDirection = { 1, 0 };

	State state = ready_attack;

	float timeLeft;
	float timeLeft_cancel_combo;

	bool button_pressed = false;

	int nb_combo = 0;

	float box_collider_attack_up_down_offset;
	float box_collider_attack_corner_offset;

	void manageNormalizeDirection();
	void manageAttackButton();
	void attackButtonPressed();

	void cancelAttackColliders();
	void activeAttackColliders();

	BoxCollider* getActiveCollider();
};

