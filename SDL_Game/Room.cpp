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

void Room::addDoor(Door* value)
{
	doors.push_back(value);
}

std::vector<Door*> Room::getDoors()
{
	return doors;
}

void Room::setTileMapData(TileMapData* value)
{
	
	TileMapData* newTileMapData = new TileMapData();
	for (std::vector<TileData*> tiles_ligne : value->data) {
		std::vector<TileData*> new_vec;

		for (TileData* tile : tiles_ligne) {
			
			TileData* newTile = new TileData();
			newTile->is_collider = tile->is_collider;
			newTile->nb_img = tile->nb_img;
			newTile->position_grid = tile->position_grid;

			new_vec.push_back(newTile);
		}

		newTileMapData->data.push_back(new_vec);
	}

	tile_map_data = newTileMapData;
}

TileMapData* Room::getTileMapData()
{
	return tile_map_data;
}

void Room::addEnemy(GameObject * game_object)
{
	enemies_waves.push_back(game_object);
}

std::vector<GameObject*> & Room::getEnemiesWaves()
{
	return enemies_waves;
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

