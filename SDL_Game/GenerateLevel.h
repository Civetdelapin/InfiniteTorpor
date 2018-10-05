#pragma once
#include "Renderer.h"
#include "Room.h"

class GenerateLevel : public Renderer
{
public:
	GenerateLevel(GameObject * game_object);
	~GenerateLevel();

	static const int world_grid_size_x = 10;
	static const int world_grid_size_y = 10;
	static const int number_of_rooms = 10;
	
	void start();
	void render();
	void clean();

private:
	std::vector<OwnMathFuncs::Vector2> pos_taken;

	Room* rooms[world_grid_size_x][world_grid_size_y];
	std::vector<Room*> rooms_vector;

	int seed = 500;

	Room* start_room;
	Room* end_room;

	void generateLevel();

	int getNumberOfNeighbours(OwnMathFuncs::Vector2 room_pos);

	OwnMathFuncs::Vector2 getNewPos();
};

