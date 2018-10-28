#pragma once
#include "Room.h"
#include <list>

struct Node{

	Node* parent = nullptr;
	OwnMathFuncs::Vector2 position = { 0, 0 };

	int score = 0;
	int heuristic = 0;

	int getScore();

	Node(OwnMathFuncs::Vector2 pos);
};

class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	static std::vector<TileData*> getPath(TileMapData* tileMapData, OwnMathFuncs::Vector2 startPoint, OwnMathFuncs::Vector2 endPoint);

private:
	static Node* findNodeOnVectorByPosition(std::vector<Node*>& vector, OwnMathFuncs::Vector2 position);
};

