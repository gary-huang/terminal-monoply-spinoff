#ifndef DCTIMSLINE_H
#define DCTIMSLINE_H
#include "nonpropertytile.h"
#include <string>

class Player;
class GameBoard;

class DCTimsLine : public NonPropertyTile{
	public:
		void doEvent(Player *player);
		DCTimsLine(GameBoard *gameboard);
		~DCTimsLine();
};

#endif
