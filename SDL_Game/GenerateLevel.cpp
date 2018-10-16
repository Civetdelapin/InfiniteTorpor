#include "GenerateLevel.h"
#include "Game.h"

OwnMathFuncs::Vector2 const GenerateLevel::tile_size = { 16, 16 };

GenerateLevel::GenerateLevel(GameObject * gameObject) : Renderer(this), Component(gameObject)
{
	setLayer(14);
}


GenerateLevel::~GenerateLevel()
{
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
	generateLevel(); // We create the levels	
}

void GenerateLevel::render()
{

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
			
			
			door_rect.x += door->door_position.x * (rect.w / 2);
			door_rect.y -= door->door_position.y * (rect.h / 2);

			TextureManager::DrawRect(door_rect, 255, 255, 255, 255, true, false);
		}

	}

}

void GenerateLevel::clean()
{
	
	cleanGeneratedData();

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
			std::string open_door = "levels/doors/door_"+ std::to_string(i) +"/open_door_" + std::to_string(i) + "_1.png";
			open_door_vect.push_back(TextureManager::LoadTexture(open_door.c_str()));

			open_door = "levels/doors/door_" + std::to_string(i) + "/open_door_" + std::to_string(i) + "_2.png";
			open_door_vect.push_back(TextureManager::LoadTexture(open_door.c_str()));
		}
		else {
			std::string open_door = "levels/doors/door_" + std::to_string(i) + "/open_door_" + std::to_string(i) + ".png";
			open_door_vect.push_back(TextureManager::LoadTexture(open_door.c_str()));
		}

		std::string close_door = "levels/doors/door_" + std::to_string(i) + "/close_door_" + std::to_string(i) + ".png";
		close_door_vect.push_back(TextureManager::LoadTexture(close_door.c_str()));

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
	OwnMathFuncs::Vector2 first_pos = {(float) WORLD_GRID_SIZE_X / 2, (float) WORLD_GRID_SIZE_Y / 2 };

	posTaken.push_back(first_pos);

	Room* first_room = new Room(first_pos);
	rooms[(int) first_pos.x][(int) first_pos.y] = first_room;
	roomsVector.push_back(first_room);

	//magic number
	float random_to_compare = 0.55f;

	for (int i = 0; i < NUMBER_OF_ROOMS - 1; i++) {

		float r = ((float) rand() / (float) RAND_MAX);
		
		bool one_neighbour = r < random_to_compare ? true : false;
		
		OwnMathFuncs::Vector2 new_pos = { 0, 0 };
		int iteration = 0;

		do {

			new_pos = getNewPos();
			iteration++;

		} while ((one_neighbour && getNumberOfNeighbours(new_pos) > 1) && iteration < 500);
		
		Room* new_room = new Room(new_pos);
		rooms[(int)new_pos.x][(int)new_pos.y] = new_room;

	
		roomsVector.push_back(new_room);
		posTaken.push_back(new_pos);
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
			door->door_position = { -1, 0 };
			room->addDoor(door);

		}

		x = room->getGridPos().x + 1;
		y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::WORLD_GRID_SIZE_X && y > 0 && y < GenerateLevel::WORLD_GRID_SIZE_Y && rooms[x][y] != nullptr) {
			Door* door = new Door();
			door->door_position = { 1, 0 };
			room->addDoor(door);
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y + 1;

		if (x > 0 && x < GenerateLevel::WORLD_GRID_SIZE_X && y > 0 && y < GenerateLevel::WORLD_GRID_SIZE_Y && rooms[x][y] != nullptr) {
			Door* door = new Door();
			door->door_position = { 0, -1 };
			room->addDoor(door);
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y - 1;

		if (x > 0 && x < GenerateLevel::WORLD_GRID_SIZE_X && y > 0 && y < GenerateLevel::WORLD_GRID_SIZE_Y && rooms[x][y] != nullptr) {
			Door* door = new Door();
			door->door_position = { 0, 1 };
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
	GameObject* start_room_object = nullptr;
	GameObject* end_room_object = nullptr;

	for (Room* room : roomsVector) {
		
		GameObject* room_prefab = new GameObject();
		room_prefab->localScale = { 4, 4 };
		room_prefab->localPosition = { room->getGridPos().x * room_prefab->localScale.x * ROOM_GRID_SIZE_X * tile_size.x, room->getGridPos().y * room_prefab->localScale.y * ROOM_GRID_SIZE_Y * tile_size.y };


		RoomDataStruct* roomDataStructChoosen;

		if (room->getRoomType() == Room::StartRoom) {
			
			roomDataStructChoosen = startingRoom;
			start_room_object = room_prefab;
		}
		else if (room->getRoomType() == Room::EndRoom) {

			roomDataStructChoosen = endingRoom;
			end_room_object = room_prefab;
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

						if (door->door_position == door_possible) {
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
				SpriteRenderer* sprite_renderer = new SpriteRenderer(room_prefab, texture, false);
				sprite_renderer->setLayer(i);

				std::cout << i << std::endl;
			}
		}

		bool left_door_found = false;
		bool right_door_found = false;
		bool top_door_found = false;
		bool bot_door_found = false;



		for (Door* door : room->getDoors()) {

			GameObject* open_door_prefab = new GameObject();
			GameObject* close_door_prefab = new GameObject();

			//--------------- ADD COLLIDERS ---------------
			BoxCollider* door_collider_trigger = new BoxCollider(room_prefab);
			door_collider_trigger->setCollisionLayer(10);

			door_collider_trigger->size.y = door->door_position.y == 0 ? tile_size.y * 2 : tile_size.y;
			door_collider_trigger->size.x = door->door_position.x == 0 ? tile_size.x * 2 : tile_size.x;

			int nb_tile = (ROOM_GRID_SIZE_X / 2) - ROOM_NO_DOOR_OFFSET_X - 1;
			door_collider_trigger->offset.x = door->door_position.x * ((nb_tile * tile_size.x) - door_collider_trigger->size.x / 2);

			nb_tile = door->door_position.y == -1 ? (ROOM_GRID_SIZE_Y / 2) - ROOM_NO_DOOR_OFFSET_Y : (ROOM_GRID_SIZE_Y / 2) - ROOM_NO_DOOR_OFFSET_Y - 1;
			door_collider_trigger->offset.y = -1 * door->door_position.y * ((nb_tile * tile_size.y) - door_collider_trigger->size.y / 2);

			door->box_collider_trigger = door_collider_trigger;


			BoxCollider* door_collider = new BoxCollider(room_prefab);

			door_collider->size.y = door->door_position.y == 0 ? tile_size.y * 2 : tile_size.y;
			door_collider->size.x = door->door_position.x == 0 ? tile_size.x * 2 : tile_size.x;

			nb_tile = (ROOM_GRID_SIZE_X / 2) - ROOM_NO_DOOR_OFFSET_X + 1;
			door_collider->offset.x = door->door_position.x * ((nb_tile * tile_size.x) - door_collider_trigger->size.x / 2);

			nb_tile = door->door_position.y == -1 ? (ROOM_GRID_SIZE_Y / 2) - ROOM_NO_DOOR_OFFSET_Y + 3 : (ROOM_GRID_SIZE_Y / 2) - ROOM_NO_DOOR_OFFSET_Y + 1;
			door_collider->offset.y = -1 * door->door_position.y * ((nb_tile * tile_size.y) - door_collider_trigger->size.y / 2);

			door->box_collider = door_collider;
			//--------------------------------------------

			//-------- ADD DOORS TEXTURES ----------------

			for (SDL_Texture* texture : openDoorTextures[convDoorPosToIndex(door->door_position)]) {
				SpriteRenderer* sprite_renderer = new SpriteRenderer(open_door_prefab, texture, false);
				if (convDoorPosToIndex(door->door_position) != 1) {
					sprite_renderer->setLayer(4);
				}
				else {
					sprite_renderer->setLayer(5);
				}
			}

			for (SDL_Texture* texture : closeDoorTextures[convDoorPosToIndex(door->door_position)]) {
				SpriteRenderer* sprite_renderer = new SpriteRenderer(close_door_prefab, texture, false);

				if (convDoorPosToIndex(door->door_position) != 1) {
					sprite_renderer->setLayer(4);
				}
				else {
					sprite_renderer->setLayer(5);
				}
			}
			//-------------------------------------------

			close_door_prefab->localPosition = door_collider->offset;
			door->close_door = close_door_prefab;
			room_prefab->addGameObjectAsChild(open_door_prefab);

			open_door_prefab->localPosition = door_collider->offset;
			door->open_door = open_door_prefab;
			room_prefab->addGameObjectAsChild(close_door_prefab);

			if (door->door_position.x == 1 && door->door_position.y == 0) {

				right_door_found = true;

			}
			else if (door->door_position.x == 0 && door->door_position.y == -1) {

				bot_door_found = true;
			}
			else if (door->door_position.x == -1 && door->door_position.y == 0) {

				left_door_found = true;
			}
			else if (door->door_position.x == 0 && door->door_position.y == 1) {

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
						room->getTileMapData()->data[mid_y - index][ROOM_GRID_SIZE_X - ROOM_NO_DOOR_OFFSET_X - 1]->is_collider = true;
					}
					else {
						room->getTileMapData()->data[mid_y + index][ROOM_GRID_SIZE_X - ROOM_NO_DOOR_OFFSET_X - 1]->is_collider = true;
					}
				}
				else {

					room->getTileMapData()->data[mid_y][ROOM_GRID_SIZE_X - ROOM_NO_DOOR_OFFSET_X - 1]->is_collider = true;
				}
			}

			SpriteRenderer* sprite_renderer = new SpriteRenderer(room_prefab, noDoorTextures[0], false);
			sprite_renderer->setLayer(11);
		}

		if (!bot_door_found) {
			for (int index = 0; index < ROOM_NB_TILE_DOOR_X; index++) {

				if (index > 0) {
					if (index % 2 == 0) {
						room->getTileMapData()->data[ROOM_GRID_SIZE_Y - ROOM_NO_DOOR_OFFSET_Y + 1][mid_x - index]->is_collider = true;
					}
					else {
						room->getTileMapData()->data[ROOM_GRID_SIZE_Y - ROOM_NO_DOOR_OFFSET_Y + 1][mid_x + index]->is_collider = true;
					}
				}
				else {

					room->getTileMapData()->data[ROOM_GRID_SIZE_Y - ROOM_NO_DOOR_OFFSET_Y + 1][mid_x]->is_collider = true;
				}
			}


			SpriteRenderer* sprite_renderer = new SpriteRenderer(room_prefab, noDoorTextures[1], false);
			sprite_renderer->setLayer(11);
		}

		if (!left_door_found) {
			for (int index = 0; index < ROOM_NB_TILE_DOOR_X; index++) {

				if (index > 0) {
					if (index % 2 == 0) {
						room->getTileMapData()->data[mid_y - index][ROOM_NO_DOOR_OFFSET_X]->is_collider = true;
					}
					else {
						room->getTileMapData()->data[mid_y + index][ROOM_NO_DOOR_OFFSET_X]->is_collider = true;
					}
				}
				else {

					room->getTileMapData()->data[mid_y][ROOM_NO_DOOR_OFFSET_X]->is_collider = true;
				}
			}

			SpriteRenderer* sprite_renderer = new SpriteRenderer(room_prefab, noDoorTextures[2], false);
			sprite_renderer->setLayer(11);
		}

		if (!top_door_found) {


			for (int index = 0; index < ROOM_NB_TILE_DOOR_X; index++) {

				if (index > 0) {
					if (index % 2 == 0) {
						room->getTileMapData()->data[ROOM_NO_DOOR_OFFSET_Y][mid_x - index]->is_collider = true;
					}
					else {
						room->getTileMapData()->data[ROOM_NO_DOOR_OFFSET_Y][mid_x + index]->is_collider = true;
					}
				}
				else {

					room->getTileMapData()->data[ROOM_NO_DOOR_OFFSET_Y][mid_x]->is_collider = true;
				}
			}


			SpriteRenderer* sprite_renderer = new SpriteRenderer(room_prefab, noDoorTextures[3], false);
			sprite_renderer->setLayer(2);
		}


		if (room->getRoomType() != Room::StartRoom && room->getRoomType() != Room::EndRoom) {

			// ------ CREATE ENEMIES OF THE ROOM -------------
			//int nb_enemies = 0;

			int nb_enemy_min = minEnemy * nbEnemyMultiplicator;
			int nb_enemy_max = maxEnemy * nbEnemyMultiplicator;

			int nb_enemies = 0;
			if (nb_enemy_min != 0 && nb_enemy_max != 0) {
				int nb_enemies = rand() % nb_enemy_max + nb_enemy_min;
			}
			
			for (int i = 0; i < nb_enemies; i++) {

				GameObject* new_enemy;
				OwnMathFuncs::Vector2 new_pos = { room_prefab->getWorldPosition() };

				OwnMathFuncs::Vector2 sprite_size = room->getTileMapData()->sprite_size;
				OwnMathFuncs::Vector2 new_world_pos = { room_prefab->getWorldPosition().x - (GenerateLevel::ROOM_GRID_SIZE_X * sprite_size.x * room_prefab->localScale.x) / 2,
					room_prefab->getWorldPosition().y - (GenerateLevel::ROOM_GRID_SIZE_Y * sprite_size.y * room_prefab->localScale.y) / 2 };


				if (room->getTileMapData()->spawners.size() > 0) {

					int index_spawner = rand() % room->getTileMapData()->spawners.size();
					TileData* tile_data = room->getTileMapData()->spawners[index_spawner];

					new_pos = { new_world_pos.x + tile_data->position_grid.x * sprite_size.x * room_prefab->localScale.x,
						new_world_pos.y + tile_data->position_grid.y * sprite_size.y * room_prefab->localScale.x };


					int enemy = rand() % 4;
					switch (enemy)
					{

					case 0:
						new_enemy = new SnakePrefab(new_pos);
						break;

					case 1:
						new_enemy = new GoblinPrefab(new_pos);
						break;

					case 2:
						new_enemy = new MinotaurPrefab(new_pos);
						break;

					case 3:
						new_enemy = new SlimPrefab(new_pos);
						break;

					default:
						new_enemy = new GoblinPrefab(new_pos);
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

		RoomBehavior* room_behavior = new RoomBehavior(room_prefab, room);

		TileMapCollider* tile_map_collider = new TileMapCollider(room_prefab);
		tile_map_collider->setLayer(40);

		Game::instance()->instantiateGameObject(room_prefab);

		roomPrefabs.push_back(room_prefab);
	}

	Game::instance()->findGameObject("Manager")->getComponent<GameManager>()->startLevel(start_room_object->getWorldPosition());


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
					t->nb_img = datum;
					t->position_grid = { (float)x, (float)y };

					vec_x.push_back(t);

					x++;
					buff = "";
				}

		}
		if (buff != "") {
			std::cout << buff << ", ";

			int datum = atoi(buff.c_str());

			struct TileData* t = new TileData();
			t->nb_img = datum;
			t->position_grid = { (float)x, (float)y };

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

							t->is_collider = true;
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

					t->is_collider = true;
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

							t->is_spawner = true;
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

					t->is_spawner = true;
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

		if (tile != nullptr && tile->is_spawner) {
			std::cout << tile->position_grid.x << ", " << tile->position_grid.y << std::endl;
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
		std::string sprite_renderer = "levels/" + room_name + "/" + room_name + "_" + std::to_string(i) + ".png";

		roomDataStruct->roomTextures[i] = TextureManager::LoadTexture(sprite_renderer.c_str());
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


	for (GameObject* room_prefab : roomPrefabs) {

		Game::instance()->destroyGameObject(room_prefab);
	}
	roomPrefabs.clear();

}


OwnMathFuncs::Vector2 GenerateLevel::getNewPos()
{
	bool pos_ok = true;
	int x, y;
	OwnMathFuncs::Vector2 checking_pos = { 0, 0 };

	do {
		//------- GETTING A POS ---------

		//Get a random existing pos
		OwnMathFuncs::Vector2 random_existing_pos = posTaken.at((int)rand() % (posTaken.size()));

		x = random_existing_pos.x;
		y = random_existing_pos.y;

		int random_x_or_y = rand() % 2;

		if (random_x_or_y == 0) {
			int random_x = rand() % 2;
			if (random_x == 0) {
				x = random_existing_pos.x + 1;
			}
			else {
				x = random_existing_pos.x - 1;
			}
		}
		else {
			int random_y = rand() % 2;
			if (random_y == 0) {
				y = random_existing_pos.y + 1;
			}
			else {
				y = random_existing_pos.y - 1;
			}
		}
		checking_pos = { (float)x , (float)y };


		//We check if the pos is not already taken
		pos_ok = true;
		for (OwnMathFuncs::Vector2 pos : posTaken) {
			if (pos == checking_pos) {
				pos_ok = false;
			}
		}

	} while (!pos_ok || x < 0 || x > WORLD_GRID_SIZE_X || y < 0 || y > WORLD_GRID_SIZE_Y);


	return checking_pos;
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
