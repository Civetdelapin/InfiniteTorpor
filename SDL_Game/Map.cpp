#include "Map.h"

Map::Map(SDL_Renderer* renderer, int map_int) : GameObject(renderer)
{
	int w, h;
	map_texture = TextureManager::LoadTexture("img/dungeon_tileset.png", renderer, w, h);

	std::ostringstream o;
	o << "levels/TileMap_" << map_int << ".csv" ;
	readCSV(o.str().c_str(), mapValues);


	std::ostringstream o2;
	o2 << "levels/TileMap_" << map_int << "_Collider.csv";
	readCSV(o2.str().c_str(), mapCollider);
}

Map::~Map()
{




}


void Map::render(float camera_pos_x, float camera_pos_y)
{
	DrawMap(mapValues, camera_pos_x, camera_pos_y);
	DrawMap(mapCollider, camera_pos_x, camera_pos_y);
}

int Map::getTile(int x, int y)
{
	//std::cout << "---------------" << std::endl;
	//std::cout << "x : " << x << " , y : " << y << std::endl;


	//Get the x and y by the world space
	x = (x - position.x) / (scale_factor * Map::tile_width); 
	y = (y - position.y) / (scale_factor * Map::tile_height);

	//std::cout << "x : " << x << " , y : " << y << std::endl;

	if (y >= 0 && y < mapCollider.size() ) {
		//std::cout << "COLLISION : " << std::endl;

		if (x >= 0 && x < mapCollider[y].size()) {
			//std::cout << "collider : " << mapCollider[y][x] << std::endl;
			return mapCollider[y][x];
		}

	}
	
	return -1;
}

void Map::DrawMap(std::vector<std::vector<int>> vecToDraw, float camera_pos_x, float camera_pos_y)
{
	int x = 0;
	int y = 0;
	for (std::vector<int> mapValue : vecToDraw) {
		x = 0;
		for (int i : mapValue) {

			if (i != -1) {
				SDL_Rect srcrect;
				SDL_Rect dstrect;

				srcrect.x = (i % 30) * Map::tile_width;

				srcrect.y = (i / 30) * Map::tile_height;
				srcrect.h = Map::tile_height;
				srcrect.w = Map::tile_width;

				dstrect.x = position.x - camera_pos_x + (x * Map::tile_width * scale_factor);
				dstrect.y = position.y - camera_pos_y + (y * Map::tile_height * scale_factor);

				dstrect.h = Map::tile_height * scale_factor;
				dstrect.w = Map::tile_width * scale_factor;

				TextureManager::DrawTexture(map_texture, renderer, srcrect, dstrect);

			}
			x++;
		}

		y++;
	}

}

void Map::readCSV(const char* file_path, std::vector<std::vector<int>>& vls)
{
	std::vector<std::vector<int>> vecTemp;

	std::ifstream myfile(file_path);

	std::cout << "READING : " << file_path << std::endl;

	while (myfile.good()) {
		
		std::string line;
		std::getline(myfile, line, '\n');

		std::string buff{ "" };
		std::vector<int> v;

		for (auto n : line)
		{
			if (n != ',') buff += n; else
				if (n == ',' && buff != "") { 

					std::cout << buff << ", ";

					v.push_back(atoi(buff.c_str())); buff = "";
				}
		}
		if (buff != "") v.push_back(atoi(buff.c_str()));

		std::cout << "" << std::endl;

		vecTemp.push_back(v);
	}

	vls = vecTemp;
}



