#pragma once
#include "Component.h"
#include "Room.h"
#include "Renderer.h"
#include "EnemyBasicBehavior.h"

class GenerateLevel;

class RoomBehavior : public Component
{
public:
	RoomBehavior(GameObject* game_object, Room* room_data);
	~RoomBehavior();

	enum RoomState { NotOver, Active, Over };

	void start();
	void update();


	void clean();

	Room* getRoomData();

private:
	Room* room_data;

	void playerStartRoom();
	void playerEndRoom();

	void setDoorsCollider(bool value);
	void setDoors(bool value);

	void spawnEnemy();

	GameObject* player;

	RoomState state = NotOver;
	GenerateLevel* generate_level;
	BoxCollider* end_hitbox;

	float time_passed;
};

