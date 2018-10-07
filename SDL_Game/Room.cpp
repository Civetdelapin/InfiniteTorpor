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

void Room::setTileMapData(TileMapData value)
{
	tile_map_data = value;
}

TileMapData Room::getTileMapData()
{
	return tile_map_data;
}


TileData::TileData() : is_collider(false) {
}



TileData* TileMapData::getTile(int x, int y)
{
	if (y >= 0 && y < data.size()) {
		if (x >= 0 && x < data[y].size()) {
			
			return data[y][x];
		}
	}

	return nullptr;
}

