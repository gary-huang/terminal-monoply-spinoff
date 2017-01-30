#ifndef TUITION_H
#define TUITION_H
#include "nonpropertytile.h"
#include <string>

class Player;
class GameBoard;

class Tuition : public NonPropertyTile {
	public:
		void doEvent(Player * player);
		Tuition(GameBoard *gameboard);
		~Tuition();
};

#endif
