#include "GenerateLevel.h"
#include "Game.h"

OwnMathFuncs::Vector2 const GenerateLevel::tile_size = { 16, 16 };

GenerateLevel::GenerateLevel(GameObject * game_object) : Renderer(this), Component(game_object)
{
	setLayer(50);
}


GenerateLevel::~GenerateLevel()
{
}

void GenerateLevel::start()
{
	tile_map_texture = TextureManager::LoadTexture("img/dungeon_tileset.png");

	srand(seed);

	loadRoomsFromFiles(); // We load all the rooms data 

	generateLevel(); // We create the level 
		
}

void GenerateLevel::render()
{

	const int size = 50;


	//Draw the rects for testing
	for (Room* room : rooms_vector) {
		
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
	for (Room* room : rooms_vector) {
		delete room;
	}
	rooms_vector.clear();


	vect_room_data_struct.clear();

	SDL_DestroyTexture(tile_map_texture);

	Renderer::clean();
	Component::clean();
}

void GenerateLevel::loadRoomsFromFiles()
{
	//---------------- WE LOAD ALL THE ROOMS DATA ------------------


	//------- LOAD THE NO DOOR'S TEXTURES ---------
	for (int i = 0; i < 4; i++) {
		std::string tile_data = "levels/no_doors/doors_" + std::to_string(i) + ".png";
		no_door_textures.push_back(TextureManager::LoadTexture(tile_data.c_str()));
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

		open_door_textures.push_back(open_door_vect);
		close_door_textures.push_back(close_door_vect);
	}
	//--------------------------------------------


	//---- LOAD THE ROOM'S DATA AND TEXTURES -------
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

						for (int i = 0; i <= 10; i++) {
							roomDataStruct->vect_room_texture.push_back(nullptr);
						}

						TileMapData* tile_map_data = new TileMapData();
						std::string tile_data = "levels/"+ buff +"/" + buff + ".csv";
						readCSV(tile_data.c_str(), tile_map_data);

						std::string tile_data_collider = "levels/" + buff + "/" + buff + "_collider.csv";
						readCSVCollider(tile_data_collider.c_str(), tile_map_data);

						std::string tile_data_spawner = "levels/" + buff + "/" + buff + "_spawner.csv";
						readCSVSpawner(tile_data_spawner.c_str(), tile_map_data);

						roomDataStruct->tile_map_data = tile_map_data;

						for (int i = 0; i <= 10; i++) {
							std::string sprite_renderer = "levels/" + buff + "/" + buff + "_" + std::to_string(i) + ".png";
							roomDataStruct->vect_room_texture[i] = TextureManager::LoadTexture(sprite_renderer.c_str());
						}					

					}
					else {
						int door = std::atoi(buff.c_str());
						if (door == 1) {

							switch (x)
							{
								case 1:
									roomDataStruct->doors_possible.push_back({ 1, 0 });
									break;

								case 2:
									roomDataStruct->doors_possible.push_back({ 0, -1 });
									break;

								case 3:
									roomDataStruct->doors_possible.push_back({ -1, 0 });
									break;

								case 4:
									roomDataStruct->doors_possible.push_back({ 0, 1 });
									break;
							
							}


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
				roomDataStruct->doors_possible.push_back({ 0, 1 });
			}

			x++;
			buff = "";
		}

		vect_room_data_struct.push_back(roomDataStruct);

		std::cout << "" << std::endl;
		y++;
	}
	//------------------------------------------------------
	
}

void GenerateLevel::generateLevel()
{
	//init the first room at center
	OwnMathFuncs::Vector2 first_pos = {(float) world_grid_size_x / 2, (float) world_grid_size_y / 2 };

	pos_taken.push_back(first_pos);

	Room* first_room = new Room(first_pos);
	rooms[(int) first_pos.x][(int) first_pos.y] = first_room;
	rooms_vector.push_back(first_room);

	//magic number
	float random_to_compare = 0.55f;

	for (int i = 0; i < number_of_rooms - 1; i++) {

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

	
		rooms_vector.push_back(new_room);
		pos_taken.push_back(new_pos);
	}

	//Set the start and the end of the level
	GameObject* start_room = nullptr;
	GameObject* end_room = nullptr;


	for(Room* room : rooms_vector){

		GameObject* room_prefab = new GameObject();
		room_prefab->local_scale = { 4, 4 };
		room_prefab->local_position = { room->getGridPos().x * room_prefab->local_scale.x * room_grid_size_x * tile_size.x, room->getGridPos().y * room_prefab->local_scale.y * room_grid_size_y * tile_size.y };

		//set the doors
		int x = room->getGridPos().x - 1;
		int y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			Door* door = new Door();
			door->door_position = { -1, 0 };
			room->addDoor(door);

		}

		x = room->getGridPos().x + 1;
		y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			Door* door = new Door();
			door->door_position = { 1, 0 };
			room->addDoor(door);
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y + 1;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			Door* door = new Door();
			door->door_position = { 0, -1 };
			room->addDoor(door);
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y - 1;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			Door* door = new Door();
			door->door_position = { 0, 1 };
			room->addDoor(door);
		}

		int random_index = rand() % vect_room_data_struct.size();
		
		RoomDataStruct* roomDataStructChoosen = vect_room_data_struct[random_index];
		room->setTileMapData(roomDataStructChoosen->tile_map_data);


		//Create Sprite Renderers for each texture
		for (int i = 0; i < roomDataStructChoosen->vect_room_texture.size(); i++) {
			SDL_Texture* texture = roomDataStructChoosen->vect_room_texture[i];
			if (texture != nullptr) {
				SpriteRenderer* sprite_renderer = new SpriteRenderer(room_prefab, texture);
				sprite_renderer->setLayer(i);
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

			int nb_tile = (room_grid_size_x / 2) - room_no_door_offset_x - 1;
			door_collider_trigger->offset.x = door->door_position.x * ((nb_tile * tile_size.x) - door_collider_trigger->size.x / 2);

			nb_tile = door->door_position.y == -1 ? (room_grid_size_y / 2) - room_no_door_offset_y : (room_grid_size_y / 2) - room_no_door_offset_y - 1;
			door_collider_trigger->offset.y = -1 * door->door_position.y * ((nb_tile * tile_size.y) - door_collider_trigger->size.y / 2);

			door->box_collider_trigger = door_collider_trigger;


			BoxCollider* door_collider = new BoxCollider(room_prefab);

			door_collider->size.y = door->door_position.y == 0 ? tile_size.y * 2 : tile_size.y;
			door_collider->size.x = door->door_position.x == 0 ? tile_size.x * 2 : tile_size.x;

			nb_tile = (room_grid_size_x / 2) - room_no_door_offset_x + 1;
			door_collider->offset.x = door->door_position.x * ((nb_tile * tile_size.x) - door_collider_trigger->size.x / 2);

			nb_tile = door->door_position.y == -1 ? (room_grid_size_y / 2) - room_no_door_offset_y + 3 : (room_grid_size_y / 2) - room_no_door_offset_y + 1;
			door_collider->offset.y = -1 * door->door_position.y * ((nb_tile * tile_size.y) - door_collider_trigger->size.y / 2);

			door->box_collider = door_collider;
			//--------------------------------------------

			//-------- ADD DOORS TEXTURES ----------------

			for (SDL_Texture* texture : open_door_textures[convDoorPosToIndex(door->door_position)]) {
				SpriteRenderer* sprite_renderer = new SpriteRenderer(open_door_prefab, texture);
				if (convDoorPosToIndex(door->door_position) != 1) {
					sprite_renderer->setLayer(4);
				}
				else {
					sprite_renderer->setLayer(5);
				}
			}

			for (SDL_Texture* texture : close_door_textures[convDoorPosToIndex(door->door_position)]) {
				SpriteRenderer* sprite_renderer = new SpriteRenderer(close_door_prefab, texture);

				if (convDoorPosToIndex(door->door_position) != 1) {
					sprite_renderer->setLayer(4);
				}
				else {
					sprite_renderer->setLayer(5);
				}
			}
			//-------------------------------------------

			close_door_prefab->local_position = door_collider->offset;
			door->close_door = close_door_prefab;
			room_prefab->addGameObjectAsChild(open_door_prefab);

			open_door_prefab->local_position = door_collider->offset;
			door->open_door = open_door_prefab;
			room_prefab->addGameObjectAsChild(close_door_prefab);

			if (door->door_position.x == 1 && door->door_position.y == 0) {

				right_door_found = true;

			}else if(door->door_position.x == 0 && door->door_position.y == -1) {

				bot_door_found = true;	
			}
			else if (door->door_position.x == -1 && door->door_position.y == 0) {

				left_door_found = true;		
			}
			else if (door->door_position.x == 0 && door->door_position.y == 1) {

				top_door_found = true;
			}
		}
		

		int mid_x = (room_grid_size_x / 2);
		mid_x = room_grid_size_x % 2 == 0 ? mid_x -= 1 : mid_x ;

		int mid_y = (room_grid_size_y / 2) - 1;
		mid_y = room_grid_size_y % 2 == 0 ? mid_y : mid_y -= 1;


		//Set the no door textures
		if (!right_door_found) {
			for (int index = 0; index < room_nb_tile_door_x; index++) {

				if (index > 0) {
					if (index % 2 == 0) {
						room->getTileMapData()->data[mid_y - index][room_grid_size_x - room_no_door_offset_x - 1]->is_collider = true;
					}
					else {
						room->getTileMapData()->data[mid_y + index][room_grid_size_x - room_no_door_offset_x - 1]->is_collider = true;
					}
				}
				else {

					room->getTileMapData()->data[mid_y][room_grid_size_x - room_no_door_offset_x - 1]->is_collider = true;
				}
			}

			SpriteRenderer* sprite_renderer = new SpriteRenderer(room_prefab, no_door_textures[0]);
			sprite_renderer->setLayer(11);
		}

		if (!bot_door_found) {
			for (int index = 0; index < room_nb_tile_door_x; index++) {

				if (index > 0) {
					if (index % 2 == 0) {
						room->getTileMapData()->data[room_grid_size_y - room_no_door_offset_y + 1][mid_x - index]->is_collider = true;
					}
					else {
						room->getTileMapData()->data[room_grid_size_y - room_no_door_offset_y + 1][mid_x + index]->is_collider = true;
					}
				}
				else {

					room->getTileMapData()->data[room_grid_size_y - room_no_door_offset_y + 1][mid_x]->is_collider = true;
				}
			}


			SpriteRenderer* sprite_renderer = new SpriteRenderer(room_prefab, no_door_textures[1]);
			sprite_renderer->setLayer(11);
		}

		if (!left_door_found) {
			for (int index = 0; index < room_nb_tile_door_x; index++) {

				if (index > 0) {
					if (index % 2 == 0) {
						room->getTileMapData()->data[mid_y - index][room_no_door_offset_x]->is_collider = true;
					}
					else {
						room->getTileMapData()->data[mid_y + index][room_no_door_offset_x]->is_collider = true;
					}
				}
				else {

					room->getTileMapData()->data[mid_y][room_no_door_offset_x]->is_collider = true;
				}
			}

			SpriteRenderer* sprite_renderer = new SpriteRenderer(room_prefab, no_door_textures[2]);
			sprite_renderer->setLayer(11);
		}

		if (!top_door_found) {

			
			for (int index = 0; index < room_nb_tile_door_x; index++) {
				
				if (index > 0) {
					if (index % 2 == 0) {
						room->getTileMapData()->data[room_no_door_offset_y][mid_x - index]->is_collider = true;
					}
					else {
						room->getTileMapData()->data[room_no_door_offset_y][mid_x + index]->is_collider = true;
					}
				}
				else {
					
					room->getTileMapData()->data[room_no_door_offset_y][mid_x]->is_collider = true;
				}
			}


			SpriteRenderer* sprite_renderer = new SpriteRenderer(room_prefab, no_door_textures[3]);
			sprite_renderer->setLayer(2);
		}

		

		// ------ CREATE ENEMIES OF THE ROOM -------------
		
		
		int nb_enemies = rand() % 5 + 3;
		for (int i = 0; i < nb_enemies; i++) {
			
			GameObject* new_enemy;
			OwnMathFuncs::Vector2 new_pos = { room_prefab->getWorldPosition() };
			
			OwnMathFuncs::Vector2 sprite_size = room->getTileMapData()->sprite_size;
			OwnMathFuncs::Vector2 new_world_pos = { room_prefab->getWorldPosition().x - (GenerateLevel::room_grid_size_x * sprite_size.x * room_prefab->local_scale.x) / 2,
				room_prefab->getWorldPosition().y - (GenerateLevel::room_grid_size_y * sprite_size.y * room_prefab->local_scale.y) / 2 };


			if (room->getTileMapData()->spawners.size() > 0) {

				int index_spawner = rand() % room->getTileMapData()->spawners.size();
				TileData* tile_data = room->getTileMapData()->spawners[index_spawner];

				new_pos = { new_world_pos.x + tile_data->position_grid.x * sprite_size.x * room_prefab->local_scale.x,
							new_world_pos.y + tile_data->position_grid.y * sprite_size.y * room_prefab->local_scale.x };


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

				new_enemy->is_active = false;
				room->addEnemy(new_enemy);

				Game::instance()->instantiateGameObject(new_enemy);

			}
		}
		//-------------------------------------------

		RoomBehavior* room_behavior = new RoomBehavior(room_prefab, room);

		TileMapCollider* tile_map_collider = new TileMapCollider(room_prefab);
		tile_map_collider->setLayer(40);

		Game::instance()->instantiateGameObject(room_prefab);
		

		//test for start room & end room
		if (start_room == nullptr || (room->getGridPos().x + room->getGridPos().y) <= (start_room->getComponent<RoomBehavior>()->getRoomData()->getGridPos().x + start_room->getComponent<RoomBehavior>()->getRoomData()->getGridPos().y)) {
			start_room = room_prefab;
		}
		else if (end_room == nullptr || (room->getGridPos().x + room->getGridPos().y) >(end_room->getComponent<RoomBehavior>()->getRoomData()->getGridPos().x + end_room->getComponent<RoomBehavior>()->getRoomData()->getGridPos().y)) {
			end_room = room_prefab;
		}
}


	Game::instance()->findGameObject("Player")->local_position = { start_room->getWorldPosition().x + (room_grid_size_x * start_room->getWorldScale().x), start_room->getWorldPosition().y + (room_grid_size_y * start_room->getWorldScale().y) };

	start_room->getComponent<RoomBehavior>()->getRoomData()->setRoomType(Room::StartRoom);
	end_room->getComponent<RoomBehavior>()->getRoomData()->setRoomType(Room::EndRoom);


	OwnMathFuncs::Vector2 player_pos = Game::instance()->findGameObject("Player")->getWorldPosition();
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

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			i++;
		}

		x = room->getGridPos().x + 1;
		y = room->getGridPos().y;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			i++;
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y - 1;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			i++;
		}

		x = room->getGridPos().x;
		y = room->getGridPos().y + 1;

		if (x > 0 && x < GenerateLevel::world_grid_size_x && y > 0 && y < GenerateLevel::world_grid_size_y && rooms[x][y] != nullptr) {
			i++;
		}
	}

	return i;
}

void GenerateLevel::readCSV(const char * file_path, TileMapData* tile_map_data)
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

	tile_map_data->data = vec_temp;
}

void GenerateLevel::readCSVCollider(const char * file_path, TileMapData* tile_map_data)
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
						TileData* t = tile_map_data->getTile(x, y);

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
				TileData* t = tile_map_data->getTile(x, y);

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

void GenerateLevel::readCSVSpawner(const char * file_path, TileMapData * tile_map_data)
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
						TileData* t = tile_map_data->getTile(x, y);
						

						if (t != nullptr) {

							t->is_spawner = true;
							tile_map_data->spawners.push_back(t);
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
				TileData* t = tile_map_data->getTile(x, y);

				if (t != nullptr) {

					t->is_spawner = true;
					tile_map_data->spawners.push_back(t);
				}
			}
			x++;
			buff = "";
		}

		std::cout << "" << std::endl;
		y++;
	}

	std::cout << "----------- SPAWNERS ---------------------" << std::endl;
	for (TileData* tile : tile_map_data->spawners) {

		if (tile != nullptr && tile->is_spawner) {
			std::cout << tile->position_grid.x << ", " << tile->position_grid.y << std::endl;
		}

	}
	std::cout << "-----------------------------------------" << std::endl;
}

OwnMathFuncs::Vector2 GenerateLevel::getNewPos()
{
	bool pos_ok = true;
	int x, y;
	OwnMathFuncs::Vector2 checking_pos = { 0, 0 };

	do {
		//------- GETTING A POS ---------

		//Get a random existing pos
		OwnMathFuncs::Vector2 random_existing_pos = pos_taken.at((int)rand() % (pos_taken.size()));

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
		for (OwnMathFuncs::Vector2 pos : pos_taken) {
			if (pos == checking_pos) {
				pos_ok = false;
			}
		}

	} while (!pos_ok || x < 0 || x > world_grid_size_x || y < 0 || y > world_grid_size_y);


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
