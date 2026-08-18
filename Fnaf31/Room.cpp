#include "Room.h"

const char* roomName(Room room)
{
	switch (room)
	{
	case Room::MainStage:
		return "Main Stage";

	case Room::FoodCourt:
		return "Food Court";

	case Room::GameStalls:
		return "Game Stalls";

	case Room::LeftHall:
		return "Left Hall";
	
	case Room::RightHall:
		return "Right Hall";

	case Room::LeftDoor:
		return "Left Door";

	case Room::RightDoor:
		return "Right Door";


	default:
		return  "unkown";
	}
}
