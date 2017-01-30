#ifndef GOTOTIMS_H
#define GOTOTIMS_H
#include "nonpropertytile.h"
#include <string>

class Player;
class GameBoard;

class GoToTims : public NonPropertyTile {
	public:
		void doEvent(Player * actOn);
		GoToTims(GameBoard *gameboard);
		~GoToTims();
};

#endif
