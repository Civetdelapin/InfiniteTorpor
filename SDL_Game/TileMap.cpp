#include "TileMap.h"

TileMap::TileMap(GameObject* game_object, std::string img_path, OwnMathFuncs::Vector2* sprite_size, std::string data_path) : Component(game_object), sprite_size(sprite_size)
{
	texture = TextureManager::LoadTexture(img_path.c_str());

	readCSV(data_path.c_str(), data);

	

}


TileMap::~TileMap()
{
}

void TileMap::render(float camera_pos_x, float camera_pos_y)
{

	for (Tile tile : data) {

		//std::cout << "Vect_x : " << tile.position_grid.x << " vect_y : " << tile.position_grid.y << " img : " << tile.nb_img << std::endl;

		SDL_Rect srcrect;
		SDL_Rect dstrect;

		srcrect.x = (tile.nb_img % 30) * sprite_size->x;
		srcrect.y = (tile.nb_img / 30) * sprite_size->y;
		srcrect.h = sprite_size->x;
		srcrect.w = sprite_size->y;

		dstrect.x = game_object->position.x - camera_pos_x + (tile.position_grid.x * sprite_size->x * game_object->scale.x);
		dstrect.y = game_object->position.y - camera_pos_y + (tile.position_grid.y * sprite_size->y * game_object->scale.y);

		dstrect.h = sprite_size->x * game_object->scale.x;
		dstrect.w = sprite_size->y * game_object->scale.y;

		TextureManager::DrawTexture(texture, srcrect, dstrect);
	}

}


void TileMap::readCSV(const char* file_path, std::vector<Tile>& vls)
{
	std::vector<Tile> vecTemp;
	std::ifstream myfile(file_path);

	
	std::cout << "READING : " << file_path << std::endl;

	int x, y = 0;

	while (myfile.good()) {
		x = 0;

		std::string line;
		std::getline(myfile, line, '\n');

		std::string buff{ "" };
		std::vector<int> v;

		for (auto n : line)
		{
			if (n != ',') buff += n; else
				if (n == ',' && buff != "") {

					std::cout << buff << ", ";

					int datum = atoi(buff.c_str());
					if (datum != -1) {

						struct Tile t;
						t.nb_img = datum;
						t.position_grid = { (float) x, (float) y };

						vecTemp.push_back(t);
					}
					
					x++;
					buff = "";
				}

			
		}
		if (buff != "") v.push_back(atoi(buff.c_str()));

		std::cout << "" << std::endl;
		y++;
	}

	vls = vecTemp;

}
/*
int TileMap::getTile(int x, int y)
{
	//std::cout << "---------------" << std::endl;
	//std::cout << "x : " << x << " , y : " << y << std::endl;


	//Get the x and y by the world space
	x = (x - position.x) / (scale_factor * Map::tile_width);
	y = (y - position.y) / (scale_factor * Map::tile_height);

	//std::cout << "x : " << x << " , y : " << y << std::endl;

	if (y >= 0 && y < mapCollider.size()) {
		//std::cout << "COLLISION : " << std::endl;

		if (x >= 0 && x < mapCollider[y].size()) {
			//std::cout << "collider : " << mapCollider[y][x] << std::endl;
			return mapCollider[y][x];
		}

	}

	return -1;
}
*/


Tile::Tile()
{
}
