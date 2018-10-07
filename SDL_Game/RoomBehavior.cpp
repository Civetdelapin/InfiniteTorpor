#include "RoomBehavior.h"



RoomBehavior::RoomBehavior(GameObject * game_object, Room * room_data) : Component(game_object), Renderer(this), room_data(room_data)
{

}

RoomBehavior::~RoomBehavior()
{

}

void RoomBehavior::start()
{

}

void RoomBehavior::update()
{
}

void RoomBehavior::render()
{
	
}

void RoomBehavior::clean()
{

	Renderer::clean();
	Component::clean();
}

Room * RoomBehavior::getRoomData()
{
	return room_data;
}
