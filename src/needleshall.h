#ifndef NEEDLESHALL_H
#define NEEDLESHALL_H
#include "nonpropertytile.h"
#include <string>

class Player;
class GameBoard;

class NeedlesHall : public NonPropertyTile {
	bool canGetTimsCup(Player *player);
	void normalNH(Player *player);
	public:
		void doEvent(Player * player);
		NeedlesHall(GameBoard *gameboard);
		~NeedlesHall();
};

#endif
