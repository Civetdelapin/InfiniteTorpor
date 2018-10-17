#include "RoomBehavior.h"
#include "Game.h"
#include "GameManager.h"

RoomBehavior::RoomBehavior(GameObject * gameObject, Room * roomData) : Component(gameObject), roomData(roomData)
{

}

RoomBehavior::~RoomBehavior()
{

}

void RoomBehavior::start()
{	
	player = Game::instance()->findGameObject("Player");
	gameManager = Game::instance()->findGameObject("Manager")->getComponent<GameManager>();

	if (roomData->getRoomType() == Room::StartRoom || roomData->getRoomType() == Room::EndRoom || roomData->getEnemiesWaves().size() == 0) {
		state = Over;

		if (roomData->getRoomType() == Room::EndRoom) {
			endHitbox = new BoxCollider(gameObject);
			endHitbox->setCollisionLayer(10);

			endHitbox->size = roomData->getTileMapData()->spriteSize * 1;
		}
	}
	else {
		state = NotOver;
	}

	setDoors(false);
}

void RoomBehavior::update()
{

	if (state == NotOver) {

		for (Door* door : roomData->getDoors()) {

			std::vector<Collider*> vect = Game::instance()->getColliderManager()->isTrigger(door->boxColliderTrigger);
			if (vect.size() > 0) {

				for (Collider* collider : vect) {

					if (collider->getGameObject()->tag == "Player") {

						playerStartRoom();

					}
				}
			}
		}

	}
	else if (state == Active) {


		//-------- DEBUG ONLY --------------
		switch (Game::instance()->event.type) {
		case SDL_KEYDOWN:
			switch (Game::instance()->event.key.keysym.sym) {
			case SDLK_F10:
				
				playerEndRoom();
				break;
			}
			break;

		}
		//--------------------------------

		timeLeft -= Time::deltaTime;
		if (timeLeft <= 0) {
			spawnEnemy();
		}

		
		//We remove every enemy dead
		roomData->getEnemiesWaves().erase(
			std::remove_if(
				roomData->getEnemiesWaves().begin(),
				roomData->getEnemiesWaves().end(),
				[](GameObject* const & enemy) {
						if (enemy->getComponent<EnemyBasicBehavior>()->getCurHP() <= 0) {
							return true;
						}
						return false; 
					}
			),
			roomData->getEnemiesWaves().end()
		);
		
		//---------- MANAGE SPAWN ---------------
		bool need_spawn = true;
		for (int i = 0; i < roomData->getEnemiesWaves().size(); i++) {

			if (roomData->getEnemiesWaves()[i]->active) {
				need_spawn = false;
			}
		}
		if (need_spawn) {
			spawnEnemy();
		}
		//--------------------------------------

		if (roomData->getEnemiesWaves().size() == 0) {
			playerEndRoom();
		}
	}
	else {
		if (roomData->getRoomType() == Room::EndRoom) {
			
			//---- END OF FLOOR COLLISION -----
			if(Game::instance()->getColliderManager()->isCollidingWithTag(endHitbox, "Player")) {
			
				gameManager->endLevel();

				endHitbox = nullptr;
			}
			//---------------------------------
		}
	}

}


void RoomBehavior::clean()
{
	
	Component::clean();
}

Room * RoomBehavior::getRoomData()
{
	return roomData;
}

void RoomBehavior::playerStartRoom()

{
	if (state == NotOver) {

		state = Active;
		setDoors(true);

		Game::instance()->getCamera()->setObjectToFollow(gameObject);
		spawnEnemy();
	}
}

void RoomBehavior::playerEndRoom()
{
	setDoorsCollider(false);
	state = Over;

	Game::instance()->getCamera()->setObjectToFollow(player);
	setDoors(false);
}

void RoomBehavior::setDoorsCollider(bool value)
{
	for (Door* door : roomData->getDoors()) {
		door->boxCollider->setActive(value);
	}
}

void RoomBehavior::setDoors(bool value)
{
	setDoorsCollider(value);

	for (Door* door : roomData->getDoors()) {
		if (door->closeDoor != nullptr) {
			door->closeDoor->active = value;
		}
		if (door->openDoor != nullptr) {
			door->openDoor->active = !value;
		}
	}
}

void RoomBehavior::spawnEnemy()
{

	if (roomData->getEnemiesWaves().size() > 0 ) {

		int nb_enemy = 1;
		if (rand() % 6 == 0) {
			nb_enemy = 2;
		}

		for (int i = 0; i < roomData->getEnemiesWaves().size(); i++) {

			if (!roomData->getEnemiesWaves()[i]->active) {
				roomData->getEnemiesWaves()[i]->active = true;
				timeLeft = roomData->getEnemiesWaves()[i]->getComponent<EnemyBasicBehavior>()->getTimeBeforeEnemy();

				nb_enemy--;

				if (nb_enemy == 0) {
					i = roomData->getEnemiesWaves().size();
				}
			}
		}
	}

}
