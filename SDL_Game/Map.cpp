#include "Map.h"

std::vector<std::string> Map::loadMap(SDL_Renderer* renderer)
{
	int w, h;
	map_texture = TextureManager::LoadTexture("img/dungeon_tileset.png", renderer, w, h);

	std::vector<std::string> vls;

	FILE * fp;
	errno_t err = fopen_s(&fp, "levels/TileMap_1.csv", "r");

	readCSV(fp, vls);

	return vls;
}


void Map::readCSV(FILE *fp, std::vector<std::string>& vls)
{
	vls.clear();
	if (!fp)
		return;
	char buf[10000];
	if (!fgets(buf, 999, fp))
		return;
	std::string s = buf;
	int p, q;
	q = -1;
	// loop over columns
	while (1) {
		p = q;
		q = s.find_first_of(",\n", p + 1);
		if (q == -1)
			break;
		vls.push_back(s.substr(p + 1, q - p - 1));
	}
}
