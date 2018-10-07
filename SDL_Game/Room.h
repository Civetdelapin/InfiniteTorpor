#pragma once
#include "OwnMathFuncs.h"
#include <iostream>

struct TileData {
	OwnMathFuncs::Vector2 position_grid = { 0, 0 };
	int nb_img;
	bool is_collider = false;

	TileData();
};

struct TileMapData {

	std::vector<std::vector<TileData*>> data;
	OwnMathFuncs::Vector2 sprite_size = { 16, 16 };

	TileData* getTile(int x, int y);
};

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

	void setTileMapData(TileMapData value);
	TileMapData getTileMapData();

private:

	RoomType room_type = NormalRoom;

	std::vector<OwnMathFuncs::Vector2> doors;
	TileMapData tile_map_data;

	OwnMathFuncs::Vector2 grid_pos = { 0 ,0 };
};

