#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Room.h"
#include "TileMap.h"
#include "TileMapCollider.h"
#include "RoomBehavior.h"
#include "SpriteRenderer.h"
#include "SlimPrefab.h"
#include "GoblinPrefab.h"
#include "MinotaurPrefab.h"
#include "SnakePrefab.h"
#include "GameManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

struct RoomDataStruct {

	TileMapData* tileMapData;
	std::vector<SDL_Texture*> roomTextures;

	~RoomDataStruct();

	std::vector<OwnMathFuncs::Vector2> doorsPossible;
};

class GenerateLevel : public Renderer, public Component
{
public:
	GenerateLevel(GameObject * gameObject);
	~GenerateLevel();


	//---------- WORLD CONST ------------
	static const int WORLD_GRID_SIZE_X = 10;
	static const int WORLD_GRID_SIZE_Y = 10;

	static const int NUMBER_OF_ROOMS = 5;
	//-----------------------------------

	//----------- ROOM CONST -------------
	static const int ROOM_GRID_SIZE_X = 32;
	static const int ROOM_GRID_SIZE_Y = 20;

	static const int ROOM_NB_TILE_DOOR_X = 2;
	static const int ROOM_NB_TILE_DOOR_Y = 2;

	static const int ROOM_NO_DOOR_OFFSET_X = 2;
	static const int ROOM_NO_DOOR_OFFSET_Y = 4;

	static const int SPAWN_OFFSET_X = 10;
	static const int SPAWN_OFFSET_Y = 10;
	//------------------------------------

	static const OwnMathFuncs::Vector2 tileSize;

	int getCurrentFloor();

	void playerNextFloor();
	void generateNewGame();

	void start();
	void render();
	void clean();

	void cleanGeneratedData();

private:

	
	//------ GENERATED DATA --------

	std::vector<OwnMathFuncs::Vector2> posTaken;
	Room* rooms[WORLD_GRID_SIZE_X][WORLD_GRID_SIZE_Y];
	std::vector<Room*> roomsVector;

	std::vector<GameObject*> roomPrefabs;
	//---------------------------


	//---- LOADED DATA --------

	RoomDataStruct* startingRoom;
	RoomDataStruct* endingRoom;

	std::vector<RoomDataStruct*> roomDataStructs;

	std::vector<SDL_Texture*> noDoorTextures;

	std::vector<std::vector<SDL_Texture*>> openDoorTextures;
	std::vector<std::vector<SDL_Texture*>> closeDoorTextures;

	SDL_Texture* tile_map_texture;
	//---------------------------

	int curFloor = 0;
	int seed = 500;

	int minEnemy = 2;
	int maxEnemy = 3;

	float nbEnemyMultiplicator = 1.025f;
	float timeEnemyMultiplicator = 0.98f;

	float startNbEnemyMultiplicator;
	float startTimeEnemyMultiplicator;

	void loadRoomsFromFiles();
	void generateLevel();

	int getNumberOfNeighbours(OwnMathFuncs::Vector2 room_pos);

	void readCSV(const char* file_path, TileMapData* tileMapData);
	void readCSVCollider(const char* file_path, TileMapData* tileMapData);
	void readCSVSpawner(const char* file_path, TileMapData* tileMapData);
	void loadRoomDataStruct(std::string room_name, RoomDataStruct* roomDataStruct);

	OwnMathFuncs::Vector2 getNewPos();

	

	int convDoorPosToIndex(OwnMathFuncs::Vector2 pos);
	OwnMathFuncs::Vector2 convIndexToDoorPos(int index);
};

