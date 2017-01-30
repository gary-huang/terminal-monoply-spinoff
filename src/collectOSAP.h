#ifndef COLLECTOSAP_H
#define COLLECTOSAP_H
#include "nonpropertytile.h"
#include <string>

class Player;
class GameBoard;

class CollectOSAP : public NonPropertyTile{
	public:
		void doEvent(Player *player);
		CollectOSAP(GameBoard *gameboard);
		~CollectOSAP();
};

#endif
