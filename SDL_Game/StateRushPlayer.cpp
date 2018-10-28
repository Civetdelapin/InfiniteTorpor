#include "StateRushPlayer.h"
#include "Game.h"
#include "RoomBehavior.h"
#include "PathFinding.h"
#include "GenerateLevel.h"

StateRushPlayer::StateRushPlayer(GameObject * gameObject, float range, std::string nextState) : State(nextState), range(range)
{
	enemyBasicBehavior = gameObject->getComponent<EnemyBasicBehavior>();
}


StateRushPlayer::~StateRushPlayer()
{
}

void StateRushPlayer::start(StateMachine* state_machine)
{
	state_machine->getGameObject()->getComponent<Animator>()->play("Walking");
	target = Game::instance()->findGameObject("Player");

	positionToGo = state_machine->getGameObject()->getComponent<VelocityBody>()->getColliderWorldPosition();
}

void StateRushPlayer::operation(StateMachine* state_machine)
{	
	
	if (target != nullptr) {
			
		if (OwnMathFuncs::OwnMathFuncs::distanceBetweenVect(target->getWorldPosition(), state_machine->getGameObject()->getWorldPosition()) <= range) {

			state_machine->getGameObject()->getComponent<StateMachine>()->play(getNextState());
		}
		else {

			OwnMathFuncs::Vector2 enemyColliderWorldPosition = state_machine->getGameObject()->getComponent<VelocityBody>()->getColliderWorldPosition();

			OwnMathFuncs::Vector2 testEnemyColliderWorldPosition = { abs(enemyColliderWorldPosition.x), abs(enemyColliderWorldPosition.y) };
			if (testEnemyColliderWorldPosition.x > positionToGo.x - 20 && testEnemyColliderWorldPosition.x < positionToGo.x + 20 &&
				testEnemyColliderWorldPosition.y > positionToGo.y - 20 && testEnemyColliderWorldPosition.y < positionToGo.y + 20) {

					findNewPosition(state_machine);
			}


			OwnMathFuncs::Vector2 direction = ( positionToGo - state_machine->getGameObject()->getComponent<VelocityBody>()->getColliderWorldPosition() );
			OwnMathFuncs::OwnMathFuncs::normalize(direction);

			enemyBasicBehavior->addForce(direction, enemyBasicBehavior->getSpeed());
		}
	}
	else {
		state_machine->getGameObject()->getComponent<StateMachine>()->play(getNextState());
	}
}

void StateRushPlayer::exit(StateMachine* state_machine)
{

}

void StateRushPlayer::findNewPosition(StateMachine* state_machine)
{
	RoomBehavior* roomBehavior = state_machine->getGameObject()->getComponent<EnemyBasicBehavior>()->getRoomBehavior();
			
	OwnMathFuncs::Vector2 new_world_pos = { roomBehavior->getGameObject()->getWorldPosition().x - (GenerateLevel::ROOM_GRID_SIZE_X * roomBehavior->getRoomData()->getTileMapData()->spriteSize.x * roomBehavior->getGameObject()->localScale.x) / 2,
		roomBehavior->getGameObject()->getWorldPosition().y - (GenerateLevel::ROOM_GRID_SIZE_Y * roomBehavior->getRoomData()->getTileMapData()->spriteSize.y * roomBehavior->getGameObject()->localScale.y) / 2 };

	float div_x = (roomBehavior->getGameObject()->getWorldScale().x * roomBehavior->getRoomData()->getTileMapData()->spriteSize.x);
	float div_y = (roomBehavior->getGameObject()->getWorldScale().y * roomBehavior->getRoomData()->getTileMapData()->spriteSize.y);

	OwnMathFuncs::Vector2 enemyColliderPosition = state_machine->getGameObject()->getComponent<VelocityBody>()->getColliderWorldPosition();
	OwnMathFuncs::Vector2 targetColliderPosition = target->getComponent<VelocityBody>()->getColliderWorldPosition();

	OwnMathFuncs::Vector2 startPoint = {(float)(int)( (enemyColliderPosition.x - new_world_pos.x) / div_x),
		(float) (int)( (enemyColliderPosition.y - new_world_pos.y) / div_y )};

	OwnMathFuncs::Vector2 endPoint = {(float) (int)( (targetColliderPosition.x - new_world_pos.x) / div_x),
		(float) (int)( (targetColliderPosition.y - new_world_pos.y) / div_y )};

	//std::cout << "ENEMY : " << startPoint.toString() << std::endl;
	//std::cout << " PLAYER : " <<endPoint.toString() << std::endl;

	std::vector<TileData*> pathToTarget = PathFinding::getPath(roomBehavior->getRoomData()->getTileMapData(), startPoint, endPoint);

	/*
	std::cout << "PRINT PATH" << std::endl;
	for (TileData* tileData : pathToTarget) {
		std::cout << tileData->positionGrid.toString() << std::endl;
	}
	std::cout << "---------------------" << std::endl;
	*/		

	if (pathToTarget.size() >= 2) {

		positionToGo = { new_world_pos.x + (pathToTarget[pathToTarget.size() - 2]->positionGrid.x * div_x) + div_x / 2,
			new_world_pos.y + (pathToTarget[pathToTarget.size() - 2]->positionGrid.y * div_y) + div_y / 2 };

		//std::cout << "New Pos : " << positionToGo.toString() << std::endl;
	}
}
