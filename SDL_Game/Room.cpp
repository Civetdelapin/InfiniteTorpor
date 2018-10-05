#include "Room.h"

Room::Room(OwnMathFuncs::Vector2 grid_pos) : grid_pos(grid_pos)
{

}

Room::~Room()
{

}

OwnMathFuncs::Vector2 Room::getGridPos()
{
	return grid_pos;
}

void Room::setRoomType(RoomType value)
{
	room_type = value;
}

Room::RoomType Room::getRoomType()
{
	return room_type;
}

void Room::addDoor(OwnMathFuncs::Vector2 value)
{
	doors.push_back(value);
}

std::vector<OwnMathFuncs::Vector2> Room::getDoors()
{
	return doors;
}
