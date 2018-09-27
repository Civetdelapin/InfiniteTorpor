#include "TileMap.h"

TileMap::TileMap(GameObject* game_object, std::string img_path, OwnMathFuncs::Vector2 sprite_size, std::string data_path) : Component(game_object), sprite_size(sprite_size)
{
	texture = TextureManager::LoadTexture(img_path.c_str());

	readCSV(data_path.c_str(), data);
}

TileMap::TileMap(GameObject * game_object, std::string img_path, OwnMathFuncs::Vector2 sprite_size, std::string data_path, std::string collider_path) : Component(game_object), sprite_size(sprite_size)
{
	texture = TextureManager::LoadTexture(img_path.c_str());
	readCSV(data_path.c_str(), data);

	readCSVCollider(collider_path.c_str());
}


TileMap::~TileMap()
{
}

void TileMap::render()
{

	for (std::vector<Tile> tiles_ligne : data) {

		for (Tile tile : tiles_ligne) {

			if (tile.nb_img != -1) {
				SDL_Rect srcrect;
				SDL_Rect dstrect;

				srcrect.x = (tile.nb_img % 30) * sprite_size.x;
				srcrect.y = (tile.nb_img / 30) * sprite_size.y;
				srcrect.h = sprite_size.x;
				srcrect.w = sprite_size.y;

				dstrect.x = game_object->getWorldPosition().x + (tile.position_grid.x * sprite_size.x * game_object->getWorldScale().x);
				dstrect.y = game_object->getWorldPosition().y + (tile.position_grid.y * sprite_size.y * game_object->getWorldScale().y);

				dstrect.h = sprite_size.x * game_object->getWorldScale().x;
				dstrect.w = sprite_size.y * game_object->getWorldScale().y;

				TextureManager::DrawTexture(texture, srcrect, dstrect);

				if (tile.is_collider) {
					TextureManager::DrawRect(dstrect);
				}
			}
		}
	}

}

void TileMap::clean()
{
	SDL_DestroyTexture(texture);
	Component::clean();
}


void TileMap::readCSV(const char* file_path, std::vector<std::vector<Tile>>& vls)
{
	std::vector<std::vector<Tile>> vec_temp;

	std::ifstream myfile(file_path);

	std::cout << "READING : " << file_path << std::endl;

	int x, y = 0;

	while (myfile.good()) {
		x = 0;

		std::vector<Tile> vec_x;

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
			
					struct Tile t;
					t.nb_img = datum;
					t.position_grid = { (float) x, (float) y };

					vec_x.push_back(t);
					
					x++;
					buff = "";
				}
		}
		if (buff != "") v.push_back(atoi(buff.c_str()));

		vec_temp.push_back(vec_x);


		std::cout << "" << std::endl;
		y++;
	}

	vls = vec_temp;
}


std::vector<std::vector<Tile>> TileMap::getData()
{
	return data;
}

Tile* TileMap::getTile(int x, int y)
{
	if (y >= 0 && y < data.size()) {
		//std::cout << "COLLISION : " << std::endl;

		if (x >= 0 && x < data[y].size()) {
			//std::cout << "collider : " << mapCollider[y][x] << std::endl;
			return &data[y][x];
		}

	}

	return nullptr;
}

OwnMathFuncs::Vector2 TileMap::getSpriteSize()
{
	return sprite_size;
}


void TileMap::readCSVCollider(const char * file_path)
{
	std::ifstream myfile(file_path);
	std::cout << "READING : " << file_path << std::endl;

	int x, y = 0;
	while (myfile.good()) {
		x = 0;

		std::vector<Tile> vec_x;

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
						Tile* t = getTile(x, y);

						if (t != nullptr) {

							t->is_collider = true;
						}
					}
					x++;
					buff = "";
				}
		}
		
		std::cout << "" << std::endl;
		y++;
	}

}


Tile::Tile()
{
}
