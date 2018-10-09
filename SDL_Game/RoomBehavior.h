#pragma once
#include "Component.h"
#include "Room.h"
#include "Renderer.h"

class RoomBehavior : public Component, public Renderer
{
public:
	RoomBehavior(GameObject* game_object, Room* room_data);
	~RoomBehavior();

	enum RoomState { NotOver, Active, Over };

	void start();
	void update();
	void render();

	void clean();

	Room* getRoomData();

private:
	Room* room_data;

	void playerEnterRoom();
	void playerEndRoom();

	void setDoorsCollider(bool value);

	RoomState state = NotOver;
};

