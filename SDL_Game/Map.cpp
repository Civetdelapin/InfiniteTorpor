#include "Map.h"

Map::Map(SDL_Renderer* renderer, int map_int) : GameObject(renderer)
{
	int w, h;
	map_texture = TextureManager::LoadTexture("img/dungeon_tileset.png", renderer, w, h);

	std::ostringstream o;
	o << "levels/TileMap_" << map_int << ".csv" ;

	readCSV(o.str().c_str(), mapValues);
}

Map::~Map()
{
}


void Map::render(float camera_pos_x, float camera_pos_y)
{
	int x = 0;
	int y = 0;
	for (std::vector<int> mapValue : mapValues) {
		x = 0;
		for (int i : mapValue) {

			if (i != -1) {
				SDL_Rect srcrect;
				SDL_Rect dstrect;

				srcrect.x = (i % 30) * Map::tile_width;

				srcrect.y = (i / 30) * Map::tile_height;
				srcrect.h = Map::tile_height;
				srcrect.w = Map::tile_width;

				dstrect.x = position.x - camera_pos_x + (x * Map::tile_width * scale_factor) - ((mapValue.size() / 2) * scale_factor * Map::tile_width) ;
				dstrect.y = position.y - camera_pos_y + (y * Map::tile_height * scale_factor) - ((mapValues.size() / 2) * scale_factor * Map::tile_width);

				dstrect.h = Map::tile_height * scale_factor;
				dstrect.w = Map::tile_width * scale_factor;

				TextureManager::DrawTexture(map_texture, renderer, srcrect, dstrect);
				x++;
			}

		}

		y++;
	}

}

void Map::readCSV(const char* file_path, std::vector<std::vector<int>>& vls)
{
	std::vector<std::vector<int>> vecTemp;

	std::ifstream myfile(file_path);

	while (myfile.good()) {
		
		std::string line;
		std::getline(myfile, line, '\n');

		std::string buff{ "" };
		std::vector<int> v;

		for (auto n : line)
		{
			if (n != ',') buff += n; else
				if (n == ',' && buff != "") { 
					v.push_back(atoi(buff.c_str())); buff = "";
				}
		}
		if (buff != "") v.push_back(atoi(buff.c_str()));


		vecTemp.push_back(v);
	}

	vls = vecTemp;
}
