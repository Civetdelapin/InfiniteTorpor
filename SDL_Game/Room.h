#pragma once
#include "OwnMathFuncs.h"
#include <SDL.h>
#include <iostream>
#include "BoxCollider.h"

struct TileData {
	OwnMathFuncs::Vector2 positionGrid = { 0, 0 };
	int nbImg;
	bool collider = false;
	bool spawner = false;

	TileData();
	~TileData();
};

struct TileMapData {

	std::vector<std::vector<TileData*>> data;
	std::vector<TileData*> spawners;
	
	OwnMathFuncs::Vector2 spriteSize = { 16, 16 };

	~TileMapData();

	TileData* getTile(int x, int y);
};

struct Door {

	OwnMathFuncs::Vector2 doorPosition = { 0, 0 };

	BoxCollider* boxColliderTrigger;
	BoxCollider* boxCollider;

	GameObject* openDoor;
	GameObject* closeDoor;

	~Door();
};

class Room
{

public:

	enum RoomType { StartRoom, NormalRoom, EndRoom};

	Room(OwnMathFuncs::Vector2 gridPosition);
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

	RoomType roomType = NormalRoom;

	std::vector<GameObject*> enemiesWaves;

	std::vector<Door*> doors;
	TileMapData* tileMapData;

	OwnMathFuncs::Vector2 gridPosition = { 0 ,0 };
};

