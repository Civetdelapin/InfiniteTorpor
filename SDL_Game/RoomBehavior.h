#pragma once
#include "Component.h"
#include "Room.h"
#include "Renderer.h"

class RoomBehavior : public Component, public Renderer
{
public:
	RoomBehavior(GameObject* game_object, Room* room_data);
	~RoomBehavior();

	void start();
	void update();
	void render();

	void clean();

	Room* getRoomData();

private:
	Room* room_data;
};

