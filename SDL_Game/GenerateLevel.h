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

#include <iostream>
#include <fstream>
#include <sstream>

class GenerateLevel : public Renderer, public Component
{
public:
	GenerateLevel(GameObject * game_object);
	~GenerateLevel();

	static const int world_grid_size_x = 10;
	static const int world_grid_size_y = 10;
	static const int number_of_rooms = 1;
	
	static const int room_grid_size_x = 32;
	static const int room_grid_size_y = 20;

	static const OwnMathFuncs::Vector2 tile_size;

	void start();
	void render();
	void clean();

private:

	std::vector<TileMapData*> vect_tile_map_data;
	std::vector<SDL_Texture*> vect_room_texture;

	std::vector<OwnMathFuncs::Vector2> pos_taken;
	Room* rooms[world_grid_size_x][world_grid_size_y];
	std::vector<Room*> rooms_vector;

	int seed = 500;

	Room* start_room;
	Room* end_room;

	void loadRoomsFromFiles();
	void generateLevel();

	int getNumberOfNeighbours(OwnMathFuncs::Vector2 room_pos);

	void readCSV(const char* file_path, TileMapData* tile_map_data);
	void readCSVCollider(const char* file_path, TileMapData* tile_map_data);

	OwnMathFuncs::Vector2 getNewPos();

	SDL_Texture* tile_map_texture;
};

