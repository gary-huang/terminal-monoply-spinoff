#ifndef NONPROPERTYTILE_H
#define NONPROPERTYTILE_H
#include <string>
#include "tile.h"
class Player;

class NonPropertyTile : public Tile {
	public:
		virtual void doEvent(Player *player) = 0;
		~NonPropertyTile();
		NonPropertyTile(GameBoard *gameboard, std::string tileName);
		void notifyMonoplyUpdate(Player *owner, int numImproves);
};

#endif

