#pragma once
#include "OwnMathFuncs.h"
#include <SDL.h>
#include <iostream>
#include "BoxCollider.h"

struct TileData {
	OwnMathFuncs::Vector2 position_grid = { 0, 0 };
	int nb_img;
	bool is_collider = false;
	bool is_spawner = false;

	TileData();
};

struct TileMapData {

	std::vector<std::vector<TileData*>> data;
	std::vector<TileData*> spawners;
	
	OwnMathFuncs::Vector2 sprite_size = { 16, 16 };

	TileData* getTile(int x, int y);
};

struct Door {

	OwnMathFuncs::Vector2 door_position = { 0, 0 };

	BoxCollider* box_collider_trigger;
	BoxCollider* box_collider;

	GameObject* open_door;
	GameObject* close_door;
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

	void addDoor(Door* value);
	std::vector<Door*> getDoors();

	void setTileMapData(TileMapData* value);
	TileMapData* getTileMapData();

	void addEnemy(GameObject* gameObject);
	std::vector<GameObject*> & getEnemiesWaves();


private:

	RoomType room_type = NormalRoom;

	std::vector<GameObject*> enemies_waves;

	std::vector<Door*> doors;
	TileMapData* tileMapData;

	OwnMathFuncs::Vector2 grid_pos = { 0 ,0 };
};

