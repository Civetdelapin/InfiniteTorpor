#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "PlayerController.h"
#include "VelocityBody.h"

class PlayerAttack : public Component
{
public:
	PlayerAttack(GameObject* game_object, BoxCollider* box_collider_attack, PlayerController* player_controller, VelocityBody* velocity_body);
	~PlayerAttack();

	void update();

	float time_attack_up = 0.25;
	float time_attack_cd = 1;
	float time_attack_cancel_combo = 0.5;
	int nb_combo_max = 3;

	enum State { attacking, ready_attack, between_attack, cant_attack};

	float velocity_attack = 3000;


private:
	BoxCollider * box_collider_attack;
	PlayerController* player_controller;
	VelocityBody* velocity_body;

	std::vector<GameObject*> game_objects_touched;
	OwnMathFuncs::Vector2 normalizeDirection = { 1, 0 };

	State state = ready_attack;

	float time_passed;
	float time_passed_cancel_combo;

	bool button_pressed = false;

	int nb_combo = 0;

	void manageNormalizeDirection();
	void manageAttackButton();
	void attackButtonPressed();

};

