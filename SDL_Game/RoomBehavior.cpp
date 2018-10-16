#include "RoomBehavior.h"
#include "Game.h"
#include "GameManager.h"

RoomBehavior::RoomBehavior(GameObject * gameObject, Room * room_data) : Component(gameObject), room_data(room_data)
{

}

RoomBehavior::~RoomBehavior()
{

}

void RoomBehavior::start()
{	
	player = Game::instance()->findGameObject("Player");
	game_manager = Game::instance()->findGameObject("Manager")->getComponent<GameManager>();

	if (room_data->getRoomType() == Room::StartRoom || room_data->getRoomType() == Room::EndRoom || room_data->getEnemiesWaves().size() == 0) {
		state = Over;

		if (room_data->getRoomType() == Room::EndRoom) {
			end_hitbox = new BoxCollider(gameObject);
			end_hitbox->setCollisionLayer(10);

			end_hitbox->size = room_data->getTileMapData()->sprite_size * 2;
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

		for (Door* door : room_data->getDoors()) {

			std::vector<Collider*> vect = Game::instance()->getColliderManager()->isTrigger(door->box_collider_trigger);
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
		room_data->getEnemiesWaves().erase(
			std::remove_if(
				room_data->getEnemiesWaves().begin(),
				room_data->getEnemiesWaves().end(),
				[](GameObject* const & enemy) {
						if (enemy->getComponent<EnemyBasicBehavior>()->getCurHP() <= 0) {
							return true;
						}
						return false; 
					}
			),
			room_data->getEnemiesWaves().end()
		);
		
		//---------- MANAGE SPAWN ---------------
		bool need_spawn = true;
		for (int i = 0; i < room_data->getEnemiesWaves().size(); i++) {

			if (room_data->getEnemiesWaves()[i]->active) {
				need_spawn = false;
			}
		}
		if (need_spawn) {
			spawnEnemy();
		}
		//--------------------------------------

		if (room_data->getEnemiesWaves().size() == 0) {
			playerEndRoom();
		}
	}
	else {
		if (room_data->getRoomType() == Room::EndRoom) {
			
			//---- END OF FLOOR COLLISION -----
			if(Game::instance()->getColliderManager()->isCollidingWithTag(end_hitbox, "Player")) {
			
				game_manager->endLevel();

				end_hitbox = nullptr;
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
	return room_data;
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
	for (Door* door : room_data->getDoors()) {
		door->box_collider->setActive(value);
	}
}

void RoomBehavior::setDoors(bool value)
{
	setDoorsCollider(value);

	for (Door* door : room_data->getDoors()) {
		if (door->close_door != nullptr) {
			door->close_door->active = value;
		}
		if (door->open_door != nullptr) {
			door->open_door->active = !value;
		}
	}
}

void RoomBehavior::spawnEnemy()
{

	if (room_data->getEnemiesWaves().size() > 0 ) {

		int nb_enemy = 1;
		if (rand() % 6 == 0) {
			nb_enemy = 2;
		}

		for (int i = 0; i < room_data->getEnemiesWaves().size(); i++) {

			if (!room_data->getEnemiesWaves()[i]->active) {
				room_data->getEnemiesWaves()[i]->active = true;
				timeLeft = room_data->getEnemiesWaves()[i]->getComponent<EnemyBasicBehavior>()->getTimeBeforeEnemy();

				nb_enemy--;

				if (nb_enemy == 0) {
					i = room_data->getEnemiesWaves().size();
				}
			}
		}
	}

}
