#include "RoomBehavior.h"
#include "Game.h"


RoomBehavior::RoomBehavior(GameObject * game_object, Room * room_data) : Component(game_object), Renderer(this), room_data(room_data)
{

}

RoomBehavior::~RoomBehavior()
{

}

void RoomBehavior::start()
{

	if (room_data->getRoomType() == Room::StartRoom) {
		state = Over;
	}
	else {
		state = NotOver;
	}

	setDoorsCollider(false);
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

void RoomBehavior::render()
{
	
}

void RoomBehavior::clean()
{

	Renderer::clean();
	Component::clean();
}

Room * RoomBehavior::getRoomData()
{
	return room_data;
}

void RoomBehavior::playerEnterRoom()

{
	if (state == NotOver) {
		setDoorsCollider(true);
		state = Active;
	}
}

void RoomBehavior::playerEndRoom()
{
	setDoorsCollider(false);

	state = Over;
}

void RoomBehavior::setDoorsCollider(bool value)
{
	for (Door* door : room_data->getDoors()) {
		door->box_collider->setActive(value);
	}
}
