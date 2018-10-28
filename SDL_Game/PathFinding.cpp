#include "PathFinding.h"

PathFinding::PathFinding()
{

}


PathFinding::~PathFinding()
{

}

std::vector<TileData*> PathFinding::getPath(TileMapData * tileMapData, OwnMathFuncs::Vector2 startPoint, OwnMathFuncs::Vector2 endPoint)
{
	OwnMathFuncs::Vector2 direction[]  = {
		{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
	{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
	};

	std::vector<TileData*> path;

	if (tileMapData->getTile(startPoint.x, startPoint.y) == nullptr || tileMapData->getTile(startPoint.x, startPoint.y)->collider || tileMapData->getTile(endPoint.x, endPoint.y) == nullptr || tileMapData->getTile(endPoint.x, endPoint.y)->collider) {
		std::cout << "NO VALID POSITION " << std::endl;
		return path;
	}

	std::vector<Node*> openTile;
	std::vector<Node*> closeTile;

	Node* startNode = new Node({ startPoint.x, startPoint.y });
	startNode->heuristic = abs(startNode->position.x - endPoint.x) + abs(startNode->position.y - endPoint.y);

	openTile.push_back(startNode);

	Node* currentNode;

	while (!openTile.empty()) {

		currentNode = openTile.front();
		for (Node* node : openTile) {

			if (node->getScore() <= currentNode->getScore()) {
				currentNode = node;
			}

		}

		if (currentNode->position == endPoint) {
			std::cout << "FIND THE END, EXIT " << std::endl;
			break;
		}


		closeTile.push_back(currentNode);
		openTile.erase(std::find(openTile.begin(), openTile.end(), currentNode));


		for (int i = 0; i < 8; ++i) {
			OwnMathFuncs::Vector2 newCoordinates = currentNode->position + direction[i];

			TileData* newTile = tileMapData->getTile(newCoordinates.x, newCoordinates.y);

			if (newTile == nullptr || newTile->collider || findNodeOnVectorByPosition(closeTile, newCoordinates) != nullptr) {
				continue;
			}
			
			int totalCost = currentNode->score + 1;

			Node* newNode = findNodeOnVectorByPosition(openTile, newCoordinates);
			if (newNode == nullptr) {
				newNode = new Node(newCoordinates);
				openTile.push_back(newNode);
			}
			else if (totalCost >= newNode->score) {
				continue;
			}

			newNode->score = totalCost;
			newNode->heuristic = abs(newNode->position.x - endPoint.x) + abs(newNode->position.y - endPoint.y);
			newNode->parent = currentNode;
		}

	}

	while (currentNode != nullptr) {
		path.push_back(tileMapData->getTile(currentNode->position.x, currentNode->position.y));
		currentNode = currentNode->parent;
	}

	//---- FREE EVERYTHING ----
	for (auto it = openTile.begin(); it != openTile.end();) {
		delete *it;
		it = openTile.erase(it);
	}

	for (auto it = closeTile.begin(); it != closeTile.end();) {
		delete *it;
		it = closeTile.erase(it);
	}

	return path;
}

Node * PathFinding::findNodeOnVectorByPosition(std::vector<Node*>& vector, OwnMathFuncs::Vector2 position)
{
	for (auto node : vector) {
		if (node->position == position) {
			return node;
		}
	}
	return nullptr;
}

int Node::getScore()
{
	return score + heuristic;
}

Node::Node(OwnMathFuncs::Vector2 pos) : position(pos)
{

}
