#ifndef COOPFEE_H
#define COOPFEE_H
#include "nonpropertytile.h"
#include <string>
class Player;
class GameBoard;

class CoopFee : public NonPropertyTile {
	public:
	void doEvent(Player * player);
	CoopFee(GameBoard *gameboard);
	~CoopFee();
};

#endif
