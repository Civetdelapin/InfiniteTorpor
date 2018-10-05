#pragma once
#include "OwnMathFuncs.h"
class Room
{

public:

	enum RoomType { StartRoom, NormalRoom, EndRoom};

	Room(OwnMathFuncs::Vector2 grid_pos);
	~Room();

	OwnMathFuncs::Vector2 getGridPos();

	void setRoomType(RoomType value);
	RoomType getRoomType();

	void addDoor(OwnMathFuncs::Vector2 value);
	std::vector<OwnMathFuncs::Vector2> getDoors();

private:

	RoomType room_type = NormalRoom;

	std::vector<OwnMathFuncs::Vector2> doors;

	OwnMathFuncs::Vector2 grid_pos = { 0 ,0 };
};

