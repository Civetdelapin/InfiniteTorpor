#include "RoomBehavior.h"
#include "Game.h"


RoomBehavior::RoomBehavior(GameObject * game_object, Room * room_data) : Component(game_object), room_data(room_data)
{

}

RoomBehavior::~RoomBehavior()
{

}

void RoomBehavior::start()
{
	player = Game::instance()->findGameObject("Player");


	if (room_data->getRoomType() == Room::StartRoom) {
		state = Over;
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

			std::vector<Collider*> vect = Game::instance()->collider_manager->isTrigger(door->box_collider_trigger);
			if (vect.size() > 0) {

				for (Collider* collider : vect) {

					if (collider->getGameObject()->tag == "Player") {

						playerEnterRoom();

					}
				}
			}
		}

	}
	else if (state == Active) {


		//For debug 
		switch (Game::instance()->event.type) {
		case SDL_KEYDOWN:
			switch (Game::instance()->event.key.keysym.sym) {
			case SDLK_F10:
				
				playerEndRoom();
				break;
			}
			break;

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

void RoomBehavior::playerEnterRoom()

{
	if (state == NotOver) {

		Game::instance()->getCamera()->setObjectToFollow(game_object);

		state = Active;

		setDoors(true);
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
			door->close_door->is_active = value;
		}
		if (door->open_door != nullptr) {
			door->open_door->is_active = !value;
		}
	}
}
