#include "Room.h"
#include "Game.h"

Room::Room(OwnMathFuncs::Vector2 gridPosition) : gridPosition(gridPosition)
{

}

Room::~Room()
{
	delete tileMapData;

	for (GameObject* enemy : enemiesWaves) {
		Game::instance()->destroyGameObject(enemy);
	}
	enemiesWaves.clear();

	for (Door* door : doors) {
		delete door;
	}
}

OwnMathFuncs::Vector2 Room::getGridPos()
{
	return gridPosition;
}

void Room::setRoomType(RoomType value)
{
	roomType = value;
}

Room::RoomType Room::getRoomType()
{
	return roomType;
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
			newTile->collider = tile->collider;
			newTile->spawner = tile->spawner;

			newTile->nbImg = tile->nbImg;
			newTile->positionGrid = tile->positionGrid;

			if (tile->spawner) {
				newTileMapData->spawners.push_back(newTile);
			}

			new_vec.push_back(newTile);
		}

		newTileMapData->data.push_back(new_vec);
	}

	tileMapData = newTileMapData;
}

TileMapData* Room::getTileMapData()
{
	return tileMapData;
}

void Room::addEnemy(GameObject * gameObject)
{
	enemiesWaves.push_back(gameObject);
}

std::vector<GameObject*> & Room::getEnemiesWaves()
{
	return enemiesWaves;
}


TileData::TileData() : collider(false) {

}

TileData::~TileData()
{
}



TileMapData::~TileMapData()
{
	for (std::vector<TileData*> tiles_ligne : data) {

		for (TileData* tile : tiles_ligne) {
			delete tile;
		}
	}

	spawners.clear();
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

Door::~Door()
{
}
