#ifndef SLC_H
#define SLC_H
#include "nonpropertytile.h"
#include <string>

class Player;
class GameBoard;

class Slc : public NonPropertyTile {
	bool canGetTimsCup(Player *player);
	void move(Player *player);
	public:
		void doEvent(Player * player);
		Slc(GameBoard *gameboard);
		~Slc();
};

#endif
