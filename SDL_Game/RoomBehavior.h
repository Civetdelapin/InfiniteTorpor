#pragma once
#include "Component.h"
#include "Room.h"
#include "Renderer.h"
#include "EnemyBasicBehavior.h"

class GameManager;

class RoomBehavior : public Component
{
public:
	RoomBehavior(GameObject* gameObject, Room* roomData);
	~RoomBehavior();

	enum RoomState { NotOver, Active, Over };

	void start();
	void update();


	void clean();

	Room* getRoomData();

private:
	Room* roomData;

	void playerStartRoom();
	void playerEndRoom();

	void setDoorsCollider(bool value);
	void setDoors(bool value);

	void spawnEnemy();

	GameObject* player;

	RoomState state = NotOver;
	BoxCollider* endHitbox;

	GameManager* gameManager;

	float timeLeft;
};

