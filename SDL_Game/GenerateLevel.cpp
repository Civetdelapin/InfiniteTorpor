#include "GenerateLevel.h"
#include "Game.h"

OwnMathFuncs::Vector2 const GenerateLevel::tileSize = { 16, 16 };

GenerateLevel::GenerateLevel(GameObject * gameObject) : Renderer(this), Component(gameObject)
{
	setLayer(14);
}


GenerateLevel::~GenerateLevel()
{
}

int GenerateLevel::getCurrentFloor()
{
	return curFloor;
}

void GenerateLevel::playerNextFloor()
{
	curFloor++;
	generateLevel();
}

void GenerateLevel::generateNewGame()
{
	curFloor = 0;
	nbEnemyMultiplicator = startNbEnemyMultiplicator;
	timeEnemyMultiplicator = startTimeEnemyMultiplicator;

	generateLevel();
}

void GenerateLevel::start()
{
	srand(seed);

	startNbEnemyMultiplicator = nbEnemyMultiplicator;
	startTimeEnemyMultiplicator = timeEnemyMultiplicator;

	loadRoomsFromFiles(); // We load all the rooms data 
	//generateLevel(); // We create the levels	
}

void GenerateLevel::render()
{
	/*
	const int size = 50;

	//Draw the rects for testing
	for (Room* room : roomsVector) {
		
		SDL_Rect rect;
		rect.w = size;
		rect.h = size;

		rect.x = room->getGridPos().x * size * 1.2f;
		rect.y = room->getGridPos().y * size * 1.2f;

		int r, g, b;

		if (room->getRoomType() == Room::StartRoom) {
			r = 0;
			g = 255;
			b = 0;
		}
		else if (room->getRoomType() == Room::EndRoom) {
			r = 0;
			g = 0;
			b = 255;
		}
		else {
			r = 255;
			g = 0;
			b = 0;
		}
		TextureManager::DrawRect(rect, r, g, b, 255, true, false);

		//Draw the doors
		for (Door* door : room->getDoors()) {
			
			SDL_Rect door_rect;
			door_rect.w = size * 0.2;
			door_rect.h = size * 0.2;
			door_rect.x = rect.x + rect.w / 2;
			door_rect.y = rect.y + rect.h / 2;
			
			
			door_rect.x += door->doorPosition.x * (rect.w / 2);
			door_rect.y -= door->doorPosition.y * (rect.h / 2);

			TextureManager::DrawRect(door_rect, 255, 255, 255, 255, true, false);
		}

	}
	*/
}

void GenerateLevel::clean()
{
	
	cleanGeneratedData();

	delete startingRoom;
	delete endingRoom;

	for (RoomDataStruct* roomData : roomDataStructs) {
		delete roomData;
	}

	for (SDL_Texture* text : noDoorTextures) {
		SDL_DestroyTexture(text);
	}

	for (std::vector<SDL_Texture*> vect : openDoorTextures) {
		for (SDL_Texture* text : vect) {
			SDL_DestroyTexture(text);
		}
	}

	for (std::vector<SDL_Texture*> vect : closeDoorTextures) {
		for (SDL_Texture* text : vect) {
			SDL_DestroyTexture(text);
		}
	}

	SDL_DestroyTexture(tile_map_texture);

	Renderer::clean();
	Component::clean();
}

void GenerateLevel::loadRoomsFromFiles()
{
	//------------------------------- WE LOAD ALL THE ROOMS DATA -------------------------------------

	tile_map_texture = TextureManager::LoadTexture("img/dungeon_tileset.png");


	//------- LOAD THE NO DOOR'S TEXTURES ---------
	for (int i = 0; i < 4; i++) {
		std::string tile_data = "levels/no_doors/doors_" + std::to_string(i) + ".png";
		noDoorTextures.push_back(TextureManager::LoadTexture(tile_data.c_str()));
	}
	//--------------------------------------------


	//------- LOAD THE DOOR'S TEXTURES -----------
	for (int i = 0; i < 4; i++) {
		std::vector<SDL_Texture*> open_door_vect;
		std::vector<SDL_Texture*> close_door_vect;

		if (i % 2 == 0) {
			std::string openDoor = "levels/doors/door_"+ std::to_string(i) +"/open_door_" + std::to_string(i) + "_1.png";
			open_door_vect.push_back(TextureManager::LoadTexture(openDoor.c_str()));

			openDoor = "levels/doors/door_" + std::to_string(i) + "/open_door_" + std::to_string(i) + "_2.png";
			open_door_vect.push_back(TextureManager::LoadTexture(openDoor.c_str()));
		}
		else {
			std::string openDoor = "levels/doors/door_" + std::to_string(i) + "/open_door_" + std::to_string(i) + ".png";
			open_door_vect.push_back(TextureManager::LoadTexture(openDoor.c_str()));
		}

		std::string closeDoor = "levels/doors/door_" + std::to_string(i) + "/close_door_" + std::to_string(i) + ".png";
		close_door_vect.push_back(TextureManager::LoadTexture(closeDoor.c_str()));

		openDoorTextures.push_back(open_door_vect);
		closeDoorTextures.push_back(close_door_vect);
	}
	//--------------------------------------------


	//------ LOAD THE ENDING AND STARTING ROOM'S DATA --------

	endingRoom = new RoomDataStruct();
	loadRoomDataStruct("room_end", endingRoom);

	for (int i = 1; i <= 4; i++) {
		endingRoom->doorsPossible.push_back(convIndexToDoorPos(i));
	}


	startingRoom = new RoomDataStruct();
	loadRoomDataStruct("room_start", startingRoom);

	for (int i = 1; i <= 4; i++) {
		startingRoom->doorsPossible.push_back(convIndexToDoorPos(i));
	}

	//--------------------------------------------------------

	//---- LOAD THE OTHERS ROOM'S DATA AND TEXTURES -------
	std::string file_path = "levels/levels_name.txt";
	std::ifstream myfile(file_path);

	std::cout << "READING : " << file_path << std::endl;

	int x, y = 0;
	while (myfile.good()) {
		x = 0;

		std::vector<TileData*> vec_x;

		std::string line;
		std::getline(myfile, line, '\n');

		std::string buff{ "" };

		RoomDataStruct* roomDataStruct = new RoomDataStruct();
		
		for (auto n : line)
		{

			if (n != ',') buff += n; else
				if (n == ',' && buff != "") {
					std::cout << buff << ", ";

					if (x == 0) {

						loadRoomDataStruct(buff, roomDataStruct);

					}
					else {
						int door = std::atoi(buff.c_str());
						if (door == 1) {
							roomDataStruct->doorsPossible.push_back(convIndexToDoorPos(x));
						}
					}

					x++;
					buff = "";
				}

			
		}
		if (buff != "") {
			std::cout << buff << ", ";
			int door = std::atoi(buff.c_str());
			if (door == 1) {
				roomDataStruct->doorsPossible.push_back({ 0, 1 });
			}

			x++;
			buff = "";
		}

		roomDataStructs.push_back(roomDataStruct);

		std::cout << "" << std::endl;
		y++;
	}
	//------------------------------------------------------
	
}

void GenerateLevel::generateLevel()
{
	cleanGeneratedData();

	nbEnemyMultiplicator *= nbEnemyMultiplicator;
	timeEnemyMultiplicator *= timeEnemyMultiplicator;

	//init the first room at center
	OwnMathFuncs::Vector2 firstPos = {(float) WORLD_GRID_SIZE_X / 2, (float) WORLD_GRID_SIZE_Y / 2 };

	posTaken.push_back(firstPos);

	Room* firstRoom = new Room(firstPos);
	rooms[(int) firstPos.x][(int) firstPos.y] = firstRoom;
	roomsVector.push_back(firstRoom);

	//magic number
	float random_to_compare = 0.55f;

	for (int i = 0; i < NUMBER_OF_ROOMS - 1; i++) {

		float r = ((float) rand() / (float) RAND_MAX);
		
		bool one_neighbour = r < random_to_compare ? true : false;
		
		OwnMathFuncs::Vector2 newPos = { 0, 0 };
		int iteration = 0;

		do {

			newPos = getNewPos();
			iteration++;

		} while ((one_neighbour && getNumberOfNeighbours(newPos) > 1) && iteration < 500);
		
		Room* newRoom = new Room(newPos);
		rooms[(int)newPos.x][(int)newPos.y] = newRoom;

		roomsVector.push_back(newRoom);
		posTaken.push_back(newPos);
	}

	//------ FIND THE START AND END ROOM AND SET THE DOORS -------------

	//Set the start and the end of the level
	Room* start_room = nullptr;
	Room* end_room = nullptr;

	for(Room* room : roomsVector){

		//set the doors
		int x = room->getGridPos().x - 1;
		int y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::WORLD_GRID_SIZE_X && y > 0 && y < GenerateLevel::WORLD_GRID_SIZE_Y && rooms[x][y] != nullptr) {
			Door* door = new Door();
			door->doorPosition = { -1, 0 };
			room->addDoor(door);

		}

		x = room->getGridPos().x + 1;
		y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::WORLD_GRID_SIZE_X && y > 0 && y < GenerateLevel::WORLD_GRID_SIZE_Y && rooms[x][y] != nullptr) {
			Door* door = new Door();
			door->doorPosition = { 1, 0 };
			room->addDoor(door);
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y + 1;

		if (x > 0 && x < GenerateLevel::WORLD_GRID_SIZE_X && y > 0 && y < GenerateLevel::WORLD_GRID_SIZE_Y && rooms[x][y] != nullptr) {
			Door* door = new Door();
			door->doorPosition = { 0, -1 };
			room->addDoor(door);
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y - 1;

		if (x > 0 && x < GenerateLevel::WORLD_GRID_SIZE_X && y > 0 && y < GenerateLevel::WORLD_GRID_SIZE_Y && rooms[x][y] != nullptr) {
			Door* door = new Door();
			door->doorPosition = { 0, 1 };
			room->addDoor(door);
		}

		//test for start room & end room
		if (start_room == nullptr || (room->getGridPos().x + room->getGridPos().y) <= (start_room->getGridPos().x + start_room->getGridPos().y)) {
			start_room = room;
		}
		else if (end_room == nullptr || (room->getGridPos().x + room->getGridPos().y) >(end_room->getGridPos().x + end_room->getGridPos().y)) {
			end_room = room;
		}
	}

	start_room->setRoomType(Room::StartRoom);
	end_room->setRoomType(Room::EndRoom);
	//-------------------------------------------------------------------------------------


	//---- CHOSE THE RIGHT TILE MAP DATA AND INSTANTIATE THE GAME OBJECTS -----------------
	GameObject* startRoomObject = nullptr;
	GameObject* endRoomObject = nullptr;

	for (Room* room : roomsVector) {
		
		GameObject* roomPrefab = new GameObject();
		roomPrefab->localScale = { 4, 4 };
		roomPrefab->localPosition = { room->getGridPos().x * roomPrefab->localScale.x * ROOM_GRID_SIZE_X * tileSize.x, room->getGridPos().y * roomPrefab->localScale.y * ROOM_GRID_SIZE_Y * tileSize.y };


		RoomDataStruct* roomDataStructChoosen;

		if (room->getRoomType() == Room::StartRoom) {
			
			roomDataStructChoosen = startingRoom;
			startRoomObject = roomPrefab;
		}
		else if (room->getRoomType() == Room::EndRoom) {

			roomDataStructChoosen = endingRoom;
			endRoomObject = roomPrefab;
		}
		else {

			//We try to find a tile map data that fit the doors
			bool is_ok = true;

			int random_index = 0;
			int iteration = 0;

			do {

				is_ok = true;
				random_index = rand() % roomDataStructs.size();

				roomDataStructChoosen = roomDataStructs[random_index];
				for (Door* door : room->getDoors()) {

					bool door_ok = false;
					for (OwnMathFuncs::Vector2 door_possible : roomDataStructChoosen->doorsPossible) {

						if (door->doorPosition == door_possible) {
							door_ok = true;
						}
					}

					if (!door_ok) {
						is_ok = false;
					}

				}

				iteration++;
			} while (!is_ok && iteration < 150);

		}

		room->setTileMapData(roomDataStructChoosen->tileMapData);

		//Create Sprite Renderers for each texture
		for (int i = 0; i < roomDataStructChoosen->roomTextures.size(); i++) {
			SDL_Texture* texture = roomDataStructChoosen->roomTextures[i];
			if (texture != nullptr) {
				SpriteRenderer* spriteRenderer = new SpriteRenderer(roomPrefab, texture, false);
				spriteRenderer->setLayer(i);

				std::cout << i << std::endl;
			}
		}

		bool left_door_found = false;
		bool right_door_found = false;
		bool top_door_found = false;
		bool bot_door_found = false;



		for (Door* door : room->getDoors()) {

			GameObject* openDoorPrefab = new GameObject();
			GameObject* closeDoorPrefab = new GameObject();

			//--------------- ADD COLLIDERS ---------------
			BoxCollider* doorColliderTrigger = new BoxCollider(roomPrefab);
			doorColliderTrigger->setCollisionLayer(10);

			doorColliderTrigger->size.y = door->doorPosition.y == 0 ? tileSize.y * 2 : tileSize.y;
			doorColliderTrigger->size.x = door->doorPosition.x == 0 ? tileSize.x * 2 : tileSize.x;

			int nbTile = (ROOM_GRID_SIZE_X / 2) - ROOM_NO_DOOR_OFFSET_X - 1;
			doorColliderTrigger->offset.x = door->doorPosition.x * ((nbTile * tileSize.x) - doorColliderTrigger->size.x / 2);

			nbTile = door->doorPosition.y == -1 ? (ROOM_GRID_SIZE_Y / 2) - ROOM_NO_DOOR_OFFSET_Y : (ROOM_GRID_SIZE_Y / 2) - ROOM_NO_DOOR_OFFSET_Y - 1;
			doorColliderTrigger->offset.y = -1 * door->doorPosition.y * ((nbTile * tileSize.y) - doorColliderTrigger->size.y / 2);

			door->boxColliderTrigger = doorColliderTrigger;


			BoxCollider* door_collider = new BoxCollider(roomPrefab);

			door_collider->size.y = door->doorPosition.y == 0 ? tileSize.y * 2 : tileSize.y;
			door_collider->size.x = door->doorPosition.x == 0 ? tileSize.x * 2 : tileSize.x;

			nbTile = (ROOM_GRID_SIZE_X / 2) - ROOM_NO_DOOR_OFFSET_X + 1;
			door_collider->offset.x = door->doorPosition.x * ((nbTile * tileSize.x) - doorColliderTrigger->size.x / 2);

			nbTile = door->doorPosition.y == -1 ? (ROOM_GRID_SIZE_Y / 2) - ROOM_NO_DOOR_OFFSET_Y + 3 : (ROOM_GRID_SIZE_Y / 2) - ROOM_NO_DOOR_OFFSET_Y + 1;
			door_collider->offset.y = -1 * door->doorPosition.y * ((nbTile * tileSize.y) - doorColliderTrigger->size.y / 2);

			door->boxCollider = door_collider;
			//--------------------------------------------

			//-------- ADD DOORS TEXTURES ----------------

			for (SDL_Texture* texture : openDoorTextures[convDoorPosToIndex(door->doorPosition)]) {
				SpriteRenderer* spriteRenderer = new SpriteRenderer(openDoorPrefab, texture, false);
				if (convDoorPosToIndex(door->doorPosition) != 1 && convDoorPosToIndex(door->doorPosition) < 3) {
					spriteRenderer->setLayer(4);
				}
				else {
					spriteRenderer->setLayer(5);
				}
			}

			for (SDL_Texture* texture : closeDoorTextures[convDoorPosToIndex(door->doorPosition)]) {
				SpriteRenderer* spriteRenderer = new SpriteRenderer(closeDoorPrefab, texture, false);

				if (convDoorPosToIndex(door->doorPosition) != 1) {
					spriteRenderer->setLayer(4);
				}
				else {
					spriteRenderer->setLayer(5);
				}
			}
			//-------------------------------------------

			closeDoorPrefab->localPosition = door_collider->offset;
			door->closeDoor = closeDoorPrefab;
			roomPrefab->addGameObjectAsChild(openDoorPrefab);

			openDoorPrefab->localPosition = door_collider->offset;
			door->openDoor = openDoorPrefab;
			roomPrefab->addGameObjectAsChild(closeDoorPrefab);

			if (door->doorPosition.x == 1 && door->doorPosition.y == 0) {

				right_door_found = true;

			}
			else if (door->doorPosition.x == 0 && door->doorPosition.y == -1) {

				bot_door_found = true;
			}
			else if (door->doorPosition.x == -1 && door->doorPosition.y == 0) {

				left_door_found = true;
			}
			else if (door->doorPosition.x == 0 && door->doorPosition.y == 1) {

				top_door_found = true;
			}
		}


		int mid_x = (ROOM_GRID_SIZE_X / 2);
		mid_x = ROOM_GRID_SIZE_X % 2 == 0 ? mid_x -= 1 : mid_x;

		int mid_y = (ROOM_GRID_SIZE_Y / 2) - 1;
		mid_y = ROOM_GRID_SIZE_Y % 2 == 0 ? mid_y : mid_y -= 1;


		//Set the no door textures
		if (!right_door_found) {
			for (int index = 0; index < ROOM_NB_TILE_DOOR_X; index++) {

				if (index > 0) {
					if (index % 2 == 0) {
						room->getTileMapData()->data[mid_y - index][ROOM_GRID_SIZE_X - ROOM_NO_DOOR_OFFSET_X - 1]->collider = true;
					}
					else {
						room->getTileMapData()->data[mid_y + index][ROOM_GRID_SIZE_X - ROOM_NO_DOOR_OFFSET_X - 1]->collider = true;
					}
				}
				else {

					room->getTileMapData()->data[mid_y][ROOM_GRID_SIZE_X - ROOM_NO_DOOR_OFFSET_X - 1]->collider = true;
				}
			}

			SpriteRenderer* spriteRenderer = new SpriteRenderer(roomPrefab, noDoorTextures[0], false);
			spriteRenderer->setLayer(11);
		}

		if (!bot_door_found) {
			for (int index = 0; index < ROOM_NB_TILE_DOOR_X; index++) {

				if (index > 0) {
					if (index % 2 == 0) {
						room->getTileMapData()->data[ROOM_GRID_SIZE_Y - ROOM_NO_DOOR_OFFSET_Y + 1][mid_x - index]->collider = true;
					}
					else {
						room->getTileMapData()->data[ROOM_GRID_SIZE_Y - ROOM_NO_DOOR_OFFSET_Y + 1][mid_x + index]->collider = true;
					}
				}
				else {

					room->getTileMapData()->data[ROOM_GRID_SIZE_Y - ROOM_NO_DOOR_OFFSET_Y + 1][mid_x]->collider = true;
				}
			}


			SpriteRenderer* spriteRenderer = new SpriteRenderer(roomPrefab, noDoorTextures[1], false);
			spriteRenderer->setLayer(11);
		}

		if (!left_door_found) {
			for (int index = 0; index < ROOM_NB_TILE_DOOR_X; index++) {

				if (index > 0) {
					if (index % 2 == 0) {
						room->getTileMapData()->data[mid_y - index][ROOM_NO_DOOR_OFFSET_X]->collider = true;
					}
					else {
						room->getTileMapData()->data[mid_y + index][ROOM_NO_DOOR_OFFSET_X]->collider = true;
					}
				}
				else {

					room->getTileMapData()->data[mid_y][ROOM_NO_DOOR_OFFSET_X]->collider = true;
				}
			}

			SpriteRenderer* spriteRenderer = new SpriteRenderer(roomPrefab, noDoorTextures[2], false);
			spriteRenderer->setLayer(11);
		}

		if (!top_door_found) {


			for (int index = 0; index < ROOM_NB_TILE_DOOR_X; index++) {

				if (index > 0) {
					if (index % 2 == 0) {
						room->getTileMapData()->data[ROOM_NO_DOOR_OFFSET_Y][mid_x - index]->collider = true;
					}
					else {
						room->getTileMapData()->data[ROOM_NO_DOOR_OFFSET_Y][mid_x + index]->collider = true;
					}
				}
				else {

					room->getTileMapData()->data[ROOM_NO_DOOR_OFFSET_Y][mid_x]->collider = true;
				}
			}


			SpriteRenderer* spriteRenderer = new SpriteRenderer(roomPrefab, noDoorTextures[3], false);
			spriteRenderer->setLayer(2);
		}


		if (room->getRoomType() != Room::StartRoom && room->getRoomType() != Room::EndRoom) {

			// ------ CREATE ENEMIES OF THE ROOM -------------
			
			int nb_enemy_min = minEnemy * nbEnemyMultiplicator;
			int nb_enemy_max = maxEnemy * nbEnemyMultiplicator;

			int nb_enemies = 0;
			if (nb_enemy_min != 0 && nb_enemy_max != 0) {
				nb_enemies = rand() % nb_enemy_max + nb_enemy_min;
			}
			

			for (int i = 0; i < nb_enemies; i++) {

				GameObject* new_enemy;
				OwnMathFuncs::Vector2 newPos = { roomPrefab->getWorldPosition() };

				OwnMathFuncs::Vector2 spriteSize = room->getTileMapData()->spriteSize;
				OwnMathFuncs::Vector2 new_world_pos = { roomPrefab->getWorldPosition().x - (GenerateLevel::ROOM_GRID_SIZE_X * spriteSize.x * roomPrefab->localScale.x) / 2,
					roomPrefab->getWorldPosition().y - (GenerateLevel::ROOM_GRID_SIZE_Y * spriteSize.y * roomPrefab->localScale.y) / 2 };


				if (room->getTileMapData()->spawners.size() > 0) {

					int index_spawner = rand() % room->getTileMapData()->spawners.size();
					TileData* tile_data = room->getTileMapData()->spawners[index_spawner];

					newPos = { new_world_pos.x + tile_data->positionGrid.x * spriteSize.x * roomPrefab->localScale.x,
						new_world_pos.y + tile_data->positionGrid.y * spriteSize.y * roomPrefab->localScale.x };


					int enemy = rand() % 4;
					switch (enemy)
					{

					case 0:
						new_enemy = new SnakePrefab(newPos);
						break;

					case 1:
						new_enemy = new GoblinPrefab(newPos);
						break;

					case 2:
						new_enemy = new MinotaurPrefab(newPos);
						break;

					case 3:
						new_enemy = new SlimPrefab(newPos);
						break;

					default:
						new_enemy = new GoblinPrefab(newPos);
						break;
					}

					EnemyBasicBehavior* enemy_behavior = new_enemy->getComponent<EnemyBasicBehavior>();
					enemy_behavior->setTimeBeforeEnemy(enemy_behavior->getTimeBeforeEnemy() * timeEnemyMultiplicator);

					new_enemy->active = false;
					room->addEnemy(new_enemy);

					Game::instance()->instantiateGameObject(new_enemy);

				}
			}
		}
		//-------------------------------------------

		RoomBehavior* roomBehavior = new RoomBehavior(roomPrefab, room);

		TileMapCollider* tile_map_collider = new TileMapCollider(roomPrefab);
		tile_map_collider->setLayer(40);

		Game::instance()->instantiateGameObject(roomPrefab);

		roomPrefabs.push_back(roomPrefab);
	}

	Game::instance()->findGameObject("Manager")->getComponent<GameManager>()->startLevel(startRoomObject->getWorldPosition());


	/*
	SlimPrefab* slime = new SlimPrefab(player_pos);
	Game::instance()->instantiateGameObject(slime);
	
	SlimPrefab* slime2 = new SlimPrefab({ player_pos.x + 100, player_pos.y});
	Game::instance()->instantiateGameObject(slime2);
	*/

	/*
	GoblinPrefab *goblin = new GoblinPrefab(player_pos);
	Game::instance()->instantiateGameObject(goblin);
	*/

	/*
	MinotaurPrefab *minotaur = new MinotaurPrefab(player_pos);
	Game::instance()->instantiateGameObject(minotaur);
	*/

	/*
	SnakePrefab* snake = new SnakePrefab(player_pos);
	Game::instance()->instantiateGameObject(snake);
	*/
}

int GenerateLevel::getNumberOfNeighbours(OwnMathFuncs::Vector2 room_pos)
{
	int i = 0;
	bool is_ok = false;
	

	Room* room = rooms[(int) room_pos.x][(int) room_pos.y];

	if (room != nullptr) {

		int x = room->getGridPos().x - 1;
		int y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::WORLD_GRID_SIZE_X && y > 0 && y < GenerateLevel::WORLD_GRID_SIZE_Y && rooms[x][y] != nullptr) {
			i++;
		}

		x = room->getGridPos().x + 1;
		y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::WORLD_GRID_SIZE_X && y > 0 && y < GenerateLevel::WORLD_GRID_SIZE_Y && rooms[x][y] != nullptr) {
			i++;
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y - 1;

		if (x > 0 && x < GenerateLevel::WORLD_GRID_SIZE_X && y > 0 && y < GenerateLevel::WORLD_GRID_SIZE_Y && rooms[x][y] != nullptr) {
			i++;
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y + 1;

		if (x > 0 && x < GenerateLevel::WORLD_GRID_SIZE_X && y > 0 && y < GenerateLevel::WORLD_GRID_SIZE_Y && rooms[x][y] != nullptr) {
			i++;
		}
	}

	return i;
}

void GenerateLevel::readCSV(const char * file_path, TileMapData* tileMapData)
{
	std::vector<std::vector<TileData*>> vec_temp;

	std::ifstream myfile(file_path);

	std::cout << "READING : " << file_path << std::endl;

	int x, y = 0;

	while (myfile.good()) {
		x = 0;

		std::vector<TileData*> vec_x;

		std::string line;
		std::getline(myfile, line, '\n');

		std::string buff{ "" };


		for (auto n : line)
		{

			if (n != ',') buff += n; else
				if (n == ',' && buff != "") {

					std::cout << buff << ", ";

					int datum = atoi(buff.c_str());

					struct TileData* t = new TileData();
					t->nbImg = datum;
					t->positionGrid = { (float)x, (float)y };

					vec_x.push_back(t);

					x++;
					buff = "";
				}

		}
		if (buff != "") {
			std::cout << buff << ", ";

			int datum = atoi(buff.c_str());

			struct TileData* t = new TileData();
			t->nbImg = datum;
			t->positionGrid = { (float)x, (float)y };

			vec_x.push_back(t);

			x++;
			buff = "";
		}


		vec_temp.push_back(vec_x);


		std::cout << "" << std::endl;
		y++;
	}

	tileMapData->data = vec_temp;
}

void GenerateLevel::readCSVCollider(const char * file_path, TileMapData* tileMapData)
{
	std::ifstream myfile(file_path);
	std::cout << "READING : " << file_path << std::endl;

	int x, y = 0;
	while (myfile.good()) {
		x = 0;

		std::vector<TileData> vec_x;

		std::string line;
		std::getline(myfile, line, '\n');

		std::string buff{ "" };

		for (auto n : line)
		{
			if (n != ',') buff += n; else
				if (n == ',' && buff != "") {

					std::cout << buff << ", ";
					int datum = atoi(buff.c_str());

					if (datum != -1) {
						TileData* t = tileMapData->getTile(x, y);

						if (t != nullptr) {

							t->collider = true;
						}
					}
					x++;
					buff = "";
				}
		}
		if (buff != "") {
			std::cout << buff << ", ";
			int datum = atoi(buff.c_str());

			if (datum != -1) {
				TileData* t = tileMapData->getTile(x, y);

				if (t != nullptr) {

					t->collider = true;
				}
			}
			x++;
			buff = "";
		}

		std::cout << "" << std::endl;
		y++;
	}
}

void GenerateLevel::readCSVSpawner(const char * file_path, TileMapData * tileMapData)
{
	std::ifstream myfile(file_path);
	std::cout << "READING : " << file_path << std::endl;

	int x, y = 0;
	while (myfile.good()) {
		x = 0;

		std::vector<TileData> vec_x;

		std::string line;
		std::getline(myfile, line, '\n');

		std::string buff{ "" };

		for (auto n : line)
		{
			if (n != ',') buff += n; else
				if (n == ',' && buff != "") {

					std::cout << buff << ", ";
					int datum = atoi(buff.c_str());

					if (datum != -1) {
						TileData* t = tileMapData->getTile(x, y);
						

						if (t != nullptr) {

							t->spawner = true;
							tileMapData->spawners.push_back(t);
						}
					}
					x++;
					buff = "";
				}
		}
		if (buff != "") {
			std::cout << buff << ", ";
			int datum = atoi(buff.c_str());

			if (datum != -1) {
				TileData* t = tileMapData->getTile(x, y);

				if (t != nullptr) {

					t->spawner = true;
					tileMapData->spawners.push_back(t);
				}
			}
			x++;
			buff = "";
		}

		std::cout << "" << std::endl;
		y++;
	}

	std::cout << "----------- SPAWNERS ---------------------" << std::endl;
	for (TileData* tile : tileMapData->spawners) {

		if (tile != nullptr && tile->spawner) {
			std::cout << tile->positionGrid.x << ", " << tile->positionGrid.y << std::endl;
		}

	}
	std::cout << "-----------------------------------------" << std::endl;
}

void GenerateLevel::loadRoomDataStruct(std::string room_name, RoomDataStruct * roomDataStruct)
{

	for (int i = 0; i <= 15; i++) {
		roomDataStruct->roomTextures.push_back(nullptr);
	}

	TileMapData* tileMapData = new TileMapData();
	std::string tile_data = "levels/" + room_name + "/" + room_name + ".csv";
	readCSV(tile_data.c_str(), tileMapData);

	std::string tile_data_collider = "levels/" + room_name + "/" + room_name + "_collider.csv";
	readCSVCollider(tile_data_collider.c_str(), tileMapData);

	std::string tile_data_spawner = "levels/" + room_name + "/" + room_name + "_spawner.csv";
	readCSVSpawner(tile_data_spawner.c_str(), tileMapData);

	roomDataStruct->tileMapData = tileMapData;

	int size = roomDataStruct->roomTextures.size();
	for (int i = 0; i < size; i++) {
		std::string spriteRenderer = "levels/" + room_name + "/" + room_name + "_" + std::to_string(i) + ".png";

		roomDataStruct->roomTextures[i] = TextureManager::LoadTexture(spriteRenderer.c_str());
	}
}

void GenerateLevel::cleanGeneratedData()
{
	posTaken.clear();

	for (Room* room : roomsVector) {
		delete room;
	}
	roomsVector.clear();

	for (int x = 0; x < WORLD_GRID_SIZE_X; x++) {

		for (int y = 0; y < WORLD_GRID_SIZE_Y; y++) {
			rooms[x][y] = nullptr;
		}

	}

	for (GameObject* roomPrefab : roomPrefabs) {

		Game::instance()->destroyGameObject(roomPrefab);
	}
	roomPrefabs.clear();

}


OwnMathFuncs::Vector2 GenerateLevel::getNewPos()
{
	bool posOk = true;
	int x, y;
	OwnMathFuncs::Vector2 checkingPos = { 0, 0 };

	do {
		//------- GETTING A POS ---------

		//Get a random existing pos
		OwnMathFuncs::Vector2 randomExistingPos = posTaken.at((int)rand() % (posTaken.size()));

		x = randomExistingPos.x;
		y = randomExistingPos.y;

		int randomXOrY = rand() % 2;

		if (randomXOrY == 0) {
			int randomX = rand() % 2;
			if (randomX == 0) {
				x = randomExistingPos.x + 1;
			}
			else {
				x = randomExistingPos.x - 1;
			}
		}
		else {
			int randomY = rand() % 2;
			if (randomY == 0) {
				y = randomExistingPos.y + 1;
			}
			else {
				y = randomExistingPos.y - 1;
			}
		}
		checkingPos = { (float)x , (float)y };


		//We check if the pos is not already taken
		posOk = true;
		for (OwnMathFuncs::Vector2 pos : posTaken) {
			if (pos == checkingPos) {
				posOk = false;
			}
		}

	} while (!posOk || x < 0 || x > WORLD_GRID_SIZE_X || y < 0 || y > WORLD_GRID_SIZE_Y);


	return checkingPos;
}

int GenerateLevel::convDoorPosToIndex(OwnMathFuncs::Vector2 pos)
{
	if (pos.x == 1 && pos.y == 0) {

		return 0;

	}
	else if (pos.x == 0 && pos.y == -1) {

		return 1;
	}
	else if (pos.x == -1 && pos.y == 0) {

		return 2;
	}
	else if (pos.x == 0 && pos.y == 1) {

		return 3;
	}

	return -1;
}

OwnMathFuncs::Vector2 GenerateLevel::convIndexToDoorPos(int index)
{
	switch (index)
	{
	case 1:
		return { 1, 0 };
		break;

	case 2:
		return { 0, -1 };
		break;

	case 3:
		return { -1, 0 };
		break;

	case 4:
		return { 0, 1 };
		break;
	default:
		return { 0, 0 };
		break;
	}
}

RoomDataStruct::~RoomDataStruct()
{
	delete tileMapData;
	for (SDL_Texture* text : roomTextures) {
		SDL_DestroyTexture(text);
	}
}
