#ifndef GOOSENESTINGG_H
#define GOOSENESTINGG_H
#include "nonpropertytile.h"
#include <string>

class Player;

class GooseNesting : public NonPropertyTile {
	public:
	void doEvent(Player * actOn);
	GooseNesting(GameBoard *gameboard);
	~GooseNesting();
};

#endif
